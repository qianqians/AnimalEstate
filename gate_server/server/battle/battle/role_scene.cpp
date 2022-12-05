/*
 * qianqians
 * 2020-1-22
 * battle
 * role_scene.cpp
 */
#include <cmath>
#include <memory>
#include "role.h"
#include "robot.h"
#include "role_scene.h"
#include "skill.h"
#include "constant.h"
#include "map.h"
#include "map_data.h"
#include "../singleton.h"
#include "../call_mng.h"

namespace battle {

int obb::count = 0;

int role_scene::count = 0;

role_scene::role_scene(std::weak_ptr<role> _role_handle, int32_t x, int32_t y) {
    _role = _role_handle;
    _obb = std::make_shared<obb>(x, y, x + constant::box_width, y + constant::box_height);
    direction = 0;
    move_speed = 0;
    jump_status = 0;
    jump_height = 0;
    jump_speed = 0;

    timetmp = _singleton_handle->_hub_handle->_timerservice->Tick;

    ++count;
}

role_scene::~role_scene() {
    spdlog::trace("role_scene destruction count:{0}", --count);
}

abelkhan::role_scene_info role_scene::cs_info() {
    auto pos = _obb->get_center_pos();
    abelkhan::role_scene_info info;
    info.x = pos.x;
    info.y = pos.y;
    info.direction = direction;
    auto _role_ptr = _role.lock();
    if (_role_ptr) {
        info.shoot_direction = _role_ptr->_role_battle_handle->_shoot_direction;
    }
    return info;
}

void role_scene::check_and_init() {
    spdlog::trace("check_and_init begin!");

    auto _map = _map_handle.lock();
    if (!_map) {
        return;
    }

    auto _role_ptr = _role.lock();
    if (!_role_ptr) {
        return;
    }

    c_ladder = _map->ladder_data.end();

    auto pos = _obb->get_center_pos();
    auto x = pos.x;
    auto y = pos.y;
    _map->check_and_init(_role_ptr->_role_battle_handle->is_in_house, x, y);
    _obb->set_center_pos(x, y);

    auto new_sub_map_index = _map->get_sub_map_index(x);
    auto new_role_sub_map = _map->sub_maps[new_sub_map_index];
    new_role_sub_map->into_sub_map(_role);

    auto x_box_new = (x / 16);
    auto y_down_box_new = (y / 16);
    auto y_up_box_new = (_obb->up_right_y / 16);
    for (auto i = y_down_box_new; i < y_up_box_new; i++) {
        auto box_new = _map->get_box_list(x_box_new, i);
        box_new->role_list.push_back(_role);
    }
    
    spdlog::trace("check_and_init end!");
}

void role_scene::check_and_down() {
    spdlog::trace("check_and_down begin!");

    auto _map = _map_handle.lock();
    if (!_map) {
        return;
    }

    auto _role_ptr = _role.lock();
    if (!_role_ptr) {
        return;
    }

    auto pos = _obb->get_center_pos();
    auto x = pos.x;
    auto y = pos.y;
    do {
        auto x_box = x / 16;
        auto y_box = y / 16;

        bool is_same_layer = _map->check_in_same_layer(_role_ptr->_role_battle_handle->is_in_house, x_box, y_box);
        auto box_property = _map->get_box_list(x_box, y_box);
        if (!is_same_layer || box_property->map_elem->_property != em_map_element_property::em_map_map) {
            if (y_box <= 0) {
                break;
            }

            is_same_layer = _map->check_in_same_layer(_role_ptr->_role_battle_handle->is_in_house, x_box, y_box - 1);
            auto next_box_property = _map->get_box_list(x_box, y_box - 1);
            if (!is_same_layer || next_box_property->map_elem->_property != em_map_element_property::em_map_map) {
                set_jump_down();
            }

            break;
        }

    } while (false);

    spdlog::trace("check_and_down end!");
}

bool role_scene::check_ladder_move(int32_t& _x, int32_t& _y) {
    spdlog::trace("check_ladder_move begin _x:{0}, _y:{1}!", _x, _y);

    if (ladder_state == 0) {
        return false;
    }

    auto _map = _map_handle.lock();
    if (!_map) {
        return false;
    }

    if (c_ladder == _map->ladder_data.end()) {
        return false;
    }

    do {
        auto _time = (float)(_singleton_handle->_hub_handle->_timerservice->Tick - timetmp);
        spdlog::trace("check_ladder_move Tick:{0}, timetmp:{1}, _time:{2}!", _singleton_handle->_hub_handle->_timerservice->Tick, timetmp, _time);
        if (ladder_state == -1) {
            _y = (int32_t)(_y + constant::ladder_move_speed * _time * -1 / 1000);
            c_ladder = check_ladder_down(_x, _y);
        }
        else if (ladder_state == 1) {
            _y = (int32_t)(_y + constant::ladder_move_speed * _time / 1000);
            c_ladder = check_ladder_up(_x, _y);
        }
        
        if (c_ladder != _map->ladder_data.end() && (direction == -1 || direction == 1)) {
            _x = (int32_t)(_x + (float)constant::move_speed * _time * direction / 1000);
            if (ladder_state == -1 && _y <= (c_ladder->y_min + 16)) {
                _y = c_ladder->y_min;
                c_ladder = _map->ladder_data.end();
                break;
            }
            else if (ladder_state == 1 && _y >= (c_ladder->y_max - 16)){
                _y = c_ladder->y_max;
                c_ladder = _map->ladder_data.end();
                break;
            }

            if (_x < c_ladder->x_min) {
                _x = c_ladder->x_min;
                direction = 0;
            }
            else if (_x > c_ladder->x_max) {
                _x = c_ladder->x_max;
                direction = 0;
            }
            break;
        }

    } while (0);

    if (c_ladder == _map->ladder_data.end()) {
        ladder_state = 0;
    }

    spdlog::trace("check_ladder_move set _x:{0}, _y:{1}!", _x, _y);
    _obb->set_center_pos(_x, _y);

    spdlog::trace("check_ladder_move end!");

    return c_ladder != _map->ladder_data.end();
}

void role_scene::check_shoot_direction(std::shared_ptr<role> _self) {
    spdlog::trace("check_and_move ntf_shoot_direction!");
    if ((_singleton_handle->_hub_handle->_timerservice->Tick - _self->_role_battle_handle->_shoot_direction_time) > 1000) {
        if (_self->_role_battle_handle->_shoot_direction != direction) {
            _self->_role_battle_handle->_shoot_direction = direction;
            _self->_role_battle_handle->ntf_shoot_direction();
        }
    }
}

void role_scene::check_move_out_house() {
    spdlog::trace("check_move_out_house begin!");

    do {
        auto _map = _map_handle.lock();
        if (!_map) {
            break;
        }

        auto _role_ptr = _role.lock();
        if (!_role_ptr) {
            break;
        }

        auto pos = _obb->get_center_pos();
        auto _x_box = pos.x / 16;
        auto _y_box = pos.y / 16;
        auto _house = _map->get_house_box(_x_box, _y_box + 1);
        int ret = (int)in_out_house_state::em_not_door;
        if (_house->map_elem->_property == em_map_element_property::em_map_empty) {
            if (_role_ptr->_role_battle_handle->is_in_house) {
                ret = (int)in_out_house_state::em_out_house;
                _role_ptr->_role_battle_handle->is_in_house = false;
                clear_house_range();
            }
        }

        if (ret != (int)in_out_house_state::em_not_door) {
            auto x = pos.x;
            auto y = pos.y;
            spdlog::trace("check_move_out_house is_in_house:{0}!", _role_ptr->_role_battle_handle->is_in_house);
            _map->check_and_init(_role_ptr->_role_battle_handle->is_in_house, x, y);
            _obb->set_center_pos(x, y);
            sync_in_out_house_field(_role_ptr, _map, ret);
        }

    } while (false);

    spdlog::trace("check_move_out_house end!");
}

bool role_scene::check_and_x(std::shared_ptr<role> _role_ptr, std::shared_ptr<map> _map, int32_t& _x, int32_t& _y, float current_move_speed, float step_time) {
    auto x = (int32_t)(_x + (float)current_move_speed * direction * step_time);
    spdlog::trace("check_and_move x:{0}, current_move_speed:{1}, step_time:{2}", x, current_move_speed, step_time);
    x = x < 0 ? 0 : x;
    x = x > (int32_t)(_map->_map_width - 1) ? (_map->_map_width - 1) : x;
    auto x_box = ((int32_t)(x / 16));
    auto y_box = ((int32_t)(_y / 16));
    auto box_property = _map->get_box_list(x_box, y_box);
    bool is_same_layer = _map->check_in_same_layer(_role_ptr->_role_battle_handle->is_in_house, x_box, y_box);
    if (is_same_layer && box_property->map_elem->_property == em_map_element_property::em_map_map) {
        auto box_property1 = _map->get_box_list(x_box, y_box + 1);
        is_same_layer = _map->check_in_same_layer(_role_ptr->_role_battle_handle->is_in_house, x_box, y_box + 1);
        if (is_same_layer && box_property1->map_elem->_property == em_map_element_property::em_map_map) {
            return true;
        }
        else {
            _y = (++y_box) * 16;
        }
    }
    _x = x;

    return false;
}

void role_scene::check_and_move() {
    spdlog::trace("check_and_move begin!");

    if (direction == 0 && jump_status == 0 && ladder_state == 0) {
        timetmp = _singleton_handle->_hub_handle->_timerservice->Tick;
        return;
    }

    spdlog::trace("check_and_move _role.lock!");
    auto _role_ptr = _role.lock();
    if (!_role_ptr) {
        return;
    }

    spdlog::trace("check_and_move _map_handle.lock!");
    auto _map = _map_handle.lock();
    if (!_map) {
        return;
    }

    check_shoot_direction(_role_ptr);

    spdlog::trace("check_and_move get_center_pos begin!");
    auto pos = _obb->get_center_pos();
    auto _x = pos.x;
    auto _y = pos.y;
    spdlog::trace("check_and_move get_center_pos end!");

    auto x_box_old = _x / 16;
    auto y_down_box_old = _y / 16;
    auto y_up_box_old = _obb->up_right_y / 16;

    spdlog::trace("check_and_move start move!");
    do {
        if (check_ladder_move(_x, _y)) {
            break;
        }

        check_and_y();

        auto pos = _obb->get_center_pos();
        _x = pos.x;
        _y = pos.y;
        auto x = _x;
        spdlog::trace("check_and_move _x:{0},_y:{1}", _x, _y);

        if (move_speed != 0) {
            auto current_move_speed = 0;
            if ((cos(_role_ptr->_role_battle_handle->angle) * direction) > 0) {
                current_move_speed = move_speed;
            }
            else {
                current_move_speed = (int32_t)(move_speed * 0.8);
            }
            current_move_speed = current_move_speed * move_speed_rate / 100;

            auto _time = (float)(_singleton_handle->_hub_handle->_timerservice->Tick - timetmp) / 1000;
            auto step_time = 8.0 / abs(current_move_speed);
            auto rounds = (int32_t)(_time / step_time);
            auto last_round_time = _time - step_time * rounds;
            bool is_end = false;
            for (auto step = 0; step < rounds; step++) {
                if (check_and_x(_role_ptr, _map, x, _y, (float)current_move_speed, (float)step_time)) {
                    is_end = true;
                    break;
                }
            }
            if (!is_end) {
                check_and_x(_role_ptr, _map, x, _y, (float)current_move_speed, (float)last_round_time);
            }
        }

        auto now_sub_map_index = _map->get_sub_map_index(_x);
        auto new_sub_map_index = _map->get_sub_map_index(x);
        if (now_sub_map_index != new_sub_map_index) {
            auto now_sub_map = _map->get_field_sub_map(_x);
            auto new_sub_map = _map->get_field_sub_map(x);
            check_change_sub_map(now_sub_map, new_sub_map);

            auto now_role_sub_map = _map->sub_maps[now_sub_map_index];
            now_role_sub_map->leave_sub_map(_role);
            auto new_role_sub_map = _map->sub_maps[new_sub_map_index];
            new_role_sub_map->into_sub_map(_role);
        }

        _x = x;
        auto x_box = ((int32_t)(_x / 16));
        auto y_box = ((int32_t)(_y / 16));
        if (y_box == 0) {
            break;
        }
        if (jump_status != 1) {
            auto foot_box_property = _map->get_box_list(x_box, y_box - 1);
            bool is_same_layer = _map->check_in_same_layer(_role_ptr->_role_battle_handle->is_in_house, x_box, y_box - 1);
            if (!foot_box_property) {
                spdlog::trace("foot_box_property is null");
                _y = y_box * 16;
                set_jump_done();
            }
            else if (is_same_layer && foot_box_property->map_elem->_property == em_map_element_property::em_map_map) {
                foot_box_property = _map->get_box_list(x_box, y_box);
                is_same_layer = _map->check_in_same_layer(_role_ptr->_role_battle_handle->is_in_house, x_box, y_box);
                while (is_same_layer && foot_box_property->map_elem->_property == em_map_element_property::em_map_map) {
                    foot_box_property = _map->get_box_list(x_box, ++y_box);
                    is_same_layer = _map->check_in_same_layer(_role_ptr->_role_battle_handle->is_in_house, x_box, y_box);
                }
                spdlog::trace("foot_box_property not empty");
                _y = y_box * 16;
                set_jump_done();
            }
            else {
                spdlog::trace("foot_box_property is empty, role down!");
                set_jump_down();
            }
        }

    } while (0);
    timetmp = _singleton_handle->_hub_handle->_timerservice->Tick;
    _obb->set_center_pos(_x, _y);

    auto x_box_new = (_x / 16);
    auto y_down_box_new = (_y / 16);
    auto y_up_box_new = (_obb->up_right_y / 16);
    check_sync_house_wreak_field(_role_ptr, _map, x_box_old, x_box_new, y_down_box_old, y_down_box_new, y_up_box_old, y_up_box_new);

    check_move_out_house();

    _role_ptr->check_pickup();
    send_role_move_state();

    spdlog::trace("check_and_move end!");
}

void role_scene::check_sync_house_wreak_field(std::shared_ptr<role> _self, std::shared_ptr<map> _map, int32_t x_box_old, int32_t x_box_new, int32_t y_down_box_old, int32_t y_down_box_new, int32_t y_up_box_old, int32_t y_up_box_new) {
    if (x_box_old != x_box_new || y_down_box_old != y_down_box_new || y_up_box_old != y_up_box_new) {
        bool old_in_view = false;
        bool new_in_view = false;
        for (auto i = y_down_box_old; i < y_up_box_old; i++) {
            auto box_old = _map->get_box_list(x_box_old, i);
            for (auto index = box_old->role_list.begin(); index != box_old->role_list.end(); ) {
                if (index->lock() == _self) {
                    index = box_old->role_list.erase(index);

                    auto house_box_old = _map->get_house_box(x_box_old, i);
                    if (house_box_old->map_elem->_property != em_map_element_property::em_map_map && _self->_role_battle_handle->is_in_house) {
                        old_in_view = true;
                    }
                    break;
                }
                else {
                    index++;
                }
            }
        }

        for (auto i = y_down_box_new; i < y_up_box_new; i++) {
            auto box_new = _map->get_box_list(x_box_new, i);
            box_new->role_list.push_back(_role);

            auto house_box_new = _map->get_house_box(x_box_new, i);
            if (house_box_new->map_elem->_property != em_map_element_property::em_map_map && _self->_role_battle_handle->is_in_house) {
                new_in_view = true;
            }
        }

        auto _role_list = _map->get_field_roles(get_scene_x());
        if (!old_in_view && new_in_view && _self->_role_battle_handle->is_in_house) {
            std::vector<std::string> into_field_uuids;
            std::vector<abelkhan::role_info> into_filed_role_info;
            for (auto _role_tmp : _role_list) {
                if (_role_tmp->_role_battle_handle->is_in_house) {
                    continue;
                }
                if (!_role_tmp->is_live) {
                    continue;
                }
                if (_role_tmp->check_sync()) {
                    into_field_uuids.push_back(_role_tmp->uuid);
                    _self->_role_skill_handle->check_and_send_skill_info_to_role(_self, _role_tmp);
                }
                into_filed_role_info.push_back(_role_tmp->cs_info());
                _role_tmp->_role_skill_handle->check_and_send_skill_info_to_role(_role_tmp, _self);
            }
            std::vector<abelkhan::role_info>  _role_into_info;
            _role_into_info.push_back(_self->cs_info());
            _call_mng_handle->battle_client_caller->get_multicast(into_field_uuids)->field_info(_role_into_info);
            _call_mng_handle->battle_client_caller->get_multicast({ _self->uuid })->field_info(into_filed_role_info);
        }
        else if (old_in_view && !new_in_view && _self->_role_battle_handle->is_in_house) {
            std::vector<std::string> leave_field_uuids;
            std::vector<std::string> leave_filed_role_id;
            for (auto _role_tmp : _role_list) {
                if (_role_tmp->_role_battle_handle->is_in_house) {
                    continue;
                }
                if (!_role_tmp->is_live) {
                    continue;
                }
                if (_role_tmp->check_sync()) {
                    leave_field_uuids.push_back(_role_tmp->uuid);
                }
                leave_filed_role_id.push_back(_role_tmp->id);
            }
            std::vector<std::string> _role_leave_id;
            _role_leave_id.push_back(_self->id);
            _call_mng_handle->battle_client_caller->get_multicast(leave_field_uuids)->leave_field_info(_role_leave_id);
            _call_mng_handle->battle_client_caller->get_multicast({ _self->uuid })->leave_field_info(leave_filed_role_id);
        }
    }
}

void role_scene::check_and_set_squat_obb(int32_t x_box, int32_t y_down_box_old, int32_t y_up_box_old, int32_t y_down_box_new, int32_t y_up_box_new) {
    auto _map = _map_handle.lock();
    if (!_map) {
        return;
    }

    if (y_down_box_old != y_down_box_new || y_up_box_old != y_up_box_new) {
        for (auto i = y_down_box_old; i < y_up_box_old; i++) {
            auto box_old = _map->get_box_list(x_box, i);
            for (auto index = box_old->role_list.begin(); index != box_old->role_list.end(); index++) {
                if (index->lock() == _role.lock()) {
                    box_old->role_list.erase(index);
                    break;
                }
            }
        }

        for (auto i = y_down_box_new; i < y_up_box_new; i++) {
            auto box_new = _map->get_box_list(x_box, i);
            box_new->role_list.push_back(_role);
        }
    }
}

struct pos role_scene::get_shoot_pos() {
    return _obb->get_shoot_pos();
}

int32_t role_scene::get_scene_x() {
    auto pos = _obb->get_center_pos();
    return pos.x;
}

void role_scene::force_set_direction(int32_t _direction) {
    direction = _direction;
    if (direction != 0) {
        if (is_squat) {
            move_speed = constant::squat_move_speed;
        }
        else {
            move_speed = constant::move_speed;
        }
    }
    else {
        move_speed = 0;
    }
}

void role_scene::set_direction(int32_t _direction) {
    if (jump_status != 0 && direction != 0) {
        return;
    }

    auto self = _role.lock();
    if (!self) {
        return;
    }
    auto roll_it = self->_role_skill_handle->role_skill_list.find("roll");
    if (roll_it != self->_role_skill_handle->role_skill_list.end()) {
        roll_it->second->set_direction(_direction);
    }

    direction = _direction;
    if (direction != 0) {
        if (is_squat) {
            move_speed = constant::squat_move_speed;
        }
        else {
            move_speed = constant::move_speed;
        }
    }
    else {
        move_speed = 0;
    }
}

void role_scene::set_ladder(int32_t _ladder_state) {
    auto _role_ptr = _role.lock();
    if (!_role_ptr) {
        return;
    }

    auto _map = _map_handle.lock();
    if (!_map) {
        return;
    }

    spdlog::trace("set_ladder _ladder_state:{0}, is_in_house:{1}, begin!", _ladder_state, _role_ptr->_role_battle_handle->is_in_house);

    auto pos = _obb->get_center_pos();

    if (_ladder_state == -1 && _role_ptr->_role_battle_handle->is_in_house) {
        spdlog::trace("set_ladder check_ladder_down!");
        c_ladder = check_ladder_down(pos.x, pos.y);
        if (c_ladder != _map->ladder_data.end()) {
            ladder_state = _ladder_state;
        }
    }
    else if (_ladder_state == 1 && _role_ptr->_role_battle_handle->is_in_house) {
        spdlog::trace("set_ladder check_ladder_up!");
        c_ladder = check_ladder_up(pos.x, pos.y);
        if (c_ladder != _map->ladder_data.end()) {
            ladder_state = _ladder_state;
        }
    }
    else if (_ladder_state == 0) {
        ladder_state = _ladder_state;
    }

    spdlog::trace("set_ladder end!");
}

//0 停止移动 1 右 2 右下 3 下 4 左下 5 左 6 左上 7 上 8 右上
void role_scene::set_rocker(int32_t rocker) {
    spdlog::trace("set_rocker rocker:{0}, begin!", rocker);

    auto _map = _map_handle.lock();
    if (!_map) {
        return;
    }

    if (rocker == 0) {
        set_squat(false);
        set_direction(0);
        set_ladder(0);
        send_role_move_state();
    }
    else if (rocker == 1) {
        set_squat(false);
        set_direction(1);
        set_ladder(0);
    }
    else if (rocker == 2) {
        set_ladder(-1); 
        if (c_ladder == _map->ladder_data.end()) {
            set_squat(true);
        }
        set_direction(1);
    }
    else if (rocker == 3) {
        set_ladder(-1);
        if (c_ladder == _map->ladder_data.end()) {
            set_squat(true);
        }
        set_direction(0);
    }
    else if (rocker == 4) {
        set_ladder(-1);
        if (c_ladder == _map->ladder_data.end()) {
            set_squat(true);
        }
        set_direction(-1);
    }
    else if (rocker == 5) {
        set_squat(false);
        set_direction(-1);
        set_ladder(0);
    }
    else if (rocker == 6) {
        set_squat(false);
        set_direction(-1);
        set_ladder(1);
    }
    else if (rocker == 7) {
        set_squat(false);
        set_direction(0);
        set_ladder(1);
    }
    else if (rocker ==8) {
        set_squat(false);
        set_direction(1);
        set_ladder(1);
    }
    last_rocker = rocker;

    check_and_move();

    spdlog::trace("set_rocker end!");
}

void role_scene::set_jump() {
    do {
        auto _map = _map_handle.lock();
        if (!_map) {
            return;
        }

        auto self = _role.lock();
        if (!self) {
            return;
        }

        if (is_twostepjump) {
            spdlog::trace("set_jump is_twostepjump!");
            is_twostepjump = false;
            self->_role_skill_handle->set_skill_status("twostepjump");
            self->_role_skill_handle->send_skill_info(self);
            break;
        }

        if (jump_status != 0) {
            return;
        }

        c_ladder = _map->ladder_data.end();
        ladder_state = 0;

        auto it = self->_role_skill_handle->role_skill_list.find("twostepjump");
        if (it != self->_role_skill_handle->role_skill_list.end()) {
            it->second->do_skill();
        }

    } while (false);

    jump_status = 1;
    jump_speed = constant::jump_speed;
    jump_height = 0;
    check_and_move();
}

void role_scene::set_squat(bool _squat) {
    if (is_squat == _squat) {
        return;
    }
    is_squat = _squat;

    if (direction != 0) {
        if (is_squat) {
            move_speed = constant::squat_move_speed;
        }
        else {
            move_speed = constant::move_speed;
        }
    }
    else {
        move_speed = 0;
    }
    
    auto old_y_down_box = _obb->down_left_y / 16;
    auto old_y_up_box = _obb->up_right_y / 16;
    if (is_squat) {
        _obb->squat_down();
    }
    else {
        _obb->stand_up();
    }
    auto x_box = (_obb->down_left_x + _obb->up_right_x) / 2 / 16;
    auto new_y_down_box = _obb->down_left_y / 16;
    auto new_y_up_box = _obb->up_right_y / 16;
    check_and_set_squat_obb(x_box, old_y_down_box, old_y_up_box, new_y_down_box, new_y_up_box);

    //send_role_move_state();
    //check_and_move();
}

std::vector<std::string> role_scene::get_role_field() {
    std::vector<std::string> field_list;
    do {
        auto pos = _obb->get_center_pos();
        auto x = pos.x;

        auto _map = _map_handle.lock();
        if (!_map) {
            break;
        }

        auto _role_ptr = _role.lock();
        if (!_role_ptr) {
            break;
        }

        auto _role_field_list = _map->get_field_roles(x);
        for (auto _role_tmp : _role_field_list) {
            if (_role_tmp->_role_battle_handle->is_in_house != _role_ptr->_role_battle_handle->is_in_house) {
                continue;
            }

            if (!_role_tmp->check_sync()) {
                continue;
            }

            field_list.push_back(_role_tmp->uuid);
        }
    } while (false);

    return field_list;
}

void role_scene::send_role_move_state() {
    auto _map = _map_handle.lock();
    if (!_map) {
        return;
    }

    auto _role_ptr = _role.lock();
    if (!_role_ptr) {
        return;
    }

    auto current_move_speed = 0;
    if (direction != 0) {
        if ((cos(_role_ptr->_role_battle_handle->angle) * direction) > 0) {
            current_move_speed = move_speed;
        }
        else {
            current_move_speed = (int32_t)(move_speed * 0.8);
        }
    }
    current_move_speed = current_move_speed * move_speed_rate / 100;
    auto current_jump_speed = 0;
    if (jump_status != 0) {
        current_jump_speed = abs(jump_speed);
    }

    auto pos = _obb->get_center_pos();
    auto x = pos.x;
    auto y = pos.y;
    auto field_roles = _map->get_field_roles(x);
    std::vector<std::string> field_uuids;
    for(auto _role_tmp : field_roles) {
        if (_role_tmp->_role_battle_handle->is_in_house != _role_ptr->_role_battle_handle->is_in_house) {
            auto x_box = ((int32_t)(x / 16));
            auto y_box = ((int32_t)(y / 16));     
            auto house_box = _map->get_house_box(x_box, y_box);
            if (house_box->map_elem->_property == em_map_element_property::em_map_map) {
                continue;
            }
        }
        if (!_role_tmp->check_sync()) {
            continue;
        }
        auto dist = (int32_t)(abs((int32_t)x - (int32_t)_role_tmp->_role_scene_handle->get_scene_x()));
        if (dist > constant::view_dist) {
            continue;
        }

        field_uuids.push_back(_role_tmp->uuid);
    }
    _call_mng_handle->battle_client_caller->get_multicast(field_uuids)->role_move_status(
        _role_ptr->id, x, y, is_squat,
        direction, current_move_speed, jump_status, current_jump_speed, 
        ladder_state, constant::ladder_move_speed,
        _singleton_handle->_hub_handle->_timerservice->Tick);
}

void role_scene::check_change_sub_map(std::vector<std::shared_ptr<sub_map> > now_sub_map, std::vector<std::shared_ptr<sub_map> > new_sub_map) {
    auto _map = _map_handle.lock();
    if (!_map) {
        return;
    }

    auto _role_ptr = _role.lock();
    if (!_role_ptr) {
        return;
    }

    std::vector<std::shared_ptr<sub_map> > _leave_sub_map;
    for (auto _sub_map : now_sub_map) {
        if (std::find(new_sub_map.begin(), new_sub_map.end(), _sub_map) == new_sub_map.end()) {
            _leave_sub_map.push_back(_sub_map);
        }
    }
    if (_leave_sub_map.size() > 0) {
        std::vector<std::shared_ptr<role> > leave_field_roles;
        std::vector<std::string> leave_field_drop_item_uuid;
        for (auto _sub_map : _leave_sub_map) {
            for (auto _role : _sub_map->field_roles) {
                auto _role_ptr = _role.lock();
                if (!_role_ptr) {
                    continue;
                }
                if (!_role_ptr->is_live) {
                    continue;
                }
                leave_field_roles.push_back(_role_ptr);
            }

            for (auto _drop_item : _sub_map->item_box_list) {
                leave_field_drop_item_uuid.push_back(_drop_item->uuid);
            }
        }
        std::vector<std::string> leave_field_uuids;
        std::vector<std::string> leave_filed_role_id;
        for (auto _leave_role : leave_field_roles) {
            if (_leave_role->check_sync()) {
                leave_field_uuids.push_back(_leave_role->uuid);
            }
            leave_filed_role_id.push_back(_leave_role->id);
        }
        std::vector<std::string> _role_leave_id;
        _role_leave_id.push_back(_role_ptr->id);
        _call_mng_handle->battle_client_caller->get_multicast(leave_field_uuids)->leave_field_info(_role_leave_id);
        _call_mng_handle->battle_client_caller->get_multicast({ _role_ptr->uuid })->leave_field_info(leave_filed_role_id);
        _call_mng_handle->battle_client_caller->get_multicast({ _role_ptr->uuid })->leave_field_info(leave_field_drop_item_uuid);
    }

    std::vector<std::shared_ptr<sub_map> > into_sub_map;
    for (auto _sub_map : new_sub_map) {
        if (std::find(now_sub_map.begin(), now_sub_map.end(), _sub_map) == now_sub_map.end()) {
            into_sub_map.push_back(_sub_map);
        }
    }
    if (into_sub_map.size() > 0) {
        std::vector<std::shared_ptr<role> > into_field_roles;
        for (auto _sub_map : into_sub_map) {
            for (auto _role : _sub_map->field_roles) {
                auto _role_ptr = _role.lock();
                if (!_role_ptr) {
                    continue;
                }
                into_field_roles.push_back(_role_ptr);
            }
        }
        std::vector<std::string> into_field_uuids;
        std::vector<abelkhan::role_info> into_filed_role_info;
        for (auto _role_handle : into_field_roles) {
            //if (!_role_handle->is_live) {
            //    continue;
            //}

            auto pos = _role_handle->_role_scene_handle->_obb->get_center_pos();
            auto x_box = (int32_t)(pos.x / 16);
    		auto y_box = (int32_t)(pos.y / 16);
			auto house_box = _map->get_house_box(x_box, y_box);
			if (house_box->map_elem->_property != em_map_element_property::em_map_empty) {
                if (_role_ptr->_role_battle_handle->is_in_house != _role_handle->_role_battle_handle->is_in_house) {
                    continue;
                }
            }
            
            if (_role_handle->check_sync()) {
                into_field_uuids.push_back(_role_handle->uuid);
            }

            if (_role_handle->is_live) {
                into_filed_role_info.push_back(_role_handle->cs_info());
            }
        }
        std::vector<abelkhan::role_info> _role_self_info;
        _role_self_info.push_back(_role_ptr->cs_info());
        _call_mng_handle->battle_client_caller->get_multicast(into_field_uuids)->field_info(_role_self_info);
        _call_mng_handle->battle_client_caller->get_multicast({ _role_ptr->uuid })->field_info(into_filed_role_info);

        std::vector<abelkhan::wreck_box_info> _wreck_box_list;
        for (auto _sub_map : into_sub_map) {
            for (auto wreck_box : _sub_map->be_wreck_box) {
                auto x = wreck_box.x_box;
                auto y = wreck_box.y_box;
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
                    }
                }
            }
        }
        _call_mng_handle->battle_client_caller->get_multicast({ _role_ptr->uuid })->be_wreck_box("groundLayer", _wreck_box_list);

