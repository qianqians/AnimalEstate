#ifndef _h_bcallmatch_d56d2148_eccd_3234_b502_03d0b098ce47_
#define _h_bcallmatch_d56d2148_eccd_3234_b502_03d0b098ce47_

#include <hub_service.h>
#include <signals.h>

#include "common.h"

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
    class match_battle_info {
    public:
        std::string battle_hub_name;
        bool is_busy;

    public:
        static msgpack11::MsgPack::object match_battle_info_to_protcol(match_battle_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("battle_hub_name", _struct.battle_hub_name));
            _protocol.insert(std::make_pair("is_busy", _struct.is_busy));
            return _protocol;
        }

        static match_battle_info protcol_to_match_battle_info(const msgpack11::MsgPack::object& _protocol){
            match_battle_info _struct70d4c29d_352a_38f0_ac8e_98fcfb795b32;
            for(auto i : _protocol){
                if (i.first == "battle_hub_name"){
                    _struct70d4c29d_352a_38f0_ac8e_98fcfb795b32.battle_hub_name = i.second.string_value();
                }
                else if (i.first == "is_busy"){
                    _struct70d4c29d_352a_38f0_ac8e_98fcfb795b32.is_busy = i.second.bool_value();
                }
            }
            return _struct70d4c29d_352a_38f0_ac8e_98fcfb795b32;
        }
    };

/*this caller code is codegen by abelkhan codegen for cpp*/
    class battle_match_rsp_cb;
    class battle_match_back_match_cb : public std::enable_shared_from_this<battle_match_back_match_cb>{
    private:
        uint64_t cb_uuid;
        std::shared_ptr<battle_match_rsp_cb> module_rsp_cb;

    public:
        battle_match_back_match_cb(uint64_t _cb_uuid, std::shared_ptr<battle_match_rsp_cb> _module_rsp_cb);
    public:
        concurrent::signals<void(std::string, match_team)> sig_back_match_cb;
        concurrent::signals<void(int32_t)> sig_back_match_err;
        concurrent::signals<void()> sig_back_match_timeout;

        std::shared_ptr<battle_match_back_match_cb> callBack(std::function<void(std::string match_hub_name, match_team team_info)> cb, std::function<void(int32_t err)> err);
        void timeout(uint64_t tick, std::function<void()> timeout_cb);
    };

/*this cb code is codegen by abelkhan for cpp*/
    class battle_match_rsp_cb : public common::imodule, public std::enable_shared_from_this<battle_match_rsp_cb>{
    public:
        std::mutex mutex_map_back_match;
        std::unordered_map<uint64_t, std::shared_ptr<battle_match_back_match_cb> > map_back_match;
        battle_match_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            _hub_service->modules.add_mothed("battle_match_rsp_cb_back_match_rsp", std::bind(&battle_match_rsp_cb::back_match_rsp, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_match_rsp_cb_back_match_err", std::bind(&battle_match_rsp_cb::back_match_err, this, std::placeholders::_1));
        }

        void back_match_rsp(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto _match_hub_name = inArray[1].string_value();
            auto _team_info = match_team::protcol_to_match_team(inArray[2].object_items());
            auto rsp = try_get_and_del_back_match_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_back_match_cb.emit(_match_hub_name, _team_info);
            }
        }

        void back_match_err(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto _err = inArray[1].int32_value();
            auto rsp = try_get_and_del_back_match_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_back_match_err.emit(_err);
            }
        }

        void back_match_timeout(uint64_t cb_uuid){
            auto rsp = try_get_and_del_back_match_cb(cb_uuid);
            if (rsp != nullptr){
                rsp->sig_back_match_timeout.emit();
            }
        }

        std::shared_ptr<battle_match_back_match_cb> try_get_and_del_back_match_cb(uint64_t uuid){
            std::lock_guard<std::mutex> l(mutex_map_back_match);
            if (map_back_match.find(uuid) != map_back_match.end()) {
                auto rsp = map_back_match[uuid];
                map_back_match.erase(uuid);
                return rsp;
            }
            return nullptr;
        }

    };

    class battle_match_hubproxy {
    public:
        std::string hub_name_ef520bea_4ff6_3e84_ac9b_89ff599f2c37;

    private:
        std::atomic<uint64_t> uuid_ef520bea_4ff6_3e84_ac9b_89ff599f2c37;
        std::shared_ptr<hub::hub_service> _hub_service;
        std::shared_ptr<battle_match_rsp_cb> rsp_cb_battle_match_handle;

    public:
        battle_match_hubproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<battle_match_rsp_cb> rsp_cb_battle_match_handle_)
        {
            _hub_service = hub_service_;
            rsp_cb_battle_match_handle = rsp_cb_battle_match_handle_;

            uuid_ef520bea_4ff6_3e84_ac9b_89ff599f2c37.store(random());
        }

        void battle_info(match_battle_info _battle_info){
            msgpack11::MsgPack::array _argv_504125a2_a75d_3fa2_9a35_a9fdc5331928;
            _argv_504125a2_a75d_3fa2_9a35_a9fdc5331928.push_back(match_battle_info::match_battle_info_to_protcol(_battle_info));
            _hub_service->_hubmng->call_hub(hub_name_ef520bea_4ff6_3e84_ac9b_89ff599f2c37, "battle_match_battle_info", _argv_504125a2_a75d_3fa2_9a35_a9fdc5331928);
        }

        std::shared_ptr<battle_match_back_match_cb> back_match(team team_info){
            auto uuid_e5ac2872_05b0_5f62_9404_d58fd6e03440 = uuid_ef520bea_4ff6_3e84_ac9b_89ff599f2c37++;
            msgpack11::MsgPack::array _argv_d8ad13dd_7fe0_3c70_8dce_625ee475377b;
            _argv_d8ad13dd_7fe0_3c70_8dce_625ee475377b.push_back(uuid_e5ac2872_05b0_5f62_9404_d58fd6e03440);
            _argv_d8ad13dd_7fe0_3c70_8dce_625ee475377b.push_back(team::team_to_protcol(team_info));
            _hub_service->_hubmng->call_hub(hub_name_ef520bea_4ff6_3e84_ac9b_89ff599f2c37, "battle_match_back_match", _argv_d8ad13dd_7fe0_3c70_8dce_625ee475377b);

            auto cb_back_match_obj = std::make_shared<battle_match_back_match_cb>(uuid_e5ac2872_05b0_5f62_9404_d58fd6e03440, rsp_cb_battle_match_handle);
            std::lock_guard<std::mutex> l(rsp_cb_battle_match_handle->mutex_map_back_match);
            rsp_cb_battle_match_handle->map_back_match.insert(std::make_pair(uuid_e5ac2872_05b0_5f62_9404_d58fd6e03440, cb_back_match_obj));
            return cb_back_match_obj;
        }

    };
    class battle_match_caller {
    private:
        static std::shared_ptr<battle_match_rsp_cb> rsp_cb_battle_match_handle;

    private:
        std::shared_ptr<battle_match_hubproxy> _hubproxy;

    public:
        battle_match_caller(std::shared_ptr<hub::hub_service> _hub_service)
        {
            if (rsp_cb_battle_match_handle == nullptr){
                rsp_cb_battle_match_handle = std::make_shared<battle_match_rsp_cb>();
                rsp_cb_battle_match_handle->Init(_hub_service);
            }
            _hubproxy = std::make_shared<battle_match_hubproxy>(_hub_service, rsp_cb_battle_match_handle);
        }

        std::shared_ptr<battle_match_hubproxy> get_hub(std::string hub_name) {
            _hubproxy->hub_name_ef520bea_4ff6_3e84_ac9b_89ff599f2c37 = hub_name;
            return _hubproxy;
        }

    };

