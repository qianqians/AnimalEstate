/*
 * qianqians
 * 2021-4-3
 * robot
 * robot.cpp
 */
#include <memory>

#include "robot.h"
#include "team.h"
#include "role_bag.h"
#include "constant.h"
#include "../singleton.h"
#include "../json_config/json_config_mng.h"
#include "random.h"

namespace battle {

void robot::Init(std::shared_ptr<map> _map) {
    spdlog::trace("Init role begin!");

    uuid = xg::newGuid().str();
    lobby = "";
    account = "robot";
    id = uuid;

    _role_body_handle = std::make_shared<role_body>();
    _role_battle_handle = std::make_shared<role_battle>(shared_from_this());
    _role_bag_handle = std::make_shared<role_bag>(shared_from_this());
    _role_scene_handle = std::make_shared<role_scene>(shared_from_this(), _map->random_born(), 10);

    //Fossilizid::JsonParse::JsonCast<Fossilizid::JsonParse::JsonArray>((*cs_role)["bag"]));
    _role_bag_handle->Init();
    
    std::vector<std::string> skill_list = { "roll", "sprint", "treatment", "twostepjump" };
    _role_skill_handle = std::make_shared<role_skill>(shared_from_this(), skill_list);

    is_robot = true;
    load_scene_done = true;
    is_live = true;

    is_exception = false;

    _role_battle_handle->ntf_shoot_direction();

    spdlog::trace("Init role end!");
}

void robot::ai_work() {
    if (!is_live) {
        return;
    }

    auto _battle = _battle_handle.lock();
    if (!_battle) {
        return;
    }

    do {
        if (!_battle->is_start) {
            int r = utils::random(100);
            spdlog::trace("ai_work start direction r:{0}", r);
            if (r < 50) {
                _role_scene_handle->set_direction(1);
            }
            else {
                _role_scene_handle->set_direction(-1);
            }
            break;
        }

        if (is_in_battle) {
            _role_scene_handle->set_direction(0);
            break;
        }

        auto pos = _role_scene_handle->_obb->get_center_pos();
        auto next_poison_center = (_battle->next_poison_left + _battle->next_poison_right) / 2;
        if (next_poison_center > pos.x) {
            _role_scene_handle->set_direction(1);
        }
        else {
            _role_scene_handle->set_direction(-1);
        }
        spdlog::trace("next_poison_center:{0}, pos.x:{1}", next_poison_center, pos.x);

    } while (false);

    int r = utils::random(100);
    if (r < 50) {
        _role_scene_handle->set_jump();
    }
}

double _atan(float offset_x, float offset_y) {
    spdlog::trace("offset_x:{0}, offset_y:{1}", offset_x, offset_y);

    auto _angle = (atan2(offset_y, offset_x)) * 180 / constant::PI;
    if (_angle < 0) {
        _angle += 360;
    }

    return _angle;
}

void robot::check_shoot() {
    spdlog::trace("robot check_shoot begin!");

    auto _battle = _battle_handle.lock();
    if (!_battle) {
        spdlog::trace("robot check_shoot !_battle end!");
        return;
    }

    if (!_battle->is_start) {
        spdlog::trace("robot check_shoot _battle not start end!");
        return;
    }
    if (!is_live) {
        spdlog::trace("robot check_shoot robot !is_live end!");
        return;
    }

    auto _map = _role_scene_handle->_map_handle.lock();
    if (!_map) {
        return;
    }

    is_aim_right = !is_aim_right;
    if (is_aim_right) {
        auto x = _role_scene_handle->get_scene_x();
        auto right_roles = _map->get_range_field_roles(x, x + constant::robot_range);
        for (auto _role : right_roles) {
            if (!_role->is_live) {
                continue;
            }

            if (!check_camp(_role) && _role_battle_handle->_bullets_num > 0) {
                auto self_pos = _role_scene_handle->_obb->get_center_pos();
                auto target_pos = _role->_role_scene_handle->_obb->get_center_pos();
                auto offset_x = (float)target_pos.x - self_pos.x;
                if (abs(offset_x) < constant::robot_range) {
                    auto shoot_angle = (float)_atan(offset_x, float((float)target_pos.y - self_pos.y));
                    _role_battle_handle->aim(shoot_angle);
                    _role_battle_handle->shoot();
                    is_in_battle = true;
                    spdlog::trace("robot check_shoot end!");
                    return;
                }
                if (offset_x > 0) {
                    _role_scene_handle->set_direction(1);
                }
                else {
                    _role_scene_handle->set_direction(-1);
                }
            }
        }

        auto left_roles = _map->get_range_field_roles(x - constant::robot_range, x);
        for (auto _role : left_roles) {
            if (!_role->is_live) {
                continue;
            }

            if (!check_camp(_role) && _role_battle_handle->_bullets_num > 0) {
                auto self_pos = _role_scene_handle->_obb->get_center_pos();
                auto target_pos = _role->_role_scene_handle->_obb->get_center_pos();
                auto offset_x = (float)target_pos.x - self_pos.x;
                if (abs(offset_x) < constant::robot_range) {
                    auto shoot_angle = (float)_atan(offset_x, float((float)target_pos.y - self_pos.y));
                    _role_battle_handle->aim(shoot_angle);
                    _role_battle_handle->shoot(); 
                    is_in_battle = true;
                    spdlog::trace("robot check_shoot end!");
                    return;
                }
                if (offset_x > 0) {
                    _role_scene_handle->set_direction(1);
                }
                else {
                    _role_scene_handle->set_direction(-1);
                }
            }
        }
        is_in_battle = false;
    }
    else {
        auto x = _role_scene_handle->get_scene_x();
        auto left_roles = _map->get_range_field_roles(x - constant::robot_range, x);
        for (auto _role : left_roles) {
            if (!_role->is_live) {
                continue;
            }

            if (!check_camp(_role) && _role_battle_handle->_bullets_num > 0) {
                auto self_pos = _role_scene_handle->_obb->get_center_pos();
                auto target_pos = _role->_role_scene_handle->_obb->get_center_pos();
                auto offset_x = (float)target_pos.x - self_pos.x;
                if (abs(offset_x) < constant::robot_range) {
                    auto shoot_angle = (float)_atan(offset_x, float((float)target_pos.y - self_pos.y));
                    _role_battle_handle->aim(shoot_angle);
                    _role_battle_handle->shoot();
                    is_in_battle = true;
                    spdlog::trace("robot check_shoot end!");
                    return;
                }
                if (offset_x > 0) {
                    _role_scene_handle->set_direction(1);
                }
                else {
                    _role_scene_handle->set_direction(-1);
                }
            }
        }

        auto right_roles = _map->get_range_field_roles(x, x + constant::robot_range);
        for (auto _role : right_roles) {
            if (!_role->is_live) {
                continue;
            }

            if (!check_camp(_role) && _role_battle_handle->_bullets_num > 0) {
                auto self_pos = _role_scene_handle->_obb->get_center_pos();
                auto target_pos = _role->_role_scene_handle->_obb->get_center_pos();
                auto offset_x = (float)target_pos.x - self_pos.x;
                if (abs(offset_x) < constant::robot_range) {
                    auto shoot_angle = (float)_atan(offset_x, float((float)target_pos.y - self_pos.y));
                    _role_battle_handle->aim(shoot_angle);
                    _role_battle_handle->shoot();
                    is_in_battle = true;
                    spdlog::trace("robot check_shoot end!");
                    return;
                }
                if (offset_x > 0) {
                    _role_scene_handle->set_direction(1);
                }
                else {
                    _role_scene_handle->set_direction(-1);
                }
            }
        }
        is_in_battle = false;
    }

    spdlog::trace("robot check_shoot end!");
}

}