        std::vector<abelkhan::wreck_box_info> _wreck_house_list;
        for (auto _sub_map : into_sub_map) {
            for (auto wreck_box : _sub_map->be_wreck_house) {
                auto x = wreck_box.x_box;
                auto y = wreck_box.y_box;
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

                        abelkhan::wreck_box_info _wreck_house_info;
                        _wreck_house_info.x = tile_x;
                        _wreck_house_info.y = tile_y;
                        _wreck_house_info.tiled_x = atoi(x_str.c_str());
                        _wreck_house_info.tiled_y = atoi(y_str.c_str());
                        _wreck_house_list.push_back(_wreck_house_info);
                    }
                }
            }
        }
        _call_mng_handle->battle_client_caller->get_multicast({ _role_ptr->uuid })->be_wreck_box("houseLayer", _wreck_house_list);
    }
}

bool role_scene::check_and_y_down(std::shared_ptr<role> _role_ptr, std::shared_ptr<map> _map, int32_t& _x, int32_t& _y, float step_time) {
    auto y = (int32_t)((float)_y + abs(jump_speed) * step_time * jump_status + constant::gravity * step_time * step_time / 2);
    jump_speed += (int32_t)(constant::gravity * step_time);

    y = y < 0 ? 0 : y;
    if (y <= 0) {
        _y = 0;
        set_jump_done();
        return true;
    }

    auto x_box = (_x / 16);
    auto y_box = (int32_t)(y / 16);
    auto next_box_property = _map->get_box_list(x_box, y_box);
    bool is_same_layer = _map->check_in_same_layer(_role_ptr->_role_battle_handle->is_in_house, x_box, y_box);
    if (is_same_layer && next_box_property->map_elem->_property == em_map_element_property::em_map_map) {
        _y = (y_box + 1) * 16;
        set_jump_done();
        return true;
    }
    _y = y;

    return false;
}

