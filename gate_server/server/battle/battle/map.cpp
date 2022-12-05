/*
 * qianqians
 * 2020-1-22
 * battle
 * map.cpp
 */
#include "random.h"
#include "map.h"
#include "battle.h"
#include "role.h"

namespace battle {

int sub_map::count = 0;

sub_map::sub_map() {
    ++count;
}

sub_map::~sub_map() {
    spdlog::trace("sub_map destruction count:{0}", --count);
}

void sub_map::leave_sub_map(std::weak_ptr<role> _role) {
    for (auto it = field_roles.begin(); it != field_roles.end(); it++) {
        if (it->lock() == _role.lock()) {
            field_roles.erase(it);
            break;
        }
    }
}

void sub_map::into_sub_map(std::weak_ptr<role> _role) {
    field_roles.push_back(_role);
}

std::vector<std::string> sub_map::get_field_roles_uuid() {
    std::vector<std::string> roles_uuid;
    for (auto _role : field_roles) {
        auto _role_ptr = _role.lock();
        if (!_role_ptr) {
            continue;
        }

        if (!_role_ptr->check_sync()) {
            continue;
        }

        roles_uuid.push_back(_role_ptr->uuid);
    }
    return roles_uuid;
}

int map::count = 0;

map::map() {
    map_data = create_map();
    house_data = create_house();
    door_data = create_door();
    ladder_data = create_ladder();

    _map_width = map_width;
    _map_height = map_height;
    _map_width_box = map_width_box;
    _map_height_box = map_height_box;

    for (int32_t i = 0; i <= _map_width_box / 64; i++) {
        auto _sub_map_ptr = std::make_shared<sub_map>();
        sub_maps.push_back(_sub_map_ptr);
    }

    ++count;
}

map::~map() {
    spdlog::trace("map destruction count:{0}", --count);
}

int32_t map::random_born() {
    int32_t x = utils::random(_map_width);
    int32_t count = 0;
    do {
        bool check = true;
        for (auto _x : born_point) {
            if (abs(x - _x) < 100) {
                check = false;
                break;
            }
        }

        if (!check) {
            x = utils::random(_map_width);
            count++;
        }
        else {
            break;
        }

        if (count > 3) {
            break;
        }

    } while (true);

    born_point.push_back(x);

    return x;
}

bool map::check_in_same_layer(bool is_in_house, int32_t _x_box, int32_t _y_box) {
    auto box_property = get_box_list(_x_box, _y_box);
    auto groundlayer = std::static_pointer_cast<map_element>(box_property->map_elem)->groundlayer;

    if (groundlayer == (int32_t)em_map_element_groundlayer::em_map_groundlayer) {
        if (is_in_house) {
            return false;
        }
        else {
            return true;
        }
    }
    else if (groundlayer == (int32_t)em_map_element_groundlayer::em_map_house) {
        if (is_in_house) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (groundlayer == (int32_t)em_map_element_groundlayer::em_map_shared) {
        return true;
    }

    return false;
}

void map::check_and_init(bool is_in_house, int32_t& x, int32_t& y) {
    do {
        x = x < 0 ? 0 : x;
        x = x > _map_width - 1 ? _map_width - 1 : x;

        auto x_box = x / 16;
        auto y_box = y / 16;

        bool is_same_layer = check_in_same_layer(is_in_house, x_box, y_box);
        auto house_box = get_house_box(x_box, y_box);
        auto box_property = get_box_list(x_box, y_box);
        spdlog::trace("check_and_init is_same_layer:{0}, house_property:{1}, box_property:{2}!", is_same_layer, house_box->map_elem->_property, box_property->map_elem->_property);
        if (!is_same_layer || box_property->map_elem->_property != em_map_element_property::em_map_map) {
            if (y_box <= 0) {
                break;
            }

            is_same_layer = check_in_same_layer(is_in_house, x_box, y_box - 1);
            box_property = get_box_list(x_box, y_box - 1);
            while (!is_same_layer || box_property->map_elem->_property != em_map_element_property::em_map_map) {
                y_box--;

                is_same_layer = check_in_same_layer(is_in_house, x_box, y_box - 1);
                box_property = get_box_list(x_box, y_box - 1);

            }

            y = y_box * 16;
            break;
        }
        else if (is_same_layer && box_property->map_elem->_property == em_map_element_property::em_map_map) {
            ++y_box;
            is_same_layer = check_in_same_layer(is_in_house, x_box, y_box);
            auto next_box_property = get_box_list(x_box, y_box);
            while (is_same_layer && next_box_property->map_elem->_property == em_map_element_property::em_map_map) {
                ++y_box;
                is_same_layer = check_in_same_layer(is_in_house, x_box, y_box);
                next_box_property = get_box_list(x_box, y_box);
            }

            y = y_box * 16;
            break;
        }

    } while (false);
}

void map::into_map(std::shared_ptr<role> _role) {
    auto pos = _role->_role_scene_handle->_obb->get_center_pos();
    auto x = pos.x;
    auto sub_map_index = get_sub_map_index(x);
    auto _sub_map = sub_maps[sub_map_index];
    _sub_map->into_sub_map(_role);
}

void map::leave_map(std::shared_ptr<role> _role) {
    auto pos = _role->_role_scene_handle->_obb->get_center_pos();
    auto x = pos.x;
    auto sub_map_index = get_sub_map_index(x);
    auto _sub_map = sub_maps[sub_map_index];
    _sub_map->leave_sub_map(_role);
}

int32_t map::get_sub_map_index(int32_t x) {
    auto x_box = x / 16;
    auto sub_map_index = x_box / 64;
    return sub_map_index;
}

std::shared_ptr<sub_map> map::get_sub_map(int32_t x) {
    auto x_box = x / 16;
    auto sub_map_index = x_box / 64;

    if (sub_map_index < 0 || sub_map_index >= sub_maps.size()) {
        return nullptr;
    }

    return sub_maps[sub_map_index];
}

std::vector<std::shared_ptr<sub_map> > map::get_field_sub_map(int32_t x) {
    auto x_box = x / 16;
    auto sub_map_index = x_box / 64;
    std::vector<std::shared_ptr<sub_map> > field_sub_map;
    for (auto field_sub_map_index : { sub_map_index - 1, sub_map_index, sub_map_index + 1 }) {
        if (field_sub_map_index < 0 || field_sub_map_index >= sub_maps.size()) {
            continue;
        }

        auto sub_map = sub_maps[field_sub_map_index];
        if (!sub_map) {
            continue;
        }
        field_sub_map.push_back(sub_map);
    }
    return field_sub_map;
}

std::vector<std::shared_ptr<role> > map::get_field_roles(int32_t x) {
    auto x_box = x / 16;
    auto sub_map_index = x_box / 64;
    std::vector<std::shared_ptr<role> > field_roles;
    for (auto field_sub_map_index : { sub_map_index - 1, sub_map_index, sub_map_index + 1 }) {
        if (field_sub_map_index < 0 || field_sub_map_index >= sub_maps.size()) {
            continue;
        }

        auto sub_map = sub_maps[field_sub_map_index];
        if (!sub_map) {
            continue;
        }
        for (auto _role : sub_map->field_roles) {
            //spdlog::trace("_role->uuid:{0}", _role->uuid);
            auto _role_ptr = _role.lock();
            if (!_role_ptr) {
                continue;
            }
            field_roles.push_back(_role_ptr);
        }
    }
    return field_roles;
}

std::vector<std::string> map::get_field_roles_uuid(int32_t x) {
    auto roles = get_field_roles(x);
    std::vector<std::string> roles_uuid;
    for (auto _role : roles) {
        if (!_role->check_sync()) {
            continue;
        }

        roles_uuid.push_back(_role->uuid);
    }
    return roles_uuid;
}

std::vector<std::shared_ptr<role> > map::get_range_field_roles(int32_t start_x, int32_t end_x) {
    start_x = start_x < 0 ? 0 : start_x;
    end_x = (int32_t)end_x > _map_width ? _map_width : end_x;
    auto sub_map_index_start = start_x / 16 / 64;
    auto sub_map_index_end = end_x / 16 / 64;

    auto little_index = (int32_t)(sub_map_index_start < sub_map_index_end ? sub_map_index_start : sub_map_index_end);
    auto big_index = (int32_t)(sub_map_index_start < sub_map_index_end ? sub_map_index_end : sub_map_index_start);
    spdlog::trace("little_index:{0},big_index:{1}", little_index, big_index);
    std::vector<int32_t> index_set;
    for (auto begin = little_index - 1; begin <= big_index + 1; begin++) {
        spdlog::trace("begin:{0}", begin);
        index_set.push_back(begin);
    }
    std::vector<std::shared_ptr<role> >  roles;
    for (auto field_sub_map_index : index_set) {
        spdlog::trace("field_sub_map_index:{0}", field_sub_map_index);
        if (field_sub_map_index < 0 || field_sub_map_index >= sub_maps.size()) {
            continue;
        }
        auto sub_map = sub_maps[field_sub_map_index];
        if (!sub_map) {
            continue;
        }
        for (auto _role : sub_map->field_roles) {
            //spdlog::trace("_role->uuid:{0}", _role->uuid);
            auto _role_ptr = _role.lock();
            if (!_role_ptr) {
                continue;
            }
            roles.push_back(_role_ptr);
        }
    }
    return roles;
}

std::vector<std::string> map::get_range_field_roles_uuid(int32_t start_x, int32_t end_x) {
    auto sub_map_index_start = start_x / 16 / 64;
    auto sub_map_index_end = end_x / 16 / 64;

    auto little_index = (int32_t)(sub_map_index_start < sub_map_index_end ? sub_map_index_start : sub_map_index_end);
    auto big_index = (int32_t)(sub_map_index_start < sub_map_index_end ? sub_map_index_end : sub_map_index_start);
    spdlog::trace("little_index:{0},big_index:{1}", little_index, big_index);
    std::vector<int32_t> index_set;
    for (auto begin = little_index - 1; begin <= big_index + 1; begin++) {
        spdlog::trace("begin:{0}", begin);
        index_set.push_back(begin);
    }
    std::vector<std::string>  roles_uuid;
    for (auto field_sub_map_index : index_set) {
        spdlog::trace("field_sub_map_index:{0}", field_sub_map_index);
        if (field_sub_map_index < 0 || field_sub_map_index >= sub_maps.size()) {
            continue;
        }
        auto sub_map = sub_maps[field_sub_map_index];
        if (!sub_map) {
            continue;
        }
        for (auto _role : sub_map->field_roles) {
            auto _role_ptr = _role.lock();
            if (!_role_ptr) {
                continue;
            }

            if (!_role_ptr->check_sync()) {
                continue;
            }

            //spdlog::trace("_role->uuid:{0}", _role->uuid);
            roles_uuid.push_back(_role_ptr->uuid);
        }
    }
    return roles_uuid;
}

std::vector<abelkhan::role_info> map::get_filed_roles_info(int32_t x) {
    auto roles = get_field_roles(x);
    std::vector<abelkhan::role_info> roles_info;
    for (auto _role : roles) {
        roles_info.push_back(_role->cs_info());
    }
    return roles_info;
}

std::shared_ptr<box> map::get_box_list(int32_t x, int32_t y) {
    spdlog::trace("x:{0}, y:{1}", x, y);

    if (x >= 0 && x < _map_width_box && y >= 0 && y < _map_height_box) {
        return map_data[(size_t)y * map_width_box + x];
    }

    return nullptr;
}

std::shared_ptr<box> map::get_house_box(int32_t x, int32_t y) {
    spdlog::trace("x:{0}, y:{1}", x, y);

    if (x >= 0 && x < _map_width_box && y >= 0 && y < _map_height_box) {
        return house_data[(size_t)y * map_width_box + x];
    }

    return nullptr;
}

int32_t map::hit_box(int32_t x, int32_t y, int32_t collision, int32_t hit_terrain, std::vector<std::shared_ptr<item> >& downitems) {
    auto _box = get_box_list(x, y);
    if (!_box) {
        return 0;
    }
    if (_box->map_elem->_property == em_map_element_property::em_map_empty) {
        spdlog::trace("be hit box is empty x:{0}, y:{1}", x, y);
        return 0;
    }

    auto _map_elem = std::static_pointer_cast<map_element>(_box->map_elem);
    if (collision < _map_elem->collision) {
        spdlog::trace("be hit box x:{0}, y:{1}, collision:{2}", x, y, _map_elem->collision);
        return 0;
    }

    _map_elem->hp -= hit_terrain;
    if (_map_elem->hp <= 0) {
        spdlog::trace("wreck_box x:{0},y:{1}", x, y);

        _map_elem->_property = em_map_element_property::em_map_wreck;

        auto _role_box = get_box_list(x, y + 1);
        for (auto _role : _role_box->role_list) {
            auto _role_ptr = _role.lock();
            if (!_role_ptr) {
                continue;
            }
            _role_ptr->_role_scene_handle->check_and_down();
        }

        auto _sub_map = get_sub_map(x * 16);
        for (auto _drop_item : _sub_map->item_box_list) {
            auto _drop_item_x = _drop_item->x / 16;
            auto _drop_item_y = _drop_item->y / 16;
            if (_drop_item_x == x && _drop_item_y == y + 1) {
                downitems.push_back(_drop_item);
            }
        }

        box_pos _box;
        _box.x_box = x;
        _box.y_box = y;
        _sub_map->be_wreck_box.push_back(_box);

        std::vector<abelkhan::wreck_box_info> _wreck_box_list;
        for (auto tiledmap : tiledmap_list) {
            if (x >= (int32_t)tiledmap.x_offset_begin && x < (int32_t)tiledmap.x_offset_end &&
                y >= (int32_t)tiledmap.y_offset_begin && y < (int32_t)tiledmap.y_offset_end)
            {
                auto tile_x = x - tiledmap.x_offset_begin;
                auto tile_y = tiledmap.y_offset_begin - y + 31;
                auto first_ = tiledmap.tiledmap_name.find('_');
                auto num_ = tiledmap.tiledmap_name.substr(first_ + 1);
                auto second_ = num_.find('_');
                auto y_str = num_.substr(0, second_);
                auto x_str = num_.substr(second_ + 1);

                abelkhan::wreck_box_info _wreck_box_info;
                _wreck_box_info.x = tile_x;
                _wreck_box_info.y = tile_y;
                _wreck_box_info.tiled_x = atoi(x_str.c_str());
                _wreck_box_info.tiled_y = atoi(y_str.c_str());
                _wreck_box_list.push_back(_wreck_box_info);
                break;
            }
        }
        _call_mng_handle->battle_client_caller->get_multicast(get_field_roles_uuid(x * 16))->be_wreck_box("groundLayer", _wreck_box_list);
    }
    
    return hit_terrain;
}

void map::check_item_dowm(std::shared_ptr<battle> _battle, std::vector<std::shared_ptr<item> > downitems) {
    std::vector<abelkhan::drop_item_info> _drop_item_list;
    for (auto _drop_item : downitems) {
        check_and_init(_drop_item->is_in_house, _drop_item->x, _drop_item->y);

        abelkhan::drop_item_info _drop_box_info;
        _drop_box_info.uuid = _drop_item->uuid;
        _drop_box_info.desc_id = _drop_item->desc_id;
        _drop_box_info.x = _drop_item->x;
        _drop_box_info.y = _drop_item->y;
        _drop_item_list.push_back(_drop_box_info);
    }
    _call_mng_handle->battle_client_caller->get_multicast(_battle->battle_field_uudis())->drop_item_list(_drop_item_list);
}


}
