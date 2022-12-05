/*
 * qianqians
 * 2020-1-22
 * battle
 * map_data.cpp
 */

#include <fstream>
#include <memory>
#include <unordered_map>

#include <absl/container/node_hash_map.h>

#include <hub.h>
#include <config.h>

#include "map_data.h"
#include "role.h"

namespace battle {

int32_t map_width = 0;
int32_t map_height = 0;
int32_t map_width_box = 0;
int32_t map_height_box = 0;
std::vector<tiledmap> tiledmap_list;

struct map_box_property {
    int32_t collision = 1;
    int32_t hp = 1;
    int32_t groundlayer = 0;
};

static absl::node_hash_map<int32_t, map_box_property> _property;
static int32_t max_property_id = 0;
static std::vector<int32_t> map_data_list;
static std::vector<int32_t> house_data_list;
static std::vector<door> door_list;
static std::vector<ladder> ladder_list;

void map_primitive_data(std::string data_path) {
    auto chicken_world_path = data_path + "/" + "Chicken.world";
    auto chicken_world = config::config(chicken_world_path).get_value_list("maps");

    //Fossilizid::JsonParse::JsonObject chicken_world_info;
    //Fossilizid::JsonParse::unpacker(chicken_world_info, chicken_world_file_str);
    //auto chicken_world_info_table = Fossilizid::JsonParse::JsonCast<Fossilizid::JsonParse::JsonTable>(chicken_world_info);
    //auto maps = Fossilizid::JsonParse::JsonCast<Fossilizid::JsonParse::JsonArray>((*chicken_world_info_table)["maps"]);
    auto minx = 0, miny = 0, maxx = 0, maxy = 0;
    for (auto i = 0; i < chicken_world->get_list_size(); i++) {
        auto map_data = chicken_world->get_list_dict(i);
        auto x = (int32_t)map_data->get_value_int("x");
        auto y = (int32_t)map_data->get_value_int("y");

        if (x < minx) {
            minx = x;
        }

        if (y < miny) {
            miny = y;
        }

        if (x > maxx) {
            maxx = x;
        }

        if (y > maxy) {
            maxy = y;
        }
    }
    maxx += 1024;
    maxy += 512;
    auto width = maxx - minx;
    auto height = maxy - miny;
    auto width_box = width / 16;
    auto height_box = height / 16;

    map_width = width;
    map_height = height;
    map_width_box = width_box;
    map_height_box = height_box;
    map_data_list.resize(map_width_box * map_height_box);
    house_data_list.resize(map_width_box * map_height_box);

    spdlog::trace("begin chicken_world get_list_size:{0}", chicken_world->get_list_size());
    for (auto i = 0; i < chicken_world->get_list_size(); i++) {
        auto map_data = chicken_world->get_list_dict(i);
        auto x = (int32_t)map_data->get_value_int("x");
        auto y = (int32_t)map_data->get_value_int("y");

        auto file_name = map_data->get_value_string("fileName");
        auto real_file_name = file_name.substr(0, file_name.find('.'));
        auto json_file_name = real_file_name + ".json";
        auto offset_x = x / 16;
        auto offset_y = (0 - y) / 16;

        json_file_name = data_path + "/" + json_file_name;
        auto map_info_table = config::config(json_file_name);
        
        auto map_info_tilesets = map_info_table.get_value_list("tilesets");
        for (auto tile = 0; tile < map_info_tilesets->get_list_size(); tile++) {
            auto tile_info = map_info_tilesets->get_list_dict(tile);

            if (!tile_info->has_key("source")) {
                continue;
            }

            auto property_file_name = tile_info->get_value_string("source");
            auto begin = property_file_name.rfind('/');
            if (begin == std::string::npos) {
                begin = 0;
            }
            else {
                begin += 1;
            }
            auto end = property_file_name.rfind('.');
            auto real_property_file_name = property_file_name.substr(begin, end - begin);
            if (real_property_file_name == "empty") {
                continue;
            }
            auto json_property_file_name = real_property_file_name + ".json";
            auto firstgid = tile_info->get_value_int("firstgid");

            json_property_file_name = data_path + "/" + json_property_file_name;
            auto property_info_table = config::config(json_property_file_name);
            if (!property_info_table.has_key("tiles")) {
                continue;
            }
            auto property_info_tiles = property_info_table.get_value_list("tiles");
            for (auto tile_property = 0; tile_property < property_info_tiles->get_list_size(); tile_property++) {
                auto tile_property_info = property_info_tiles->get_list_dict(tile_property);
                auto id = tile_property_info->get_value_int("id");
                if (tile_property_info->has_key("terrain")) {
                    auto terrain_list = tile_property_info->get_value_list("terrain");
                    auto terrain = -1;
                    for (int i = 0; i < 4; i++) {
                        terrain = (int)terrain_list->get_list_int(i);
                        if (terrain >= 0) {
                            break;
                        }
                    }
                    auto terrains = property_info_table.get_value_list("terrains");
                    auto terrain_info = terrains->get_list_dict(terrain);
                    if (terrain_info->has_key("properties")) {
                        auto terrain_property = terrain_info->get_value_list("properties");

                        map_box_property _map_box_property;
                        for (auto sub_p = 0; sub_p < terrain_property->get_list_size(); sub_p++) {
                            auto sub_p_table = terrain_property->get_list_dict(sub_p);
                            auto sub_p_name = sub_p_table->get_value_string("name");

                            if (sub_p_name == "collision") {
                                _map_box_property.collision = (int32_t)sub_p_table->get_value_int("value");
                            }
                            else if (sub_p_name == "hp") {
                                _map_box_property.hp = (int32_t)sub_p_table->get_value_int("value");
                            }
                            else if (sub_p_name == "Out" || sub_p_name == "out") {
                                _map_box_property.groundlayer = (int32_t)sub_p_table->get_value_int("value");
                            }
                        }
                        auto _id = (int32_t)(id + firstgid);
                        _property.insert(std::make_pair(_id, _map_box_property));

                        if (_id > max_property_id) {
                            max_property_id = _id;
                        }
                    }
                }
                else if (tile_property_info->has_key("properties")) {
                    auto terrain_property = tile_property_info->get_value_list("properties");

                    map_box_property _map_box_property;
                    for (auto sub_p = 0; sub_p < terrain_property->get_list_size(); sub_p++) {
                        auto sub_p_table = terrain_property->get_list_dict(sub_p);
                        auto sub_p_name = sub_p_table->get_value_string("name");

                        if (sub_p_name == "collision") {
                            _map_box_property.collision = (int32_t)sub_p_table->get_value_int("value");
                        }
                        else if (sub_p_name == "hp") {
                            _map_box_property.hp = (int32_t)sub_p_table->get_value_int("value");
                        }
                        else if (sub_p_name == "Out" || sub_p_name == "out") {
                            _map_box_property.groundlayer = (int32_t)sub_p_table->get_value_int("value");
                        }
                    }

                    auto _id = (int32_t)(id + firstgid);
                    _property.insert(std::make_pair(_id, _map_box_property));

                    if (_id > max_property_id) {
                        max_property_id = _id;
                    }
                }
            }
        }

        auto layers = map_info_table.get_value_list("layers");
        for (auto layer = 0; layer < layers->get_list_size(); layer++) {
            auto layer_info = layers->get_list_dict(layer);
            auto layer_name = layer_info->get_value_string("name");
            spdlog::trace("layer_name:{0}", layer_name);

            if (layer_name == "groundLayer") {
                auto data = layer_info->get_value_list("data");
                
                for (auto x = 0; x < 64; x++) {
                    for (auto y = 0; y < 32; y++) {
                        auto id = (int32_t)data->get_list_int(y * 64 + x);
                        map_data_list[(offset_y + (32 - y - 1)) * width_box + (offset_x + x)] = id;
                        spdlog::trace("map_data_list id:{0} x:{1} y{2}", id, x, y);
                    }
                }
            }
            else if (layer_name == "houseLayer"){
                auto data = layer_info->get_value_list("data");
                
                for (auto x = 0; x < 64; x++) {
                    for (auto y = 0; y < 32; y++) {
                        auto id =(int32_t)data->get_list_int(y * 64 + x);
                        house_data_list[(offset_y + (32 - y - 1)) * width_box + (offset_x + x)] = id;
                    }
                }
            }
            else if (layer_name == "objectLayer"){
                auto data = layer_info->get_value_list("objects");

                for (auto object = 0; object < data->get_list_size(); object++) {
                    auto object_info = data->get_list_dict(object);

                    int32_t door_x = (int32_t)object_info->get_value_int("x");
                    int32_t door_width = (int32_t)object_info->get_value_int("width");
                    int32_t door_y = (int32_t)object_info->get_value_int("y");
                    int32_t door_height = (int32_t)object_info->get_value_int("height");

                    door _door;
                    _door.x_min = (int32_t)(door_x + x);
                    _door.x_max = (int32_t)(door_x + x + door_width);
                    _door.y_min = (int32_t)((512 - door_y - door_height) + y);
                    _door.y_max = (int32_t)((512 - door_y) + y);
                    door_list.push_back(_door);
                }
            }
            else if (layer_name == "ladderLayer") {
                auto data = layer_info->get_value_list("objects");

                for (auto object = 0; object < data->get_list_size(); object++) {
                    auto object_info = data->get_list_dict(object);

                    int32_t ladder_x = (int32_t)object_info->get_value_int("x");
                    int32_t ladder_width = (int32_t)object_info->get_value_int("width");
                    int32_t ladder_y = (int32_t)object_info->get_value_int("y");
                    int32_t ladder_height = (int32_t)object_info->get_value_int("height");

                    ladder _ladder;
                    _ladder.x_min = (int32_t)(ladder_x + x);
                    _ladder.x_max = (int32_t)(ladder_x + x + ladder_width);
                    _ladder.y_min = (int32_t)((512 - ladder_y - ladder_height) + y);
                    _ladder.y_max = (int32_t)((512 - ladder_y) + y);
                    ladder_list.push_back(_ladder);
                }
            }
        }

        tiledmap _tiled;
        _tiled.x_offset_begin = (int32_t)offset_x;
        _tiled.x_offset_end = (int32_t)(offset_x + 64);
        _tiled.y_offset_begin = (int32_t)offset_y;
        _tiled.y_offset_end = (int32_t)(offset_y + 32);
        _tiled.tiledmap_name = real_file_name;
        tiledmap_list.push_back(_tiled);
    }
}

std::vector<std::shared_ptr<box> > create_map() {
    std::vector<std::shared_ptr<box> > map_data_stack = {};
    for (size_t i = 0; i < map_data_list.size(); i++) {
        auto p = map_data_list[i];
        auto _box = std::make_shared<box>();
        do {
            if (p == 0) {
                _box->map_elem = std::make_shared<empty_element>();
                //spdlog::trace("create_map p == 0 property:{0}, x:{1}, y{2}!", p, i % map_width_box, i / map_width_box);
                break;
            }

            auto box_property = _property.find(p);
            if (box_property == _property.end()) {
                _box->map_elem = std::make_shared<empty_element>();
                spdlog::trace("create_map invaild property:{0}, x:{1}, y{2}!", p, i % map_width_box, i / map_width_box);
                break;
            }

            _box->map_elem = std::make_shared<map_element>((int32_t)box_property->second.collision, box_property->second.hp, box_property->second.groundlayer);

        } while (false);

        map_data_stack.push_back(_box);
    }

    return map_data_stack;
}

std::vector<std::shared_ptr<box> > create_house() {
    std::vector<std::shared_ptr<box> > house_data_stack = {};
    for (size_t i = 0; i < house_data_list.size(); i++) {
        auto p = house_data_list[i];
        auto _box = std::make_shared<box>();
        do {
            if (p == 0) {
                _box->map_elem = std::make_shared<empty_element>();
                break;
            }

            auto box_property = _property.find(p);
            if (box_property == _property.end()) {
                _box->map_elem = std::make_shared<empty_element>();
                spdlog::trace("create_house invaild property:{0}, x:{1}, y{2}!", p, i % map_width_box, i / map_width_box);
                break;
            }

            _box->map_elem = std::make_shared<map_element>((int32_t)box_property->second.collision, box_property->second.hp, box_property->second.groundlayer);

        } while (false);

        house_data_stack.push_back(_box);
    }

    return house_data_stack;
}

std::vector<door> create_door() {
    return door_list;
}

std::vector<ladder> create_ladder() {
    return ladder_list;
}

bool box::check_exist_enemy(std::shared_ptr<role> _self) {
    bool has_enemy = false;
    auto _self_team = _self->_team_handle.lock();
    for (auto i : role_list) {
        auto _i_ptr = i.lock();
        if (!_i_ptr) {
            continue;
        }

        if (_i_ptr == _self) {
            continue;
        }

        if (!_i_ptr->is_live) {
            continue;
        }

        auto _i_team = _i_ptr->_team_handle.lock();
        if (_i_team != _self_team) {
            has_enemy = true;
            break;
        }
    }
    return has_enemy;
}

}