bool role_scene::check_up_map_stop(std::shared_ptr<role> _role_ptr, std::shared_ptr<map> _map, int32_t _x) {
    auto x_box = (_x / 16);
    auto y_box = (int32_t)(_obb->up_right_y / 16);
    auto next_box_property = _map->get_box_list(x_box, y_box);
    bool is_same_layer = _map->check_in_same_layer(_role_ptr->_role_battle_handle->is_in_house, x_box, y_box);
    if (is_same_layer && next_box_property->map_elem->_property == em_map_element_property::em_map_map) {
        return true;
    }
    return false;
}

bool role_scene::check_and_y_up(std::shared_ptr<role> _role_ptr, std::shared_ptr<map> _map, int32_t& _x, int32_t& _y, float step_time) {
    if (check_up_map_stop(_role_ptr, _map, _x)) {
        set_jump_down();
        spdlog::trace("check_and_y, jump_status jump em_map_map end jump change:{0}", jump_status);
        return true;
    }
    
    auto _jump_height = (int32_t)(abs(jump_speed) * step_time * jump_status + constant::gravity * step_time * step_time / 2);
    jump_speed += (int32_t)(constant::gravity * step_time);
    auto y = (int32_t)(_y + _jump_height);
    jump_height += _jump_height;

    spdlog::trace("Tick:{0}, timetmp:{1}", _singleton_handle->_hub_handle->_timerservice->Tick, timetmp);

    _y = y;
    if (jump_height >= constant::max_jump_height) {
        set_jump_down();
        spdlog::trace("check_and_y, jump_status max_jump_height end jump change:{0}", jump_status);
        return true;
    }
    if (jump_speed <= 0) {
        set_jump_down();
        spdlog::trace("check_and_y, jump_status jump_speed == 0 jump change:{0}", jump_status);
        return true;
    }

    return false;
}

