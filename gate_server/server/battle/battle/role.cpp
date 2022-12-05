/*
 * qianqians
 * 2021-5-1
 * battle
 * role.cpp
 */

#include "role.h"
#include "team.h"

namespace battle {

int role::count = 0;

abelkhan::main_role_info role::main_cs_info() {
    abelkhan::main_role_info info;
    info.id = id;
    info.account = account;
    info.name = name;
    auto _team = _team_handle.lock();
    if (_team) {
        info.team_id = _team->team_id;
    }
    info._bag_info = _role_bag_handle->cs_info();
    info._scene_info = _role_scene_handle->cs_info();
    info._body_info = _role_body_handle->cs_info();
    info._battle_info = _role_battle_handle->cs_info();
    info._skill_info = _role_skill_handle->cs_info();
    return info;
}

}
