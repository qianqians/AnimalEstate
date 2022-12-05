#ifndef _h_mcallbattle_767e27e5_d761_31df_bea2_1dcf944b1cf9_
#define _h_mcallbattle_767e27e5_d761_31df_bea2_1dcf944b1cf9_

#include <hub_service.h>
#include <signals.h>

#include "common.h"

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this caller code is codegen by abelkhan codegen for cpp*/
    class match_battle_rsp_cb;
    class match_battle_create_room_cb : public std::enable_shared_from_this<match_battle_create_room_cb>{
    private:
        uint64_t cb_uuid;
        std::shared_ptr<match_battle_rsp_cb> module_rsp_cb;

    public:
        match_battle_create_room_cb(uint64_t _cb_uuid, std::shared_ptr<match_battle_rsp_cb> _module_rsp_cb);
    public:
        concurrent::signals<void(std::string, std::string, int32_t, bool)> sig_create_room_cb;
        concurrent::signals<void(int32_t)> sig_create_room_err;
        concurrent::signals<void()> sig_create_room_timeout;

        std::shared_ptr<match_battle_create_room_cb> callBack(std::function<void(std::string room_id, std::string host, int32_t port, bool is_busy)> cb, std::function<void(int32_t err)> err);
        void timeout(uint64_t tick, std::function<void()> timeout_cb);
    };

/*this cb code is codegen by abelkhan for cpp*/
    class match_battle_rsp_cb : public common::imodule, public std::enable_shared_from_this<match_battle_rsp_cb>{
    public:
        std::mutex mutex_map_create_room;
        std::unordered_map<uint64_t, std::shared_ptr<match_battle_create_room_cb> > map_create_room;
        match_battle_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            _hub_service->modules.add_mothed("match_battle_rsp_cb_create_room_rsp", std::bind(&match_battle_rsp_cb::create_room_rsp, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("match_battle_rsp_cb_create_room_err", std::bind(&match_battle_rsp_cb::create_room_err, this, std::placeholders::_1));
        }

        void create_room_rsp(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto _room_id = inArray[1].string_value();
            auto _host = inArray[2].string_value();
            auto _port = inArray[3].int32_value();
            auto _is_busy = inArray[4].bool_value();
            auto rsp = try_get_and_del_create_room_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_create_room_cb.emit(_room_id, _host, _port, _is_busy);
            }
        }

        void create_room_err(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto _err = inArray[1].int32_value();
            auto rsp = try_get_and_del_create_room_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_create_room_err.emit(_err);
            }
        }

        void create_room_timeout(uint64_t cb_uuid){
            auto rsp = try_get_and_del_create_room_cb(cb_uuid);
            if (rsp != nullptr){
                rsp->sig_create_room_timeout.emit();
            }
        }

        std::shared_ptr<match_battle_create_room_cb> try_get_and_del_create_room_cb(uint64_t uuid){
            std::lock_guard<std::mutex> l(mutex_map_create_room);
            if (map_create_room.find(uuid) != map_create_room.end()) {
                auto rsp = map_create_room[uuid];
                map_create_room.erase(uuid);
                return rsp;
            }
            return nullptr;
        }

    };

    class match_battle_hubproxy {
    public:
        std::string hub_name_05055ba2_6d36_36bc_b92f_d14ef45d5529;

    private:
        std::atomic<uint64_t> uuid_05055ba2_6d36_36bc_b92f_d14ef45d5529;
        std::shared_ptr<hub::hub_service> _hub_service;
        std::shared_ptr<match_battle_rsp_cb> rsp_cb_match_battle_handle;

    public:
        match_battle_hubproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<match_battle_rsp_cb> rsp_cb_match_battle_handle_)
        {
            _hub_service = hub_service_;
            rsp_cb_match_battle_handle = rsp_cb_match_battle_handle_;

            uuid_05055ba2_6d36_36bc_b92f_d14ef45d5529.store(random());
        }

        std::shared_ptr<match_battle_create_room_cb> create_room(std::vector<team> battle_team_list){
            auto uuid_596b5288_d0f2_52ea_802a_a61621d93808 = uuid_05055ba2_6d36_36bc_b92f_d14ef45d5529++;
            msgpack11::MsgPack::array _argv_23854e65_5189_3f0a_a35a_e9ce5a5cd896;
            _argv_23854e65_5189_3f0a_a35a_e9ce5a5cd896.push_back(uuid_596b5288_d0f2_52ea_802a_a61621d93808);
            msgpack11::MsgPack::array _array_0220e335_edfb_37ff_b934_5cccd315065a;
            for(auto v_ce5a1f6e_6e83_5194_b735_f1e3bd3fa845 : battle_team_list){
                _array_0220e335_edfb_37ff_b934_5cccd315065a.push_back(team::team_to_protcol(v_ce5a1f6e_6e83_5194_b735_f1e3bd3fa845));
            }
            _argv_23854e65_5189_3f0a_a35a_e9ce5a5cd896.push_back(_array_0220e335_edfb_37ff_b934_5cccd315065a);
            _hub_service->_hubmng->call_hub(hub_name_05055ba2_6d36_36bc_b92f_d14ef45d5529, "match_battle_create_room", _argv_23854e65_5189_3f0a_a35a_e9ce5a5cd896);

            auto cb_create_room_obj = std::make_shared<match_battle_create_room_cb>(uuid_596b5288_d0f2_52ea_802a_a61621d93808, rsp_cb_match_battle_handle);
            std::lock_guard<std::mutex> l(rsp_cb_match_battle_handle->mutex_map_create_room);
            rsp_cb_match_battle_handle->map_create_room.insert(std::make_pair(uuid_596b5288_d0f2_52ea_802a_a61621d93808, cb_create_room_obj));
            return cb_create_room_obj;
        }

    };
    class match_battle_caller {
    private:
        static std::shared_ptr<match_battle_rsp_cb> rsp_cb_match_battle_handle;

    private:
        std::shared_ptr<match_battle_hubproxy> _hubproxy;

    public:
        match_battle_caller(std::shared_ptr<hub::hub_service> _hub_service)
        {
            if (rsp_cb_match_battle_handle == nullptr){
                rsp_cb_match_battle_handle = std::make_shared<match_battle_rsp_cb>();
                rsp_cb_match_battle_handle->Init(_hub_service);
            }
            _hubproxy = std::make_shared<match_battle_hubproxy>(_hub_service, rsp_cb_match_battle_handle);
        }

        std::shared_ptr<match_battle_hubproxy> get_hub(std::string hub_name) {
            _hubproxy->hub_name_05055ba2_6d36_36bc_b92f_d14ef45d5529 = hub_name;
            return _hubproxy;
        }

    };