void role_scene::set_jump_down() {
    jump_height = 0;
    jump_status = -1;
    jump_speed = -(int32_t)constant::jump_speed;
}

void role_scene::set_jump_done() {
    auto _self = _role.lock();
    if (!_self) {
        return;
    }

    jump_status = 0;
    jump_speed = 0;
    is_twostepjump = false;

    _self->_role_skill_handle->clear_skill_status();
}

void role_scene::check_and_y() {
    spdlog::trace("check_and_y begin!");

    if (jump_status == 0) {
        return;
    }

    auto pos = _obb->get_center_pos();
    auto _x = pos.x;
    auto _y = pos.y;
    do {
        auto _map = _map_handle.lock();
        if (!_map) {
            break;
        }

        auto _role_ptr = _role.lock();
        if (!_role_ptr) {
            break;
        }

        if (jump_status == -1) {
            spdlog::trace("check_and_y, jump_status:{0}", jump_status);

            auto x_box = (_x / 16);
            auto y_box = (_y / 16);

            bool is_same_layer = _map->check_in_same_layer(_role_ptr->_role_battle_handle->is_in_house, x_box, y_box);
            auto house_box = _map->get_house_box(x_box, y_box);
            auto box_property = _map->get_box_list(x_box, y_box);
            spdlog::trace("is_same_layer:{0}, house_box _property:{1}, box_property:{2}", is_same_layer, house_box->map_elem->_property, box_property->map_elem->_property);
            if (is_same_layer && (box_property->map_elem->_property == em_map_element_property::em_map_map)) {
                do {
                    box_property = _map->get_box_list(x_box, ++y_box);
                    house_box = _map->get_house_box(x_box, y_box);
                    is_same_layer = _map->check_in_same_layer(_role_ptr->_role_battle_handle->is_in_house, x_box, y_box);
                    spdlog::trace("is_same_layer:{0}, house_box _property:{1}, box_property:{2}", is_same_layer, house_box->map_elem->_property, box_property->map_elem->_property);

                } while (is_same_layer && (box_property->map_elem->_property == em_map_element_property::em_map_map));
                
                _y = y_box * 16;
                set_jump_done();
            }
            else {
                spdlog::trace("check_and_y, jump down begin!");

                auto _time = (float)(_singleton_handle->_hub_handle->_timerservice->Tick - timetmp) / 1000;
                auto step_time = 8.0 / abs(jump_speed);
                auto rounds = (int32_t)(_time / step_time);
                auto last_round_time = _time - step_time * rounds;
                spdlog::trace("check_and_y, jump down jump_speed:{0}, _time{1}", jump_speed, _time);
                spdlog::trace("jump_status down step_time:{0}, rounds:{1}, last_round_time:{2}", step_time, rounds, last_round_time);
                bool is_end = false;
                for (auto step = 0; step < rounds; step++) {
                    if (check_and_y_down(_role_ptr, _map, _x, _y, (float)step_time)) {
                        is_end = true;
                        break;
                    }
                }
                if (!is_end) {
                    check_and_y_down(_role_ptr, _map, _x, _y, (float)last_round_time);
                }
            }
        }
        else if (jump_status == 1) {
            spdlog::trace("check_and_y, jump_status:{0}", jump_status);

            auto _time = (float)(_singleton_handle->_hub_handle->_timerservice->Tick - timetmp) / 1000;
            spdlog::trace("_time:{0}, jump_speed:{1}", _time, jump_speed);
            auto step_time = 8.0 / abs(jump_speed);
            auto rounds = (int32_t)(_time / step_time);
            auto last_round_time = _time - step_time * rounds;
            spdlog::trace("jump_status up step_time:{0}, rounds:{1}, last_round_time:{2}", step_time, rounds, last_round_time);
            bool is_end = false;
            for (auto step = 0; step < rounds; step++) {
                if (check_and_y_up(_role_ptr, _map, _x, _y, (float)step_time)) {
                    is_end = true;
                    break;
                }
            }
            if (!is_end) {
                check_and_y_up(_role_ptr, _map, _x, _y, (float)last_round_time);
            }
        }
    } while (false);
    
    _obb->set_center_pos(_x, _y);

    spdlog::trace("check_and_y end! _x:{0}, _y:{1}", _x, _y);
}

