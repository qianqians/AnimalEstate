/*
 * qianqians
 * 2020-1-22
 * battle
 * role_battle.h
 */

#include <vector>

#include <msec_time.h>
#include <memory>

#include <crossguid/guid.hpp>

#include "role_battle.h"
#include "role.h"
#include "battle.h"
#include "constant.h"
#include "team.h"
#include "random.h"
#include "../singleton.h"
#include "../call_mng.h"
#include "../json_config/json_config_mng.h"

namespace battle {

int bullet::count = 0;

bullet::bullet(bool _is_in_house, int32_t _pos_x, int32_t _pos_y, int32_t angle, std::shared_ptr<config::config> bullet_config, std::weak_ptr<role> _self_role) {
    is_expose = false;
    is_aim_shoot = false;
    is_in_house = _is_in_house;
    pos_x = _pos_x;
    pos_y = _pos_y;
    uuid = xg::newGuid().str();
    id = (int32_t)bullet_config->get_value_int("bullet");
    is_gravity = (int32_t)bullet_config->get_value_bool("gravity");
    collision = (int32_t)bullet_config->get_value_int("collision");
    range = (int32_t)bullet_config->get_value_int("range");
    blast_radius = (int32_t)bullet_config->get_value_int("blast_radius");
    attack = (int32_t)bullet_config->get_value_int("attack");
    range_damage = (int32_t)bullet_config->get_value_bool("range_damage");
    hit_terrain = (int32_t)bullet_config->get_value_int("hit_terrain");
    speed = (int32_t)bullet_config->get_value_int("speed");
    shoot_angle = (float)angle * constant::PI / 180;
    x_speed = (int32_t)(speed * cos(shoot_angle));
    y_speed = (int32_t)(speed * sin(shoot_angle));
    last_time = (uint64_t)_singleton_handle->_hub_handle->_timerservice->Tick;
    step_distance = 0;
    self_role = _self_role;

    spdlog::trace("bullet::bullet pos_x:{0},pos_y:{1}", pos_x, pos_y);

    ++count;
}

bullet::bullet(bool _is_in_house, int32_t _pos_x, int32_t _pos_y, int32_t _target_x, int32_t _target_y, std::shared_ptr<config::config> bullet_config, std::weak_ptr<role> _self_role) {
    is_expose = false;
    is_aim_shoot = true;
    target_x = _target_x;
    target_y = _target_y;
    is_in_house = _is_in_house;
    pos_x = _pos_x;
    pos_y = _pos_y;

    spdlog::trace("bullet::bullet pos_x:{0},pos_y:{1}, target_x:{2}, target_y:{3}", pos_x, pos_y, target_x, target_y);

    speed = (int32_t)bullet_config->get_value_int("speed");
    id = (int32_t)bullet_config->get_value_int("bullet");
    is_gravity = (int32_t)bullet_config->get_value_bool("gravity");
    collision = (int32_t)bullet_config->get_value_int("collision");
    range = (int32_t)bullet_config->get_value_int("range");
    blast_radius = (int32_t)bullet_config->get_value_int("blast_radius");
    attack = (int32_t)bullet_config->get_value_int("attack");
    range_damage = (int32_t)bullet_config->get_value_bool("range_damage");
    hit_terrain = (int32_t)bullet_config->get_value_int("hit_terrain");

    if (is_gravity) {
        auto target_distance = (int32_t)sqrt((target_y - pos_y) * (target_y - pos_y) + (target_x - pos_x) * (target_x - pos_x));
        x_speed = ((int32_t)speed * (target_x - pos_x)) / target_distance;
        y_speed = ((int32_t)speed * (target_y - pos_y)) / target_distance;

        auto t = ((float)(_target_x - pos_x)) / x_speed;
        auto __target_y_ = pos_y + y_speed * t + constant::gravity * t * t / 2;

        while (fabs(target_y - __target_y_) > 8) {
            y_speed = (int32_t)(((_target_y - pos_y) - constant::gravity * t * t / 2) / t);
            auto abs_x_speed = sqrt(speed * speed - y_speed * y_speed);
            x_speed = (int32_t)(x_speed < 0 ? -abs_x_speed : abs_x_speed);

            t = ((float)(_target_x - pos_x)) / x_speed;
            __target_y_ = pos_y + y_speed * t + constant::gravity * t * t / 2;
        }
    }
    else {
        auto target_distance = (int32_t)sqrt((target_y - pos_y) * (target_y - pos_y) + (target_x - pos_x) * (target_x - pos_x));
        x_speed = ((int32_t)speed * (target_x - pos_x)) / target_distance;
        y_speed = ((int32_t)speed * (target_y - pos_y)) / target_distance;
    }
    spdlog::trace("bullet::bullet x_speed:{0},y_speed:{1}", x_speed, y_speed);

    uuid = xg::newGuid().str();
    last_time = _singleton_handle->_hub_handle->_timerservice->Tick;
    step_distance = 0;
    self_role = _self_role;

    ++count;
}

void bullet::make_up(int32_t _gun_id, int range_addition, int speed_addition, int attack_addition, int radius, bool _range_damage) {
    gun_id = _gun_id;
    range = range * range_addition / 100;
    x_speed = x_speed * speed_addition / 100;
    y_speed = y_speed * speed_addition / 100;
    attack = attack * attack_addition / 100;
    blast_radius = radius;
    range_damage = _range_damage;
}

void bullet::send_fly_info(float _old_x, std::shared_ptr<map> _map) {
    auto filed_roles = _map->get_range_field_roles((int32_t)_old_x, pos_x);
    std::vector<std::string> hide_uuids;
    std::vector<std::string> filed_uuids;
    bool is_set_not_expose = false;
    auto box_x = (int32_t)(pos_x / 16);
    auto box_y = (int32_t)(pos_y / 16);
    auto house_box = _map->get_house_box(box_x, box_y);
    for (auto _role : filed_roles) {
        if (!_role->check_sync()) {
            continue;
        }

        auto dist = (int32_t)abs(pos_x - (int32_t)_role->_role_scene_handle->get_scene_x());
        if (dist > constant::view_dist) {
            continue;
        }

        if (_role->_role_battle_handle->is_in_house != is_in_house) {
            if (house_box != nullptr && house_box->map_elem->_property == em_map_element_property::em_map_map) {
                if (is_expose) {
                    is_set_not_expose = true;
                    hide_uuids.push_back(_role->uuid);
                }
                continue;
            }
            else {
                is_expose = true;
            }
        }
        if (_role->_role_battle_handle->is_in_house == is_in_house || _role->_role_scene_handle->check_at_wreck()) {
            filed_uuids.push_back(_role->uuid);
        }
    }
    if (is_set_not_expose) {
        is_expose = false;
    }
    _call_mng_handle->battle_client_caller->get_multicast(filed_uuids)->bullet_fly(
        uuid, gun_id, id, pos_x, pos_y, x_speed, y_speed);
    _call_mng_handle->battle_client_caller->get_multicast(hide_uuids)->bullet_hide(
        uuid, id, pos_x, pos_y);
}

bool bullet::blast(std::shared_ptr<role> _role, std::shared_ptr<map> _map, std::vector<std::string> filed_uuids, int32_t old_x, int32_t pos_x, int32_t pos_y, int32_t end_pos_x, int32_t end_pos_y) {
    spdlog::trace("blast pos_x:{0},pos_y:{1}", pos_x, pos_y);

    auto _battle = _role->_battle_handle.lock();
    if (!_battle) {
        return false;
    }

    auto x_box = (int32_t)(pos_x / 16);
    auto y_box = (int32_t)(pos_y / 16);
    std::vector<abelkhan::house_info> house_list;
    std::vector<abelkhan::house_info> elem_list;
    std::vector<abelkhan::role_info> behiters;
    std::vector<std::shared_ptr<item> > downitems;
    std::vector<std::shared_ptr<role> > behiterrole;
    auto x_box_begin = x_box - (int32_t)blast_radius;
    auto x_box_end = x_box + (int32_t)blast_radius;
    auto y_box_begin = y_box - (int32_t)blast_radius;
    auto y_box_end = y_box + (int32_t)blast_radius;
    spdlog::trace("blast x_box:{0},y_box:{1},blast_radius:{2}", x_box, y_box, blast_radius);
    spdlog::trace("blast x_box_begin:{0},x_box_end:{1}", x_box_begin, x_box_end);
    spdlog::trace("blast y_box_begin:{0},y_box_end:{1}", y_box_begin, y_box_end);
    for (int32_t _x_box = x_box_begin; _x_box <= x_box_end; _x_box++) {
        for (int32_t _y_box = y_box_begin; _y_box <= y_box_end; _y_box++) {
            spdlog::trace("blast _x_box:{0},_y_box:{1}", _x_box, _y_box);
            if (_x_box < 0 || _y_box < 0) {
                continue;
            }
            auto map_box = _map->get_box_list(_x_box, _y_box);
            if (!map_box) {
                continue;
            }
            auto house_box = _map->get_house_box(_x_box, _y_box);

            if (map_box->role_list.size() > 0) {
                for (auto _hit_role : map_box->role_list) {
                    auto _hit_role_ptr = _hit_role.lock();
                    if (!_hit_role_ptr) {
                        continue;
                    }

                    if (!_hit_role_ptr->is_live) {
                        continue;
                    }
                    if (_hit_role_ptr->id == _role->id) {
                        continue;
                    }
                    if (std::find(behiterrole.begin(), behiterrole.end(), _hit_role_ptr) != behiterrole.end()) {
                        continue;
                    }

                    if (_role->check_camp(_hit_role_ptr)) {
                        continue;
                    }

                    if (_hit_role_ptr->_role_battle_handle->be_ignore_attack) {
                        continue;
                    }

                    if (house_box->map_elem->_property != em_map_element_property::em_map_empty && house_box->map_elem->_property != em_map_element_property::em_map_wreck) {
                        if (_hit_role_ptr->_role_battle_handle->is_in_house != is_in_house) {
                            continue;
                        }
                    }

                    behiters.push_back(_hit_role_ptr->cs_info());
                    behiterrole.push_back(_hit_role_ptr);
                    if (!range_damage) {
                        break;
                    }
                }
            }

            do{
                if (is_aim_shoot && !is_in_house && house_box->map_elem->_property == em_map_element_property::em_map_map) {
                    auto _map_elem = std::static_pointer_cast<map_element>(house_box->map_elem);

                    if (collision < _map_elem->collision) {
                        spdlog::trace("be hit box x:{0}, y:{1}, collision:", _x_box, _y_box, _map_elem->collision);
                        break;
                    }

                    _map_elem->hp -= hit_terrain;
                    abelkhan::house_info house_elem;
                    house_elem.x = _x_box;
                    house_elem.y = _y_box;
                    house_elem.collision = _map_elem->collision;
                    house_elem.hp = _map_elem->hp;
                    house_list.push_back(house_elem);

                    if (_map_elem->hp <= 0) {
                        _map_elem->_property = em_map_element_property::em_map_wreck;

                        auto _sub_map = _map->get_sub_map(_x_box * 16);

                        box_pos _box;
                        _box.x_box = _x_box;
                        _box.y_box = _y_box;
                        _sub_map->be_wreck_house.push_back(_box);

                        std::vector<abelkhan::wreck_box_info> _wreck_box_list;
                        for (auto tiledmap : tiledmap_list) {
                            if (_x_box >= tiledmap.x_offset_begin && _x_box < tiledmap.x_offset_end &&
                                _y_box >= tiledmap.y_offset_begin && _y_box < tiledmap.y_offset_end)
                            {
                                auto tile_x = _x_box - tiledmap.x_offset_begin;
                                auto tile_y = tiledmap.y_offset_begin - _y_box + 31;
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
                        _call_mng_handle->battle_client_caller->get_multicast(_map->get_range_field_roles_uuid(old_x, pos_x))->be_wreck_box("houseLayer", _wreck_box_list);
                        break;
                    }
                }

                spdlog::trace("blast map_box _property:{0}", map_box->map_elem->_property);
                if (map_box->map_elem->_property == em_map_element_property::em_map_map) {
                    if (!is_in_house){
                        if (house_box->map_elem->_property != em_map_element_property::em_map_empty){
                            break;
                        }
                    }

                    abelkhan::house_info elem;
                    elem.x = _x_box;
                    elem.y = _y_box;
                    elem.collision = std::static_pointer_cast<map_element>(map_box->map_elem)->collision;
                    elem.hp = std::static_pointer_cast<map_element>(map_box->map_elem)->hp;
                    elem_list.push_back(elem);
                    _map->hit_box(_x_box, _y_box, collision, hit_terrain, downitems);
                }
            }while(false);
        }
    }
    _map->check_item_dowm(_battle, downitems);
    for (auto _role_tmp : behiterrole) {
        _role_tmp->_role_battle_handle->behit(attack, _role);
    }
    if (house_list.size() > 0) {
        _call_mng_handle->battle_client_caller->get_multicast(filed_uuids)->bullet_hit_house(uuid, id, pos_x, pos_y, house_list);
    }
    if (elem_list.size() > 0) {
        _call_mng_handle->battle_client_caller->get_multicast(filed_uuids)->bullet_hit_map_box(uuid, id, end_pos_x, end_pos_y, elem_list);
    }
    if (behiters.size() > 0) {
        _call_mng_handle->battle_client_caller->get_multicast(filed_uuids)->bullet_hit_elements(uuid, id, end_pos_x, end_pos_y, behiters);
    }

    if (house_list.size() > 0 || elem_list.size() > 0 || behiters.size() > 0) {
        return true;
    }
    return false;
}

bool bullet::tick_and_check_end() {
    spdlog::trace("tick_and_check_end begin!");

    if (is_in_house) {
        return tick_and_check_end_in_house();
    }
    else {
        return tick_and_check_end_out_house();
    }

    spdlog::trace("tick_and_check_end end!");

    return false;
}

std::vector<std::string> bullet::get_filed_uuids(std::shared_ptr<map> _map, std::shared_ptr<box> _house_box, int32_t old_pos_x) {
    auto filed_roles = _map->get_range_field_roles(old_pos_x, pos_x);
    std::vector<std::string> filed_uuids;
    for (auto _role : filed_roles) {
        if (_role->_role_battle_handle->is_in_house != is_in_house) {
            if (_house_box != nullptr && _house_box->map_elem->_property == em_map_element_property::em_map_map) {
                continue;
            }
        }
        if (!_role->check_sync()) {
            continue;
        }
        filed_uuids.push_back(_role->uuid);
    }

    return filed_uuids;
}

bool bullet::check_end_in_house(std::shared_ptr<role> _role, std::shared_ptr<map> _map, int32_t _old_pos_x, float step_time) {
    auto old_pox_x = pos_x;
    auto old_pox_y = pos_y;

    auto x = pos_x + x_speed * step_time;
    if (is_gravity) {
        auto y = pos_y + y_speed * step_time + constant::gravity * step_time * step_time / 2;
        y_speed += (int32_t)(constant::gravity * step_time);
        pos_y = (int32_t)y;
    }
    else {
        auto y = pos_y + y_speed * step_time;
        pos_y = (int32_t)y;
    }

    pos_x = (int32_t)x;
    pos_x = pos_x < 0 ? 0 : pos_x;
    pos_y = pos_y < 0 ? 0 : pos_y;
    auto box_x = (int32_t)(pos_x / 16);
    auto box_y = (int32_t)(pos_y / 16);
    auto _house_box = _map->get_house_box(box_x, box_y);

    auto x_box = (int32_t)(pos_x / 16);
    auto y_box = (int32_t)(pos_y / 16);
    if (x_box < 0 || y_box < 0) {
        _call_mng_handle->battle_client_caller->get_multicast(get_filed_uuids(_map, _house_box, old_pox_x))->bullet_hit_miss(uuid, id, pos_x, pos_y);
        spdlog::trace("tick_and_check_end_in_house bullet_hit_miss!");
        return true;
    }
    auto map_box = _map->get_box_list(x_box, y_box);
    if (!map_box) {
        _call_mng_handle->battle_client_caller->get_multicast(get_filed_uuids(_map, _house_box, old_pox_x))->bullet_hit_miss(uuid, id, pos_x, pos_y);
        spdlog::trace("tick_and_check_end_in_house bullet_hit_miss!");
        return true;
    }
    if (map_box->check_exist_enemy(_role)) {
        if (blast(_role, _map, get_filed_uuids(_map, _house_box, old_pox_x), _old_pos_x, pos_x, pos_y, old_pox_x, old_pox_y)) {
            spdlog::trace("tick_and_check_end_in_house bullet_hit_player!");
            return true;
        }
    }
    if (map_box->map_elem->_property == em_map_element_property::em_map_map) {
        if (blast(_role, _map, get_filed_uuids(_map, _house_box, old_pox_x), _old_pos_x, pos_x, pos_y, old_pox_x, old_pox_y)) {
            spdlog::trace("tick_and_check_end_in_house bullet_hit_elements!");
            return true;
        }
    }
    if (is_aim_shoot && (fabs(pos_x - target_x) <= 8 && fabs(pos_y - target_y) <= 8)) {
        if (blast(_role, _map, get_filed_uuids(_map, _house_box, old_pox_x), _old_pos_x, pos_x, pos_y, old_pox_x, old_pox_y)) {
            spdlog::trace("tick_and_check_end_in_house bullet_hit_target!");
        }
        else {
            _call_mng_handle->battle_client_caller->get_multicast(get_filed_uuids(_map, _house_box, old_pox_x))->bullet_hit_miss(uuid, id, pos_x, pos_y);
        }
        return true;
    }

    auto _step_distance = (int32_t)(sqrt(((double)x - old_pox_x) * (x - old_pox_x) + ((double)pos_y - old_pox_y) * ((double)pos_y - old_pox_y)));
    step_distance += _step_distance;
    if (step_distance >= range) {
        _call_mng_handle->battle_client_caller->get_multicast(get_filed_uuids(_map, _house_box, old_pox_x))->bullet_hit_miss(uuid, id, pos_x, pos_y);
        spdlog::trace("tick_and_check_end_in_house step_distance bullet_hit_miss!");
        return true;
    }

    return false;
}

bool bullet::tick_and_check_end_in_house() {
    spdlog::trace("tick_and_check_end_in_house begin!");
    
    auto _role = self_role.lock();
    if (!_role) {
        return false;
    }

    auto _battle = _role->_battle_handle.lock();
    if (!_battle) {
        return false;
    }
    auto _map = _battle->_map_handle;

    auto tick_time = (float)(_singleton_handle->_hub_handle->_timerservice->Tick - last_time) / 1000;
    last_time = _singleton_handle->_hub_handle->_timerservice->Tick;
    speed = (int32_t)(sqrt(x_speed * x_speed + y_speed * y_speed));
    auto step_time = (float)(8.0 / speed);
    auto rounds = (int32_t)(tick_time / step_time);
    auto last_round_time = tick_time - step_time * rounds;
    auto _old_pos_x = pos_x;
    for (auto step = 0; step < rounds; step++) {
        auto _check = check_end_in_house(_role, _map, _old_pos_x, step_time);
        if (_check) {
            return true;
        }
    }
    auto _check = check_end_in_house(_role, _map, _old_pos_x, last_round_time);

    if (!_check && is_gravity) {
        send_fly_info((float)_old_pos_x, _map);
    }

    spdlog::trace("tick_and_check_end_in_house end!");

    return _check;
}

bool bullet::check_end_out_house(std::shared_ptr<role> _role, std::shared_ptr<map> _map, int32_t _old_pos_x, float step_time) {
    auto old_pox_x = pos_x;
    auto old_pox_y = pos_y;

    int32_t x = (int32_t)(pos_x + x_speed * step_time);
    if (is_gravity) {
        int32_t y = (int32_t)(pos_y + y_speed * step_time + constant::gravity * step_time * step_time / 2);
        y_speed += (int32_t)(constant::gravity * step_time);
        pos_y = y;
    }
    else {
        int32_t y = (int32_t)(pos_y + y_speed * step_time);
        pos_y = y;
    }

    pos_x = x;
    pos_x = pos_x < 0 ? 0 : pos_x;
    pos_y = pos_y < 0 ? 0 : pos_y;
    auto x_box = (int32_t)(pos_x / 16);
    auto y_box = (int32_t)(pos_y / 16);
    auto _house_box = _map->get_house_box(x_box, y_box);
    if (x_box < 0 || y_box < 0) {
        _call_mng_handle->battle_client_caller->get_multicast(get_filed_uuids(_map, _house_box, old_pox_x))->bullet_hit_miss(uuid, id, pos_x, pos_y);
        spdlog::trace("tick_and_check_end_out_house bullet_hit_miss!");
        return true;
    }
    auto map_box = _map->get_box_list(x_box, y_box);
    if (!map_box) {
        _call_mng_handle->battle_client_caller->get_multicast(get_filed_uuids(_map, _house_box, old_pox_x))->bullet_hit_miss(uuid, id, pos_x, pos_y);
        spdlog::trace("tick_and_check_end_out_house bullet_hit_miss!");
        return true;
    }
    if (map_box->check_exist_enemy(_role)) {
        if (blast(_role, _map, get_filed_uuids(_map, _house_box, old_pox_x), _old_pos_x, pos_x, pos_y, old_pox_x, old_pox_y)) {
            spdlog::trace("tick_and_check_end_out_house bullet_hit_player!");
            return true;
        }
    }
    if (map_box->map_elem->_property == em_map_element_property::em_map_map && (_house_box == nullptr || _house_box->map_elem->_property != em_map_element_property::em_map_map)) {
        if (blast(_role, _map, get_filed_uuids(_map, _house_box, old_pox_x), _old_pos_x, pos_x, pos_y, old_pox_x, old_pox_y)) {
            spdlog::trace("tick_and_check_end_out_house bullet_hit_elements!");
            return true;
        }
    }
    if (is_aim_shoot && (fabs(pos_x - target_x) <= 8 && fabs(pos_y - target_y) <= 8)) {
        if (blast(_role, _map, get_filed_uuids(_map, _house_box, old_pox_x), _old_pos_x, pos_x, pos_y, old_pox_x, old_pox_y)) {
            spdlog::trace("tick_and_check_end_out_house bullet_hit_target");
        }
        else {
            _call_mng_handle->battle_client_caller->get_multicast(get_filed_uuids(_map, _house_box, old_pox_x))->bullet_hit_miss(uuid, id, pos_x, pos_y);
        }
        return true;
    }

    auto _step_distance = (int32_t)(sqrt((x - old_pox_x) * (x - old_pox_x) + ((double)pos_y - old_pox_y) * ((double)pos_y - old_pox_y)));
    step_distance += _step_distance;
    if (step_distance >= range) {
        _call_mng_handle->battle_client_caller->get_multicast(get_filed_uuids(_map, _house_box, old_pox_x))->bullet_hit_miss(uuid, id, pos_x, pos_y);
        spdlog::trace("tick_and_check_end_out_house step_distance bullet_hit_miss!");
        return true;
    }

    return false;
}

bool bullet::tick_and_check_end_out_house() {
    spdlog::trace("tick_and_check_end_out_house begin!");

    auto _role = self_role.lock();
    if (!_role) {
        return false;
    }

    auto _battle = _role->_battle_handle.lock();
    if (!_battle) {
        return false;
    }
    auto _map = _battle->_map_handle;

    auto tick_time = (float)(_singleton_handle->_hub_handle->_timerservice->Tick - last_time) / 1000;
    last_time = _singleton_handle->_hub_handle->_timerservice->Tick;
    speed = (int32_t)(sqrt(x_speed * x_speed + y_speed * y_speed));
    auto step_time = (float)(8.0 / speed);
    auto rounds = (int32_t)(tick_time / step_time);
    auto last_round_time = tick_time - step_time * rounds;
    auto _old_pos_x = pos_x;
    for (auto step = 0; step < rounds; step++) {
        auto _check = check_end_out_house(_role, _map, _old_pos_x, step_time);
        if (_check) {
            return true;
        }
    }
    auto _check = check_end_out_house(_role, _map, _old_pos_x, last_round_time);

    if (!_check && is_gravity) {
        send_fly_info((float)_old_pos_x, _map);
    }

    spdlog::trace("tick_and_check_end_out_house end!");

    return _check;
}

int role_battle::count = 0;

role_battle::role_battle(abelkhan::role_battle_base_info db_battle, std::shared_ptr<role> _role) {
    spdlog::trace("Init role_battle begin!");
    
    is_in_house = false;
    self_role = _role;
    title = (int32_t)db_battle.title;
    score = (int32_t)db_battle.score;
    
    base_hp = 1000;
    total_hp = 1000;
    hp = 1000;

    base_defense = 10;
    defense = 10;
    
    angle = 0.0f;

    _gun = nullptr;
    _bullets_num = 0;

    _rpg_gun = nullptr;
    _rpg_bullets_num = 0;

    _grenade_num = 0;
    _grenade_cd_time = 0;

    random_shoot_direction();

    ++count;
    
    spdlog::trace("Init role_battle begin!");
}

role_battle::role_battle(std::shared_ptr<role> _role) {
    spdlog::trace("Init robot role_battle begin!");

    is_in_house = false;
    self_role = _role;
    title = 1;
    score = 1;

    base_hp = 100;
    total_hp = 100;
    hp = 100;

    base_defense = 10;
    defense = 10;

    angle = 0.0f;

    _gun = nullptr;
    _bullets_num = 0;

    _rpg_gun = nullptr;
    _rpg_bullets_num = 0;

    _grenade_num = 0;
    _grenade_cd_time = 0;

    random_shoot_direction();

    ++count;

    spdlog::trace("Init robot role_battle begin!");
}

void role_battle::random_shoot_direction() {
    auto i = utils::random(2);
    if (i == 0) {
        _shoot_direction = 1;
    }
    else {
        _shoot_direction = -1;
    }
}

abelkhan::role_battle_info role_battle::cs_info() {
    abelkhan::role_battle_info info;
    info.title = title;
    info.score = score;
    info.hp = hp;
    if (_gun == nullptr) {
        info.gun = -1;
    }
    else {
        info.gun = _gun->desc_id;
    }
    info.bullets_num = _bullets_num;
    if (_rpg_gun == nullptr) {
        info.rpg_gun = -1;
    }
    else {
        info.rpg_gun = _rpg_gun->desc_id;
    }
    info.rpg_bullets_num = _rpg_bullets_num;
    info.grenade_num = _grenade_num;
    info.angle = angle;
    for (auto equip : _equip) {
        abelkhan::equip equip_info;
        equip_info.uuid = equip.second->uuid;
        equip_info.desc_id = equip.second->desc_id;
        info.equip_info.push_back(equip_info);
    }
    return info;
}

void role_battle::aim(float _angle) {
    angle = _angle;

    spdlog::trace("aim angle:{0}", angle);

    auto _role = self_role.lock();
    if (!_role) {
        return;
    }

    if (!_gun) {
        return;
    }

    _call_mng_handle->battle_client_caller->get_multicast(_role->_role_scene_handle->get_role_field())->role_aim_status(_role->id, _gun->desc_id, (int64_t)angle);

    if (cos(angle * constant::PI / 180) > 0) {
        _shoot_direction = 1;
    }
    else {
        _shoot_direction = -1;
    }
    _shoot_direction_time = _singleton_handle->_hub_handle->_timerservice->Tick;
    ntf_shoot_direction();
}

std::shared_ptr<gun> role_battle::change_gun(std::shared_ptr<gun> _gun_ptr) {
    auto _gun_ret = _gun;
    _gun = _gun_ptr;
    return _gun_ret;
}

std::shared_ptr<equip> role_battle::change_equip(std::shared_ptr<equip> _equip_ptr) {
    auto _role = self_role.lock();
    if (!_role) {
        return nullptr;
    }

    auto _equip_ret = _equip[_equip_ptr->equip_type];
    _equip[_equip_ptr->equip_type] = _equip_ptr;

    int32_t diff_hp = total_hp - hp;
    total_hp = base_hp;
    defense = base_defense;

    for (auto it : _equip) {
        if (it.second) {
            total_hp += it.second->hp;
            defense += it.second->defense;
        }
    }
    hp = total_hp - diff_hp;
    _call_mng_handle->battle_client_caller->get_multicast(_role->_role_scene_handle->get_role_field())->role_hp_change(_role->id, hp);

    return _equip_ret;
}

void role_battle::bullet_shoot(std::shared_ptr<config::config> gun_config, std::shared_ptr<config::config> bullet_config) {
    auto _role = self_role.lock();
    if (!_role) {
        return;
    }

    auto _battle = _role->_battle_handle.lock();
    if (!_battle) {
        return;
    }

    auto _map = _battle->_map_handle;

    auto pos = _role->_role_scene_handle->get_shoot_pos();
    auto pos_x = pos.x;
    auto pos_y = pos.y;
    auto _bullet_shared = std::make_shared<bullet>(is_in_house, (int32_t)pos_x, (int32_t)pos_y, (int32_t)angle, bullet_config, self_role);

    auto range_addition = (int)gun_config->get_value_int("range");
    auto speed_addition = (int)gun_config->get_value_int("speed");
    auto attack_addition = (int)gun_config->get_value_int("attack");
    auto radius = (int)gun_config->get_value_int("radius");
    auto range_damage = gun_config->get_value_bool("range_damage");
    _bullet_shared->make_up(_gun->desc_id, range_addition, speed_addition, attack_addition, radius, range_damage);

    bullets.push_back(_bullet_shared);

    _bullet_shared->send_fly_info((float)pos_x, _map);
}

void role_battle::ntf_shoot_direction() {
    spdlog::trace("ntf_shoot_direction begin!");

    auto _role = self_role.lock();
    if (!_role) {
        return;
    }

    _call_mng_handle->battle_client_caller->get_multicast(_role->_role_scene_handle->get_role_field())->role_orientation_status(_role->id, _shoot_direction);

    spdlog::trace("ntf_shoot_direction end!");
}

void role_battle::check_shoot_direction(float _angle) {
    _shoot_direction_time = _singleton_handle->_hub_handle->_timerservice->Tick;
    if (cos(_angle * constant::PI / 180) > 0) {
        if (_shoot_direction == 1) {
            return;
        }
        _shoot_direction = 1;
    }
    else {
        if (_shoot_direction == -1) {
            return;
        }
        _shoot_direction = -1;
    }
    ntf_shoot_direction();
}

void role_battle::check_shoot_direction(int32_t pos_x, int32_t target_x) {
    _shoot_direction_time = _singleton_handle->_hub_handle->_timerservice->Tick;
    if ((target_x - pos_x) > 0) {
        if (_shoot_direction == 1) {
            return;
        }
        _shoot_direction = 1;
    }
    else {
        if (_shoot_direction == -1) {
            return;
        }
        _shoot_direction = -1;
    }
    ntf_shoot_direction();
}

void role_battle::shoot() {
    spdlog::trace("shoot begin!");

    auto _role = self_role.lock();
    if (!_role) {
        return;
    }
    
    if (!_gun) {
        return;
    }

    auto _now_tick = (uint64_t)msec_time();
    if (_gun->cd_time > _now_tick) {
        return;
    }

    if (_bullets_num <= 0){
        return;
    }
    _bullets_num--;

    check_shoot_direction(angle);

    auto gun_config = json_config::_json_config_mng->json_configs["gun"]->get_value_dict(std::to_string(_gun->desc_id));
    auto bullet_config = json_config::_json_config_mng->json_configs["bullet"]->get_value_dict(std::to_string(gun_config->get_value_int("bullet")));
    bullet_shoot(gun_config, bullet_config);

    _gun->cd_time = (uint64_t)(_now_tick + _gun->desc_cd_time * 0.9);
    _call_mng_handle->battle_client_caller->get_client(_role->uuid)->role_gun_info(_gun->uuid, _bullets_num);

    //bullet_tick();

    spdlog::trace("shoot end!");
}

void role_battle::rpg_shoot(int64_t angle) {
    spdlog::trace("rpg_shoot begin!");

    auto _role = self_role.lock();
    if (!_role) {
        return;
    }

    auto _battle = _role->_battle_handle.lock();
    if (!_battle) {
        return;
    }

    auto _map = _battle->_map_handle;

    auto _now_tick = (uint64_t)msec_time();
    if (_rpg_gun == nullptr || _rpg_gun->cd_time > _now_tick) {
        return;
    }

    if (_rpg_bullets_num <= 0) {
        return;
    }
    _rpg_bullets_num--;

    check_shoot_direction((float)angle);

    auto gun_config = json_config::_json_config_mng->json_configs["rpg"]->get_value_dict(std::to_string(_rpg_gun->desc_id));
    auto bullet_config = json_config::_json_config_mng->json_configs["bullet"]->get_value_dict(std::to_string(gun_config->get_value_int("bullet")));
    auto pos = _role->_role_scene_handle->get_shoot_pos();
    auto pos_x = pos.x;
    auto pos_y = pos.y;
    auto _bullet_shared = std::make_shared<bullet>(is_in_house, (int32_t)pos_x, (int32_t)pos_y, (int32_t)angle, bullet_config, self_role);
    bullets.push_back(_bullet_shared);

    _rpg_gun->cd_time = (uint64_t)(_now_tick + _rpg_gun->desc_cd_time * 0.9);
    _call_mng_handle->battle_client_caller->get_client(_role->uuid)->role_gun_info(_rpg_gun->uuid, _rpg_bullets_num);

    //bullet_tick();
    _bullet_shared->send_fly_info((float)pos_x, _map);

    spdlog::trace("rpg_shoot end!");
}

void role_battle::rpg_aim_shoot(int64_t target_x, int64_t target_y) {
    spdlog::trace("rpg_aim_shoot begin!");

    auto _role = self_role.lock();
    if (!_role) {
        return;
    }

    auto _battle = _role->_battle_handle.lock();
    if (!_battle) {
        return;
    }

    auto _map = _battle->_map_handle;

    auto _now_tick = (uint64_t)msec_time();
    if (_rpg_gun == nullptr || _rpg_gun->cd_time > _now_tick) {
        return;
    }

    if (_rpg_bullets_num <= 0) {
        return;
    }
    _rpg_bullets_num--;

    auto pos = _role->_role_scene_handle->get_shoot_pos();
    auto pos_x = pos.x;
    auto pos_y = pos.y;

    check_shoot_direction(pos_x, (int32_t)target_x);

    auto gun_config = json_config::_json_config_mng->json_configs["rpg"]->get_value_dict(std::to_string(_rpg_gun->desc_id));
    auto bullet_config = json_config::_json_config_mng->json_configs["bullet"]->get_value_dict(std::to_string(gun_config->get_value_int("bullet")));
    auto _bullet_shared = std::make_shared<bullet>(is_in_house, (int32_t)pos_x, (int32_t)pos_y, (int32_t)target_x, (int32_t)target_y, bullet_config, self_role);
    bullets.push_back(_bullet_shared);

    _rpg_gun->cd_time = (uint64_t)(_now_tick + _rpg_gun->desc_cd_time * 0.9);
    _call_mng_handle->battle_client_caller->get_client(_role->uuid)->role_gun_info(_rpg_gun->uuid, _rpg_bullets_num);

    //bullet_tick();
    _bullet_shared->send_fly_info((float)pos_x, _map);

    spdlog::trace("rpg_aim_shoot end!");
}

void role_battle::grenade_shoot(float angle) {
    spdlog::trace("grenade_shoot begin!");

    auto _role = self_role.lock();
    if (!_role) {
        return;
    }

    auto _battle = _role->_battle_handle.lock();
    if (!_battle) {
        return;
    }

    auto _map = _battle->_map_handle;

    auto _now_tick = (uint64_t)msec_time();
    if (_grenade_cd_time > _now_tick) {
        return;
    }

    if (_grenade_num <= 0) {
        return;
    }
    _grenade_num--;

    check_shoot_direction(angle);

    auto bullet_config = json_config::_json_config_mng->json_configs["bullet"]->get_value_dict(std::to_string(constant::grenade_desc_id));
    auto pos = _role->_role_scene_handle->get_shoot_pos();
    auto pos_x = pos.x;
    auto pos_y = pos.y;
    auto _bullet_shared = std::make_shared<bullet>(is_in_house, (int32_t)pos_x, (int32_t)pos_y, (int32_t)angle, bullet_config, self_role);
    bullets.push_back(_bullet_shared);

    _grenade_cd_time = (uint64_t)(_now_tick + constant::grenade_cd * 0.9);
    _call_mng_handle->battle_client_caller->get_client(_role->uuid)->role_grenade_num(_grenade_num);

    //bullet_tick();
    _bullet_shared->send_fly_info((float)pos_x, _map);

    spdlog::trace("grenade_shoot end!");
}

void role_battle::grenade_aim_shoot(int64_t target_x, int64_t target_y) {
    spdlog::trace("grenade_aim_shoot begin!");

    auto _role = self_role.lock();
    if (!_role) {
        return;
    }

    auto _battle = _role->_battle_handle.lock();
    if (!_battle) {
        return;
    }

    auto _map = _battle->_map_handle;

    auto _now_tick = (uint64_t)msec_time();
    if (_grenade_cd_time > _now_tick) {
        return;
    }

    if (_grenade_num <= 0) {
        return;
    }
    _grenade_num--;

    auto pos = _role->_role_scene_handle->get_shoot_pos();
    auto pos_x = pos.x;
    auto pos_y = pos.y;

    check_shoot_direction(pos_x, (int32_t)target_x);

    auto bullet_config = json_config::_json_config_mng->json_configs["bullet"]->get_value_dict(std::to_string(constant::grenade_desc_id));
    
    auto _bullet_shared = std::make_shared<bullet>(is_in_house, (int32_t)pos_x, (int32_t)pos_y, (int32_t)target_x, (int32_t)target_y, bullet_config, self_role);
    bullets.push_back(_bullet_shared);

    _grenade_cd_time = (uint64_t)(_now_tick + constant::grenade_cd * 0.9);
    _call_mng_handle->battle_client_caller->get_client(_role->uuid)->role_grenade_num(_grenade_num);

    //bullet_tick();
    _bullet_shared->send_fly_info((float)pos_x, _map);

    spdlog::trace("grenade_aim_shoot end!");

}

int32_t role_battle::behit(int32_t attack, std::shared_ptr<role> attacker) {
    int32_t _real_attack = (int32_t)attack - defense;
    int32_t min_attack = attack / 10;
    if (_real_attack < (int32_t)min_attack) {
        _real_attack = min_attack;
    }
    hurt((int32_t)_real_attack, attacker);

    return (int32_t)_real_attack;
}

bool role_battle::hurt(int32_t _hurt, std::shared_ptr<role> attacker) {
    auto _role = self_role.lock();
    if (!_role) {
        return false;
    }

    if (!_role->is_live) {
        return false;
    }

    if (be_invincible) {
        return false;
    }

    hp -= _hurt;
    _role->check_hurt_break_buff();
    _call_mng_handle->battle_client_caller->get_multicast(_role->_role_scene_handle->get_role_field())->role_hp_change(_role->id, hp);

    if (hp <= 0) {
        if (attacker) {
            attacker->_kill_list.push_back(self_role);
        }

        _role->role_dead();
        auto _team = _role->_team_handle.lock();
        if (!_team) {
            return false;
        }

        return _team->check_fall();
    }

    return false;
}

void role_battle::bullet_tick() {
    spdlog::trace("bullet_tick begin!");

    for (auto it = 0; it < bullets.size(); ) {
        if (bullets[it]->tick_and_check_end()) {
            bullets[it] = bullets.back();
            bullets.pop_back();
        }
        else {
            ++it;
        }
    }

    spdlog::trace("bullet_tick end!");
}

}
