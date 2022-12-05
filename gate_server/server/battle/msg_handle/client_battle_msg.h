/*
 * qianqians
 * 2020-1-26
 * battle
 * client_battle_msg.h
 */
#ifndef _client_battle_msg_h
#define _client_battle_msg_h

#include <hub.h>

#include "ccallbattle.h"

#include "../singleton.h"
#include "../call_mng.h"
#include "../battle/battle.h"
#include "../battle/role.h"

namespace battle {

class client_battle_msg {
public:
    std::shared_ptr<abelkhan::battle_module> _module;

public:
    client_battle_msg(std::shared_ptr<hub::hub_service> _hub) {
        _module = std::make_shared<abelkhan::battle_module>();
        _module->Init(_hub);
    }

    void Init() {
        _module->sig_ping.connect([this]() {
            spdlog::trace("ping begin!");

            auto rsp = std::static_pointer_cast<abelkhan::battle_ping_rsp>(_module->rsp);
            rsp->rsp();

            spdlog::trace("ping end!");
        });

        _module->sig_load_scene_done.connect([this](std::string role_id) {
            spdlog::trace("load_scene_done begin!");

            auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
            auto _role = _singleton_handle->_role_mng_handle->get_role_by_id(role_id);
            if (!_role) {
                spdlog::trace("load_scene_done _role is empty!");
                _call_mng_handle->error_code_caller->get_client(session_uuid)->error_code((int32_t)abelkhan::error::battle_is_end);
                return;
            }
            if (session_uuid != _role->uuid) {
                spdlog::trace("refresh_uuid old_uuid:{0}, new_uuid:{1}", _role->uuid, session_uuid);
                _singleton_handle->_role_mng_handle->refresh_uuid(role_id, session_uuid);
            }

            _role->load_scene_done = true;

            auto _battle = _role->_battle_handle.lock();
            if (!_battle) {
                return;
            }

            _call_mng_handle->battle_client_caller->get_client(session_uuid)->main_role_info_ntf(_role->main_cs_info());

            auto field_uuids = _battle->_map_handle->get_field_roles_uuid(_role->_role_scene_handle->get_scene_x());
            std::vector<std::string> _field_uuids;
            for (auto _uuid : field_uuids) {
                if (_uuid == _role->uuid) {
                    continue;
                }
                _field_uuids.push_back(_uuid);
            }
            std::vector<abelkhan::role_info> info;
            info.push_back(_role->cs_info());
            _call_mng_handle->battle_client_caller->get_multicast(_field_uuids)->field_info(info);

            _battle->role_into_battle(_role->id);
            auto field_roles = _battle->_map_handle->get_field_roles(_role->_role_scene_handle->get_scene_x());
            std::vector<abelkhan::role_info>  _field_roles;
            for (auto _tmp : field_roles) {
                if (_tmp->id == _role->id) {
                    continue;
                }
                if (_tmp->_role_battle_handle->hp <= 0) {
                    continue;
                }
                _field_roles.push_back(_tmp->cs_info());

                _tmp->_role_skill_handle->check_and_send_skill_info_to_role(_tmp, _role);
            }
            _call_mng_handle->battle_client_caller->get_multicast({ _role->uuid })->field_info(_field_roles);

            std::vector<abelkhan::drop_item_info> _drop_item_list;
            for (auto _sub_map : _battle->_map_handle->sub_maps) {
                spdlog::trace("_sub_map->item_box_list.size:{0}", _sub_map->item_box_list.size());
                for (auto _drop_item : _sub_map->item_box_list) {
                    if (_role->_role_battle_handle->is_in_house != _drop_item->is_in_house) {
                        spdlog::trace("_role item not in same layer");
                        continue;
                    }

                    abelkhan::drop_item_info _drop_item_info;
                    _drop_item_info.uuid = _drop_item->uuid;
                    _drop_item_info.desc_id = _drop_item->desc_id;
                    _drop_item_info.is_in_house = _drop_item->is_in_house;
                    _drop_item_info.x = _drop_item->x;
                    _drop_item_info.y = _drop_item->y;
                    _drop_item_list.push_back(_drop_item_info);
                }
            }
            _call_mng_handle->battle_client_caller->get_multicast({ _role->uuid })->drop_item_list(_drop_item_list);

            spdlog::trace("load_scene_done end!");
        });

        _module->sig_role_rocker.connect([](int64_t rocker_state) {
            spdlog::trace("role_rocker begin!");

            do {
                auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
                auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
                if (!_role) {
                    spdlog::trace("role_rocker _role is empty session_uuid:{0}!", session_uuid);
                    break;
                }

                auto _battle = _role->_battle_handle.lock();
                if (!_battle) {
                    break;
                }

                if (_battle->is_end) {
                    spdlog::trace("role_rocker battle is end!");
                    break;
                }

                if (!_role->is_live) {
                    spdlog::trace("role_rocker role is death!");
                    break;
                }

                if (_role->is_exception) {
                    spdlog::trace("role_rocker role is exception!");
                    break;
                }

                _role->_role_scene_handle->set_rocker((int32_t)rocker_state);
            } while (false);

            spdlog::trace("role_rocker end!");
        });

        _module->sig_role_jump.connect([]() {
            spdlog::trace("role_jump begin!");

            do {
                auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
                auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
                if (!_role) {
                    spdlog::trace("role_jump _role is empty!");
                    break;
                }

                auto _battle = _role->_battle_handle.lock();
                if (!_battle) {
                    break;
                }

                if (_battle->is_end) {
                    spdlog::trace("role_jump battle is end!");
                    break;
                }

                if (!_role->is_live) {
                    spdlog::trace("role_jump role is death!");
                    break;
                }

                if (_role->is_exception) {
                    spdlog::trace("role_jump role is exception!");
                    break;
                }

                _role->_role_scene_handle->set_jump();
            } while (false);

            spdlog::trace("role_jump end!");
        });

        _module->sig_use_skill.connect([](std::string skill_name) {
            spdlog::trace("use_skill begin!");

            do {
                auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
                auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
                if (!_role) {
                    spdlog::trace("use_skill _role is empty!");
                    break;
                }

                auto _battle = _role->_battle_handle.lock();
                if (!_battle) {
                    break;
                }

                if (_battle->is_end) {
                    spdlog::trace("use_skill battle is end!");
                    break;
                }

                if (!_role->is_live) {
                    spdlog::trace("use_skill role is death!");
                    break;
                }

                if (_role->is_exception) {
                    spdlog::trace("use_skill role is exception!");
                    break;
                }

                _role->_role_skill_handle->do_skill(skill_name);
            } while (false);

            spdlog::trace("use_skill end!");
        });

        _module->sig_role_aim.connect([](int64_t angle) {
            spdlog::trace("role_aim begin!");

            do {
                auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
                auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
                if (!_role) {
                    spdlog::trace("role_aim _role is empty!");
                    break;
                }

                auto _battle = _role->_battle_handle.lock();
                if (!_battle) {
                    break;
                }

                if (_battle->is_end) {
                    spdlog::trace("role_aim battle is end!");
                    break;
                }

                if (!_role->is_live) {
                    spdlog::trace("role_aim role is death!");
                    break;
                }

                if (_role->is_exception) {
                    spdlog::trace("role_aim role is exception!");
                    break;
                }

                _role->_role_battle_handle->aim((float)angle);

            } while (false);

            spdlog::trace("role_aim end!");
        });

        _module->sig_role_change_equip.connect([](std::string equip_uuid) {
            spdlog::trace("role_change_equip begin!");

            do {
                auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
                auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
                if (!_role) {
                    spdlog::trace("role_change_equip _role is empty!");
                    break;
                }

                auto _battle = _role->_battle_handle.lock();
                if (!_battle) {
                    break;
                }

                if (!_battle->is_start) {
                    spdlog::trace("role_change_equip battle is not start!");
                    break;
                }

                if (_battle->is_end) {
                    spdlog::trace("role_change_equip battle is end!");
                    break;
                }

                if (!_role->is_live) {
                    spdlog::trace("role_change_equip role is death!");
                    break;
                }

                if (_role->is_exception) {
                    spdlog::trace("role_change_equip role is exception!");
                    break;
                }

                if (_role->_role_bag_handle->change_equip(equip_uuid, _role->_role_battle_handle)) {
                    _call_mng_handle->battle_client_caller->get_client(session_uuid)->main_role_info_ntf(_role->main_cs_info());

                    auto filed_uuids = _role->_role_scene_handle->get_role_field();
                    std::vector<std::string> _field_uuids;
                    for (auto _uuid : filed_uuids) {
                        if (_uuid == _role->uuid) {
                            continue;
                        }
                        _field_uuids.push_back(_uuid);
                    }
                    std::vector<abelkhan::role_info> info;
                    info.push_back(_role->cs_info());
                    _call_mng_handle->battle_client_caller->get_multicast(_field_uuids)->field_info(info);
                }

            } while (false);

            spdlog::trace("role_change_equip end!");
        });

        _module->sig_role_shoot.connect([]() {
            spdlog::trace("role_shoot begin!");

            do {
                auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
                auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
                if (!_role) {
                    spdlog::trace("role_shoot _role is empty!");
                    break;
                }

                auto _battle = _role->_battle_handle.lock();
                if (!_battle) {
                    break;
                }

                if (!_battle->is_start) {
                    spdlog::trace("role_shoot battle is not start!");
                    break;
                }

                if (_battle->is_end) {
                    spdlog::trace("role_shoot battle is end!");
                    break;
                }

                if (!_role->is_live) {
                    spdlog::trace("role_shoot role is death!");
                    break;
                }

                if (_role->is_exception) {
                    spdlog::trace("role_shoot role is exception!");
                    break;
                }

                _role->_role_battle_handle->shoot();

            } while (false);

            spdlog::trace("role_shoot end!");
        });

        _module->sig_role_rpg_shoot.connect([](int64_t angle) {
            spdlog::trace("role_rpg_shoot begin!");

            do {
                auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
                auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
                if (!_role) {
                    spdlog::trace("role_rpg_shoot _role is empty!");
                    break;
                }

                auto _battle = _role->_battle_handle.lock();
                if (!_battle) {
                    break;
                }

                if (!_battle->is_start) {
                    spdlog::trace("role_rpg_shoot battle is not start!");
                    break;
                }

                if (_battle->is_end) {
                    spdlog::trace("role_rpg_shoot battle is end!");
                    break;
                }

                if (!_role->is_live) {
                    spdlog::trace("role_rpg_shoot role is death!");
                    break;
                }

                if (_role->is_exception) {
                    spdlog::trace("role_rpg_shoot role is exception!");
                    break;
                }

                _role->_role_battle_handle->rpg_shoot(angle);

            } while (false);

            spdlog::trace("role_rpg_shoot end!");
        });

        _module->sig_role_rpg_target_shoot.connect([](int64_t target_x, int64_t target_y) {
            spdlog::trace("role_rpg_target_shoot begin!");

            do {
                auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
                auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
                if (!_role) {
                    spdlog::trace("role_rpg_target_shoot _role is empty!");
                    break;
                }

                auto _battle = _role->_battle_handle.lock();
                if (!_battle) {
                    break;
                }

                if (!_battle->is_start) {
                    spdlog::trace("role_rpg_target_shoot battle is not start!");
                    break;
                }

                if (_battle->is_end) {
                    spdlog::trace("role_rpg_target_shoot battle is end!");
                    break;
                }

                if (!_role->is_live) {
                    spdlog::trace("role_rpg_target_shoot role is death!");
                    break;
                }

                if (_role->is_exception) {
                    spdlog::trace("role_rpg_target_shoot role is exception!");
                    break;
                }

                _role->_role_battle_handle->rpg_aim_shoot(target_x, target_y);

            } while (false);

            spdlog::trace("role_rpg_target_shoot end!");
        });

        _module->sig_role_grenade_shoot.connect([](int64_t angle) {
            spdlog::trace("role_grenade_shoot begin!");

            do {
                auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
                auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
                if (!_role) {
                    spdlog::trace("role_grenade_shoot _role is empty!");
                    break;
                }

                auto _battle = _role->_battle_handle.lock();
                if (!_battle) {
                    break;
                }

                if (!_battle->is_start) {
                    spdlog::trace("role_grenade_shoot battle is not start!");
                    break;
                }

                if (_battle->is_end) {
                    spdlog::trace("role_grenade_shoot battle is end!");
                    break;
                }

                if (!_role->is_live) {
                    spdlog::trace("role_grenade_shoot role is death!");
                    break;
                }

                if (_role->is_exception) {
                    spdlog::trace("role_grenade_shoot role is exception!");
                    break;
                }

                _role->_role_battle_handle->grenade_shoot((float)angle);

            } while (false);

            spdlog::trace("role_grenade_shoot end!");
        });

        _module->sig_role_grenade_target_shoot.connect([](int64_t target_x, int64_t target_y) {
            spdlog::trace("role_grenade_target_shoot begin!");

            do {
                auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
                auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
                if (!_role) {
                    spdlog::trace("role_grenade_target_shoot _role is empty!");
                    break;
                }

                auto _battle = _role->_battle_handle.lock();
                if (!_battle) {
                    break;
                }

                if (!_battle->is_start) {
                    spdlog::trace("role_grenade_target_shoot battle is not start!");
                    break;
                }

                if (_battle->is_end) {
                    spdlog::trace("role_grenade_target_shoot battle is end!");
                    break;
                }

                if (!_role->is_live) {
                    spdlog::trace("role_grenade_target_shoot role is death!");
                    break;
                }

                if (_role->is_exception) {
                    spdlog::trace("role_grenade_target_shoot role is exception!");
                    break;
                }

                _role->_role_battle_handle->grenade_aim_shoot(target_x, target_y);

            } while (false);

            spdlog::trace("role_grenade_target_shoot end!");
        });

        _module->sig_get_bag_info.connect([this]() {
            spdlog::trace("get_bag_info begin!");

            auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
            auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
            if (!_role) {
                spdlog::trace("get_bag_info _role is empty!");
                return;
            }

            auto rsp = std::static_pointer_cast<abelkhan::battle_get_bag_info_rsp>(_module->rsp);
            rsp->rsp(_role->_role_bag_handle->cs_info());

            spdlog::trace("get_bag_info end!");
        });

        _module->sig_get_battle_info.connect([this]() {
            spdlog::trace("get_battle_info begin!");

            auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
            auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
            if (!_role) {
                spdlog::trace("get_battle_info _role is empty!");
                return;
            }

            auto rsp = std::static_pointer_cast<abelkhan::battle_get_battle_info_rsp>(_module->rsp);
            rsp->rsp(_role->_role_battle_handle->cs_info());

            spdlog::trace("get_battle_info end!");
        });

        _module->sig_drop_item.connect([](std::string item_uuid, int64_t num) {
            spdlog::trace("drop_item begin!");

            auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
            auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
            if (!_role) {
                spdlog::trace("drop_item _role is empty!");
                return;
            }

            if (_role->is_exception) {
                spdlog::trace("drop_item role is exception!");
                return;
            }

            auto _battle = _role->_battle_handle.lock();
            if (!_battle) {
                return;
            }

            if (!_battle->is_start) {
                spdlog::trace("drop_item battle is not start!");
                return;
            }

            _role->drop_item(item_uuid, (int32_t)num);
            _call_mng_handle->battle_client_caller->get_client(_role->uuid)->bag_info(_role->_role_bag_handle->cs_info());
            _call_mng_handle->battle_client_caller->get_client(_role->uuid)->battle_info(_role->_role_battle_handle->cs_info());

            spdlog::trace("drop_item end!");
        });

        _module->sig_drop_bullet.connect([](int64_t num) {
            spdlog::trace("drop_bullet begin!");

            auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
            auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
            if (!_role) {
                spdlog::trace("drop_bullet _role is empty!");
                return;
            }

            if (_role->is_exception) {
                spdlog::trace("drop_bullet role is exception!");
                return;
            }

            auto _battle = _role->_battle_handle.lock();
            if (!_battle) {
                return;
            }

            if (!_battle->is_start) {
                spdlog::trace("drop_bullet battle is not start!");
                return;
            }

            _role->drop_bullet((int32_t)num);
            _call_mng_handle->battle_client_caller->get_client(_role->uuid)->battle_info(_role->_role_battle_handle->cs_info());

            spdlog::trace("drop_bullet end!");
        });

        _module->sig_pickup_item.connect([this](std::string item_uuid) {
            spdlog::trace("pickup_item begin!");

            do {
                auto rsp = std::static_pointer_cast<abelkhan::battle_pickup_item_rsp>(_module->rsp);

                auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
                auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
                if (!_role) {
                    spdlog::trace("pickup_item _role is empty!");
                    break;
                }
                auto _map = _role->_role_scene_handle->_map_handle.lock();
                if (!_map) {
                    break;
                }

                auto _battle = _role->_battle_handle.lock();
                if (!_battle) {
                    break;
                }

                if (!_battle->is_start) {
                    spdlog::trace("pickup_item battle is not start!");
                    break;
                }

                if (_battle->is_end) {
                    spdlog::trace("pickup_item battle is end!");
                    break;
                }

                if (!_role->is_live) {
                    spdlog::trace("pickup_item role is death!");
                    break;
                }

                if (_role->is_exception) {
                    spdlog::trace("pickup_item role is exception!");
                    break;
                }

                auto _sub_map = _map->get_sub_map(_role->_role_scene_handle->get_scene_x());
                for (auto _drop_item = _sub_map->item_box_list.begin(); _drop_item != _sub_map->item_box_list.end(); _drop_item++) {
                    if ((*_drop_item)->uuid == item_uuid) {
                        int32_t offset = (int32_t)((*_drop_item)->x) - _role->_role_scene_handle->get_scene_x();
                        if (abs(offset) > 64) {
                            rsp->err((int32_t)abelkhan::error::drop_box_too_far);
                            spdlog::trace("pickup_item role offset:{0}", abs(offset));
                            return;
                        }

                        _role->pickup_item(*_drop_item);
                        rsp->rsp();
                        
                        _call_mng_handle->battle_client_caller->get_client(_role->uuid)->bag_info(_role->_role_bag_handle->cs_info());
                        _call_mng_handle->battle_client_caller->get_client(_role->uuid)->battle_info(_role->_role_battle_handle->cs_info());
                        
                        std::vector<std::string> leave_field_drop_item_uuid;
                        leave_field_drop_item_uuid.push_back((*_drop_item)->uuid);
                        _call_mng_handle->battle_client_caller->get_multicast(_map->get_field_roles_uuid((*_drop_item)->x))->leave_field_info(leave_field_drop_item_uuid);
                        
                        return;
                    }
                }

                rsp->err((int32_t)abelkhan::error::invalid_drop_team);

            } while (false);

            spdlog::trace("pickup_item end!");
        });

        _module->sig_medicine.connect([](std::string medicine_uuid) {
            spdlog::trace("medicine begin!");

            auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
            auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
            if (!_role) {
                spdlog::trace("medicine _role is empty!");
                return;
            }

            auto _battle = _role->_battle_handle.lock();
            if (!_battle) {
                return;
            }

            if (!_battle->is_start) {
                spdlog::trace("medicine battle is not start!");
                return;
            }

            if (_battle->is_end) {
                spdlog::trace("medicine battle is end!");
                return;
            }

            if (!_role->is_live) {
                spdlog::trace("medicine role is death!");
                return;
            }

            if (_role->is_exception) {
                spdlog::trace("medicine role is exception!");
                return;
            }

            _role->use_medicine(medicine_uuid);
            _call_mng_handle->battle_client_caller->get_client(_role->uuid)->bag_info(_role->_role_bag_handle->cs_info());
            _call_mng_handle->battle_client_caller->get_client(_role->uuid)->battle_info(_role->_role_battle_handle->cs_info());

            spdlog::trace("medicine end!");
        });

        _module->sig_in_out_house.connect([this]() {
            spdlog::trace("in_out_house begin!");

            auto session_uuid = _singleton_handle->_hub_handle->_gatemng->current_client_cuuid;
            auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(session_uuid);
            if (!_role) {
                spdlog::trace("in_out_house _role is empty!");
                return;
            }

            auto _battle = _role->_battle_handle.lock();
            if (!_battle) {
                return;
            }

            if (!_battle->is_start) {
                spdlog::trace("in_out_house battle is not start!");
                return;
            }

            if (_battle->is_end) {
                spdlog::trace("in_out_house battle is end!");
                return;
            }

            if (!_role->is_live) {
                spdlog::trace("in_out_house role is death!");
                return;
            }

            if (_role->is_exception) {
                spdlog::trace("in_out_house role is exception!");
                return;
            }

            auto ret = _role->_role_scene_handle->in_out_house();
            auto rsp = std::static_pointer_cast<abelkhan::battle_in_out_house_rsp>(_module->rsp);

            if (ret == (int)in_out_house_state::em_in_house || ret == (int)in_out_house_state::em_out_house) {
                rsp->rsp(ret);
            }
            else {
                rsp->err((int32_t)abelkhan::error::not_at_door);
            }

            spdlog::trace("in_out_house end!");
        });
    }
};

}

#endif //_client_battle_msg_h