int role_scene::in_out_house() {
    spdlog::trace("in_out_house begin!");

    auto _map = _map_handle.lock();
    if (!_map) {
        return (int)in_out_house_state::em_not_door;
    }

    auto _role_ptr = _role.lock();
    if (!_role_ptr) {
        return (int)in_out_house_state::em_not_door;
    }

    int ret = (int)in_out_house_state::em_not_door;

    auto pos = _obb->get_center_pos();
    auto _x = pos.x;
    auto _y = pos.y;
    auto x_box = (_x / 16);
    auto y_box = (_y / 16);

    auto house_box = _map->get_house_box(x_box, y_box);
    if (house_box->map_elem->_property == em_map_element_property::em_map_wreck) {
        ret = wreck_in_out_house();
    }
    else {
        ret = door_in_out_house();
    }

    if (ret != (int)in_out_house_state::em_not_door) {
        _map->check_and_init(_role_ptr->_role_battle_handle->is_in_house, _x, _y);
        spdlog::trace("in_out_house _x:{0}, _y:{1}!", _x, _y);
        _obb->set_center_pos(_x, _y);
    }

    spdlog::trace("in_out_house end ret:{0}!", ret);

    return ret;
}

bool role_scene::check_at_wreck()
{
    auto pos = _obb->get_center_pos();
    auto _x = pos.x;
    auto _y = pos.y;
    auto x_box = (_x / 16);
    auto y_box = (_y / 16);

    auto _map = _map_handle.lock();
    if (!_map) {
        return false;
    }

    auto house_box = _map->get_house_box(x_box, y_box);
    if (house_box->map_elem->_property == em_map_element_property::em_map_wreck) {
        return true;
    }

    return false;
}