/*this module code is codegen by abelkhan codegen for cpp*/
    class match_battle_create_room_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _hub_name_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee;
        uint64_t uuid_23854e65_5189_3f0a_a35a_e9ce5a5cd896;

    public:
        match_battle_create_room_rsp(std::shared_ptr<hub::hub_service> _hub, std::string hub_name, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _hub_name_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee = hub_name;
            uuid_23854e65_5189_3f0a_a35a_e9ce5a5cd896 = _uuid;
        }

        void rsp(std::string room_id, std::string host, int32_t port, bool is_busy){
            msgpack11::MsgPack::array _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee;
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.push_back(uuid_23854e65_5189_3f0a_a35a_e9ce5a5cd896);
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.push_back(room_id);
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.push_back(host);
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.push_back(port);
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.push_back(is_busy);
            _hub_handle->_hubmng->call_hub(_hub_name_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee, "match_battle_rsp_cb_create_room_rsp", _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee);
        }

        void err(int32_t err){
            msgpack11::MsgPack::array _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee;
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.push_back(uuid_23854e65_5189_3f0a_a35a_e9ce5a5cd896);
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.push_back(err);
            _hub_handle->_hubmng->call_hub(_hub_name_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee, "match_battle_rsp_cb_create_room_err", _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee);
        }

    };

    class match_battle_module : public common::imodule, public std::enable_shared_from_this<match_battle_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        match_battle_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("match_battle_create_room", std::bind(&match_battle_module::create_room, this, std::placeholders::_1));
        }

        concurrent::signals<void(std::vector<team>)> sig_create_room;
        void create_room(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            std::vector<team> _battle_team_list;
            auto _protocol_arraybattle_team_list = inArray[1].array_items();
            for(auto it_deeab8f7_cf12_5d75_a6ff_b688bc019b44 : _protocol_arraybattle_team_list){
                _battle_team_list.push_back(team::protcol_to_team(it_deeab8f7_cf12_5d75_a6ff_b688bc019b44.object_items()));
            }
            rsp = std::make_shared<match_battle_create_room_rsp>(hub_handle, hub_handle->_hubmng->current_hubproxy->_hub_name, _cb_uuid);
            sig_create_room.emit(_battle_team_list);
            rsp = nullptr;
        }

    };

}

#endif //_h_mcallbattle_767e27e5_d761_31df_bea2_1dcf944b1cf9_
