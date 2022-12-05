/*
 * qianqians
 * 2020-1-26
 * battle
 * match_msg.h
 */
#ifndef _match_msg_h
#define _match_msg_h

#include <hub.h>

#include <mcallbattle.h>

#include "../singleton.h"
#include "../battle/battle.h"

namespace battle {

class match_msg {
public:
    std::shared_ptr<abelkhan::match_battle_module> _module;

public:
    match_msg(std::shared_ptr<hub::hub_service> _hub) {
        _module = std::make_shared<abelkhan::match_battle_module>();
        _module->Init(_hub);
    }

    void Init() {
        _module->sig_create_room.connect([this](std::vector<abelkhan::team> battle_team_list) {
            spdlog::trace("create_room begin!");

            auto rsp = std::static_pointer_cast<abelkhan::match_battle_create_room_rsp>(_module->rsp);
            auto _battle = _singleton_handle->_battle_mng_handle->create_battle(_singleton_handle->_hub_handle->_hubmng->current_hubproxy->_hub_name, battle_team_list);

            rsp->rsp(
                _battle->room_id,
                _singleton_handle->_hub_handle->websocket_address_info->host,
                (int32_t)_singleton_handle->_hub_handle->websocket_address_info->port,
                _singleton_handle->_battle_mng_handle->check_is_busy());

            spdlog::trace("create_room end!");
        });
    }
};

}

#endif //_match_msg_h