void role_scene::sync_in_out_house_field(std::shared_ptr<role> _self, std::shared_ptr<map> _map, int ret) {
    std::vector<std::string> leave_role_view_uuids;
    std::vector<std::string> leave_filed_role_id;
    std::vector<std::string> into_field_uuids;
    std::vector<abelkhan::role_info> into_filed_role_info;
    auto now_sub_map = _map->get_field_sub_map(get_scene_x());
    for (auto _sub_map : now_sub_map) {
        for (auto _role_tmp : _sub_map->field_roles) {
            auto _role_tmp_ptr = _role_tmp.lock();
            if (!_role_tmp_ptr) {
                continue;
            }

            if (_role_tmp_ptr == _self) {
                continue;
            }

            //if (!_role_tmp_ptr->is_live) {
            //    continue;
            //}

            if (_role_tmp_ptr->_role_battle_handle->is_in_house != _self->_role_battle_handle->is_in_house) {
                if (_role_tmp_ptr->check_sync()) {
                    leave_role_view_uuids.push_back(_role_tmp_ptr->uuid);
                }
                leave_filed_role_id.push_back(_role_tmp_ptr->id);
            }
            else {
                if (_self->_role_battle_handle->is_in_house)
                {
                    if (check_in_same_house(_self->_role_scene_handle, _role_tmp_ptr->_role_scene_handle))
                    {
                        if (_role_tmp_ptr->check_sync()) {
                            into_field_uuids.push_back(_role_tmp_ptr->uuid);
                        }
                        if (_role_tmp_ptr->is_live) {
                            into_filed_role_info.push_back(_role_tmp_ptr->cs_info());
                        }
                    }
                }
                else
                {
                    if (_role_tmp_ptr->check_sync()) {
                        into_field_uuids.push_back(_role_tmp_ptr->uuid);
                    }
                    if (_role_tmp_ptr->is_live) {
                        into_filed_role_info.push_back(_role_tmp_ptr->cs_info());
                    }
                }
            }
        }
    }

    std::vector<std::string> _role_leave_id;
    _role_leave_id.push_back(_self->id);
    _call_mng_handle->battle_client_caller->get_multicast(leave_role_view_uuids)->leave_field_info(_role_leave_id);
    _call_mng_handle->battle_client_caller->get_multicast({ _self->uuid })->leave_field_info(leave_filed_role_id);

    std::vector<abelkhan::role_info> _role_self_info;
    _role_self_info.push_back(_self->cs_info());
    _call_mng_handle->battle_client_caller->get_multicast(into_field_uuids)->field_info(_role_self_info);
    _call_mng_handle->battle_client_caller->get_multicast({ _self->uuid })->field_info(into_filed_role_info);

    _call_mng_handle->battle_client_caller->get_client(_self->uuid)->in_out_house(ret);

    send_role_move_state();
}

