/*
 * qianqians
 * 2020-1-22
 * battle
 * server.cpp
 */
#include <hub.h>

#include <mimalloc-override.h>
#include <mimalloc-new-delete.h>

#include "singleton.h"
#include "call_mng.h"
#include "./battle/map_data.h"
#include "./json_config/json_config_mng.h"

#include "./msg_handle/match_msg.h"
#include "./msg_handle/client_battle_msg.h"

namespace battle {
    std::shared_ptr<singleton> _singleton_handle;
    std::shared_ptr<call_mng> _call_mng_handle;
}

void tick_busy(std::shared_ptr<hub::hub_service> _hub, std::string match_hub_name, uint64_t tick) {
    abelkhan::match_battle_info info;
    info.battle_hub_name = _hub->name_info.name;
    info.is_busy = battle::_singleton_handle->_battle_mng_handle->check_is_busy();
    battle::_call_mng_handle->battle_match_caller->get_hub(match_hub_name)->battle_info(info);
    
    _hub->_timerservice->addticktimer(60 * 1000, std::bind(tick_busy, _hub, match_hub_name, std::placeholders::_1));
};

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        spdlog::error("non input start argv");
        return 1;
    }

    std::string config_file_path = argv[1];
    std::string config_name = argv[2];

    auto _hub = std::make_shared<hub::hub_service>(config_file_path, config_name, "battle");
    _hub->init();

    std::vector<std::string> load_modules = { "item", "gun", "rpg", "bullet", "equip", "medicine", "drop_time", "drop_box", "poison", "buff", "skill"};
    json_config::_json_config_mng = std::make_shared<json_config::json_config_mng>(load_modules);

    battle::_singleton_handle = std::make_shared<battle::singleton>(_hub);
    battle::_call_mng_handle = std::make_shared<battle::call_mng>(_hub);

    battle::map_primitive_data("./server_map");

    battle::match_msg _match_msg(_hub);
    _match_msg.Init();
    battle::client_battle_msg _client_battle_msg(_hub);
    _client_battle_msg.Init();

    auto _singleton_handle = battle::_singleton_handle;

    _hub->sig_hub_connect.connect([_hub](std::shared_ptr<hub::hubproxy> hub_proxy) {
        spdlog::trace("sig_hub_connect hub_proxy->_hub_type:{0}", hub_proxy->_hub_type);

        if (hub_proxy->_hub_type == "match") {
            tick_busy(_hub, hub_proxy->_hub_name, _hub->_timerservice->Tick);
        }
        else if (hub_proxy->_hub_type == "lobby") {
            battle::_call_mng_handle->battle_lobby_caller->get_hub(hub_proxy->_hub_name)->reg_battle(_hub->websocket_address_info->host, _hub->websocket_address_info->port);
        }
    });

    _hub->sig_client_exception.connect([_singleton_handle](std::string uuid) {
        auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(uuid);
        if (!_role) {
            spdlog::trace("load_scene_done _role is empty!");
            return;
        }

        //_role->is_exception = true;
        spdlog::error("exception role account:{0} id:{1}", _role->account, _role->id);
    });

    _hub->sig_client_disconnect.connect([_singleton_handle](std::string uuid) {
        auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(uuid);
        if (!_role) {
            spdlog::trace("load_scene_done _role is empty!");
            return;
        }

        _role->is_leave_battle = true;
    });

    _hub->sig_client_msg.connect([_singleton_handle, _hub](std::string uuid) {
        auto _role = _singleton_handle->_role_mng_handle->get_role_by_uuid(uuid);
        if (!_role) {
            spdlog::trace("load_scene_done _role is empty!");
            return;
        }

        _role->last_active_timetmp = _hub->_timerservice->Tick;
    });

    _hub->sig_close_server.connect([_hub]() {
        _hub->close_svr();
    });

    _hub->connect_center();
    _hub->run();

    return 0;
}