/*this module code is codegen by abelkhan codegen for cpp*/
    class battle_match_back_match_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _hub_name_3e64467f_f3a9_3216_907f_0e9bfd6381fc;
        uint64_t uuid_d8ad13dd_7fe0_3c70_8dce_625ee475377b;

    public:
        battle_match_back_match_rsp(std::shared_ptr<hub::hub_service> _hub, std::string hub_name, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _hub_name_3e64467f_f3a9_3216_907f_0e9bfd6381fc = hub_name;
            uuid_d8ad13dd_7fe0_3c70_8dce_625ee475377b = _uuid;
        }

        void rsp(std::string match_hub_name, match_team team_info){
            msgpack11::MsgPack::array _argv_3e64467f_f3a9_3216_907f_0e9bfd6381fc;
            _argv_3e64467f_f3a9_3216_907f_0e9bfd6381fc.push_back(uuid_d8ad13dd_7fe0_3c70_8dce_625ee475377b);
            _argv_3e64467f_f3a9_3216_907f_0e9bfd6381fc.push_back(match_hub_name);
            _argv_3e64467f_f3a9_3216_907f_0e9bfd6381fc.push_back(match_team::match_team_to_protcol(team_info));
            _hub_handle->_hubmng->call_hub(_hub_name_3e64467f_f3a9_3216_907f_0e9bfd6381fc, "battle_match_rsp_cb_back_match_rsp", _argv_3e64467f_f3a9_3216_907f_0e9bfd6381fc);
        }

        void err(int32_t err){
            msgpack11::MsgPack::array _argv_3e64467f_f3a9_3216_907f_0e9bfd6381fc;
            _argv_3e64467f_f3a9_3216_907f_0e9bfd6381fc.push_back(uuid_d8ad13dd_7fe0_3c70_8dce_625ee475377b);
            _argv_3e64467f_f3a9_3216_907f_0e9bfd6381fc.push_back(err);
            _hub_handle->_hubmng->call_hub(_hub_name_3e64467f_f3a9_3216_907f_0e9bfd6381fc, "battle_match_rsp_cb_back_match_err", _argv_3e64467f_f3a9_3216_907f_0e9bfd6381fc);
        }

    };

    class battle_match_module : public common::imodule, public std::enable_shared_from_this<battle_match_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        battle_match_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("battle_match_battle_info", std::bind(&battle_match_module::battle_info, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_match_back_match", std::bind(&battle_match_module::back_match, this, std::placeholders::_1));
        }

        concurrent::signals<void(match_battle_info)> sig_battle_info;
        void battle_info(const msgpack11::MsgPack::array& inArray){
            auto __battle_info = match_battle_info::protcol_to_match_battle_info(inArray[0].object_items());
            sig_battle_info.emit(__battle_info);
        }

        concurrent::signals<void(team)> sig_back_match;
        void back_match(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            auto _team_info = team::protcol_to_team(inArray[1].object_items());
            rsp = std::make_shared<battle_match_back_match_rsp>(hub_handle, hub_handle->_hubmng->current_hubproxy->_hub_name, _cb_uuid);
            sig_back_match.emit(_team_info);
            rsp = nullptr;
        }

    };

}

#endif //_h_bcallmatch_d56d2148_eccd_3234_b502_03d0b098ce47_