void role_scene::clear_house_range() {
    house_range_begin = -1;
    house_range_end = -1;
}

void role_scene::check_and_set_house_range() {
    auto pos = _obb->get_center_pos();
    auto _x = pos.x;
    auto _y = pos.y;
    auto x_box = (_x / 16);
    auto y_box = (_y / 16);

    auto _map = _map_handle.lock();
    if (!_map) {
        return ;
    }

    auto tmp_x_box = x_box;
    auto house_box = _map->get_house_box(tmp_x_box, y_box);
    while (house_box->map_elem->_property != em_map_element_property::em_map_empty) {
        if (tmp_x_box > 0) {
            house_box = _map->get_house_box(--tmp_x_box, y_box);
        }
    }
    house_range_begin = tmp_x_box * 16;

    house_box = _map->get_house_box(x_box, y_box);
    while (house_box->map_elem->_property != em_map_element_property::em_map_empty) {
        house_box = _map->get_house_box(++x_box, y_box);
    }
    house_range_end = x_box * 16;
}

int role_scene::wreck_in_out_house() 
{
    spdlog::trace("wreck_in_out_house begin!");

    int ret = (int)in_out_house_state::em_not_door;

    do {
        auto _map = _map_handle.lock();
        if (!_map) {
            break;
        }

        auto _role_ptr = _role.lock();
        if (!_role_ptr) {
            break;
        }

        if (check_at_wreck()) {
            if (_role_ptr->_role_battle_handle->is_in_house) {
                ret = (int)in_out_house_state::em_out_house;
                _role_ptr->_role_battle_handle->is_in_house = false;
                clear_house_range();
            }
            else {
                ret = (int)in_out_house_state::em_in_house;
                _role_ptr->_role_battle_handle->is_in_house = true;
                check_and_set_house_range();
            }
        }

        if (ret != (int)in_out_house_state::em_not_door) {
            sync_in_out_house_field(_role_ptr, _map, ret);
        }

    } while (false);

    return ret;

    spdlog::trace("wreck_in_out_house end!");
}

