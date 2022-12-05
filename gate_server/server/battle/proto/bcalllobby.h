#ifndef _h_bcalllobby_79154a91_06ae_37ec_a761_1a1c519cfb76_
#define _h_bcalllobby_79154a91_06ae_37ec_a761_1a1c519cfb76_

#include <hub_service.h>
#include <signals.h>

#include "common.h"

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this caller code is codegen by abelkhan codegen for cpp*/
/*this cb code is codegen by abelkhan for cpp*/
    class battle_lobby_rsp_cb : public common::imodule, public std::enable_shared_from_this<battle_lobby_rsp_cb>{
    public:
        battle_lobby_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class battle_lobby_hubproxy {
    public:
        std::string hub_name_a9ee8670_4666_358d_ac24_7da48307d020;

    private:
        std::atomic<uint64_t> uuid_a9ee8670_4666_358d_ac24_7da48307d020;
        std::shared_ptr<hub::hub_service> _hub_service;
        std::shared_ptr<battle_lobby_rsp_cb> rsp_cb_battle_lobby_handle;

    public:
        battle_lobby_hubproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<battle_lobby_rsp_cb> rsp_cb_battle_lobby_handle_)
        {
            _hub_service = hub_service_;
            rsp_cb_battle_lobby_handle = rsp_cb_battle_lobby_handle_;

            uuid_a9ee8670_4666_358d_ac24_7da48307d020.store(random());
        }

        void reg_battle(std::string host, int16_t port){
            msgpack11::MsgPack::array _argv_28b54dc8_3a3b_3934_96ff_a07741ebbeb7;
            _argv_28b54dc8_3a3b_3934_96ff_a07741ebbeb7.push_back(host);
            _argv_28b54dc8_3a3b_3934_96ff_a07741ebbeb7.push_back(port);
            _hub_service->_hubmng->call_hub(hub_name_a9ee8670_4666_358d_ac24_7da48307d020, "battle_lobby_reg_battle", _argv_28b54dc8_3a3b_3934_96ff_a07741ebbeb7);
        }

        void end_battle(std::string account, role_battle_end_info battle_end_info){
            msgpack11::MsgPack::array _argv_12fd17d3_1937_3241_ad95_532c02932439;
            _argv_12fd17d3_1937_3241_ad95_532c02932439.push_back(account);
            _argv_12fd17d3_1937_3241_ad95_532c02932439.push_back(role_battle_end_info::role_battle_end_info_to_protcol(battle_end_info));
            _hub_service->_hubmng->call_hub(hub_name_a9ee8670_4666_358d_ac24_7da48307d020, "battle_lobby_end_battle", _argv_12fd17d3_1937_3241_ad95_532c02932439);
        }

    };
    class battle_lobby_caller {
    private:
        static std::shared_ptr<battle_lobby_rsp_cb> rsp_cb_battle_lobby_handle;

    private:
        std::shared_ptr<battle_lobby_hubproxy> _hubproxy;

    public:
        battle_lobby_caller(std::shared_ptr<hub::hub_service> _hub_service)
        {
            if (rsp_cb_battle_lobby_handle == nullptr){
                rsp_cb_battle_lobby_handle = std::make_shared<battle_lobby_rsp_cb>();
                rsp_cb_battle_lobby_handle->Init(_hub_service);
            }
            _hubproxy = std::make_shared<battle_lobby_hubproxy>(_hub_service, rsp_cb_battle_lobby_handle);
        }

        std::shared_ptr<battle_lobby_hubproxy> get_hub(std::string hub_name) {
            _hubproxy->hub_name_a9ee8670_4666_358d_ac24_7da48307d020 = hub_name;
            return _hubproxy;
        }

    };

/*this module code is codegen by abelkhan codegen for cpp*/
    class battle_lobby_module : public common::imodule, public std::enable_shared_from_this<battle_lobby_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        battle_lobby_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("battle_lobby_reg_battle", std::bind(&battle_lobby_module::reg_battle, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_lobby_end_battle", std::bind(&battle_lobby_module::end_battle, this, std::placeholders::_1));
        }

        concurrent::signals<void(std::string, int16_t)> sig_reg_battle;
        void reg_battle(const msgpack11::MsgPack::array& inArray){
            auto _host = inArray[0].string_value();
            auto _port = inArray[1].int16_value();
            sig_reg_battle.emit(_host, _port);
        }

        concurrent::signals<void(std::string, role_battle_end_info)> sig_end_battle;
        void end_battle(const msgpack11::MsgPack::array& inArray){
            auto _account = inArray[0].string_value();
            auto _battle_end_info = role_battle_end_info::protcol_to_role_battle_end_info(inArray[1].object_items());
            sig_end_battle.emit(_account, _battle_end_info);
        }

    };

}

#endif //_h_bcalllobby_79154a91_06ae_37ec_a761_1a1c519cfb76_