int role_scene::door_in_out_house()
{
    spdlog::trace("door_in_out_house begin!");

    int ret = (int)in_out_house_state::em_not_door;

    do {
        auto _map = _map_handle.lock();
        if (!_map) {
            break;
        }

        auto _role_ptr = _role.lock();
        if (!_role_ptr) {
            break;
        }

        auto pos = _obb->get_center_pos();
        auto _x = pos.x;
        auto _y = pos.y;
        auto x_box = (_x / 16);
        auto y_box = (_y / 16);

        bool in_door = false;
        for (auto door : _map->door_data) {
            spdlog::trace("in_out_house pos.x{0}, pos.y{1}, door.y_min{2}, door.y_max{3}, door.x_min{4}, door.x_max{5}!", _x, _y, door.y_min, door.y_max, door.x_min, door.x_max);
            if ((_y >= (door.y_min - 32) && _y <= (door.y_max + 16)) && (_x >= (door.x_min - 16) && _x <= (door.x_max + 16))) {
                in_door = true;
                break;
            }
        }

        if (in_door) {
            if (_role_ptr->_role_battle_handle->is_in_house) {
                ret = (int)in_out_house_state::em_out_house;
                _role_ptr->_role_battle_handle->is_in_house = false;
                clear_house_range();
                spdlog::trace("in_out_house set is_in_house false!");
            }
            else {
                ret = (int)in_out_house_state::em_in_house;
                _role_ptr->_role_battle_handle->is_in_house = true;
                check_and_set_house_range();
                spdlog::trace("in_out_house set is_in_house true!");
            }
        }

        if (ret != (int)in_out_house_state::em_not_door) {
            sync_in_out_house_field(_role_ptr, _map, ret);
        }

    } while (false);

    return ret;

    spdlog::trace("door_in_out_house end!");
}

std::vector<ladder>::iterator role_scene::check_ladder_down(int32_t _x, int32_t _y) {
    spdlog::trace("check_ladder_down begin!");

    auto _map = _map_handle.lock();
    if (!_map) {
        throw std::exception("battle map is empty!");
    }

    auto x_box = (_x / 16);
    auto y_box = (_y / 16);

    auto foot_box_property = _map->get_box_list(x_box, y_box - 1);
    auto house_box = _map->get_house_box(x_box, y_box + 1);
    auto i = _map->ladder_data.end();
    if (foot_box_property->map_elem->_property != em_map_element_property::em_map_map) {
        if (house_box /*&& house_box->map_elem->_property == "map"*/) {
            for (i = _map->ladder_data.begin(); i != _map->ladder_data.end(); i++) {
                spdlog::trace("check_ladder_down _x:{0}, _y{1}, i->y_min{2}, i->y_max{3}, i->x_min{4}, i->x_max{5}!", _x, _y, i->y_min, i->y_max, i->x_min, i->x_max);
                if ((_y > (i->y_min) && _y <= (i->y_max + 16)) && (_x >= (i->x_min) && _x <= (i->x_max))) {
                    break;
                }
            }
        }
    }

    spdlog::trace("check_ladder_down end!");

    return i;
}

std::vector<ladder>::iterator role_scene::check_ladder_up(int32_t _x, int32_t _y) {
    spdlog::trace("check_ladder_up begin!");

    auto _map = _map_handle.lock();
    if (!_map) {
        throw std::exception("battle map is empty!");
    }

    auto x_box = (_x / 16);
    auto y_box = (_y / 16);
    auto house_box = _map->get_house_box(x_box, y_box);
    auto i = _map->ladder_data.end();
    if (house_box != nullptr) {
        spdlog::trace("check_ladder_up _property:{0}!", house_box->map_elem->_property);
    }
    if (house_box != nullptr /*&& house_box->map_elem->_property == "map"*/) {
        for (i = _map->ladder_data.begin(); i != _map->ladder_data.end(); i++) {
            spdlog::trace("check_ladder_up _x:{0}, _y{1}, i->y_min{2}, i->y_max{3}, i->x_min{4}, i->x_max{5}!", _x, _y, i->y_min, i->y_max, i->x_min, i->x_max);
            if ((_y >= (i->y_min - 16) && _y < (i->y_max)) && (_x >= (i->x_min) && _x <= (i->x_max))) {
                break;
            }
        }
    }

    spdlog::trace("check_ladder_up end!");

    return i;
}

bool role_scene::check_in_same_house(std::shared_ptr<role_scene> self, std::shared_ptr<role_scene> target)
{
    spdlog::trace("check_in_same_house begin!");

    auto _map = self->_map_handle.lock();
    if (!_map) {
        return false;
    }

    auto self_pos = self->_obb->get_center_pos();
    auto self_x = self_pos.x;
    auto self_y = self_pos.y;

    auto target_pos = target->_obb->get_center_pos();
    auto target_x = target_pos.x;
    auto target_y = target_pos.y;

    if ((int32_t)self_x >= target->house_range_begin && (int32_t)self_x <= target->house_range_end &&
        (int32_t)target_x >= self->house_range_begin && (int32_t)target_x <= self->house_range_end)
    {
        spdlog::trace("check_in_same_house end true!");
        return true;
    }

    spdlog::trace("check_in_same_house end false!");
    return false;
}

}