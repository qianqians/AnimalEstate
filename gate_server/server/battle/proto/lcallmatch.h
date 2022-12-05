#ifndef _h_lcallmatch_6bdc160b_695b_3df8_bc8b_af9f6f7e2500_
#define _h_lcallmatch_6bdc160b_695b_3df8_bc8b_af9f6f7e2500_

#include <hub_service.h>
#include <signals.h>

#include "common.h"

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this caller code is codegen by abelkhan codegen for cpp*/
    class lobby_match_rsp_cb;
    class lobby_match_create_team_cb : public std::enable_shared_from_this<lobby_match_create_team_cb>{
    private:
        uint64_t cb_uuid;
        std::shared_ptr<lobby_match_rsp_cb> module_rsp_cb;

    public:
        lobby_match_create_team_cb(uint64_t _cb_uuid, std::shared_ptr<lobby_match_rsp_cb> _module_rsp_cb);
    public:
        concurrent::signals<void(match_team)> sig_create_team_cb;
        concurrent::signals<void(int32_t)> sig_create_team_err;
        concurrent::signals<void()> sig_create_team_timeout;

        std::shared_ptr<lobby_match_create_team_cb> callBack(std::function<void(match_team team_info)> cb, std::function<void(int32_t err)> err);
        void timeout(uint64_t tick, std::function<void()> timeout_cb);
    };

    class lobby_match_rsp_cb;
    class lobby_match_agree_join_team_cb : public std::enable_shared_from_this<lobby_match_agree_join_team_cb>{
    private:
        uint64_t cb_uuid;
        std::shared_ptr<lobby_match_rsp_cb> module_rsp_cb;

    public:
        lobby_match_agree_join_team_cb(uint64_t _cb_uuid, std::shared_ptr<lobby_match_rsp_cb> _module_rsp_cb);
    public:
        concurrent::signals<void(match_team)> sig_agree_join_team_cb;
        concurrent::signals<void(int32_t)> sig_agree_join_team_err;
        concurrent::signals<void()> sig_agree_join_team_timeout;

        std::shared_ptr<lobby_match_agree_join_team_cb> callBack(std::function<void(match_team team_info)> cb, std::function<void(int32_t err)> err);
        void timeout(uint64_t tick, std::function<void()> timeout_cb);
    };

/*this cb code is codegen by abelkhan for cpp*/
    class lobby_match_rsp_cb : public common::imodule, public std::enable_shared_from_this<lobby_match_rsp_cb>{
    public:
        std::mutex mutex_map_create_team;
        std::unordered_map<uint64_t, std::shared_ptr<lobby_match_create_team_cb> > map_create_team;
        std::mutex mutex_map_agree_join_team;
        std::unordered_map<uint64_t, std::shared_ptr<lobby_match_agree_join_team_cb> > map_agree_join_team;
        lobby_match_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            _hub_service->modules.add_mothed("lobby_match_rsp_cb_create_team_rsp", std::bind(&lobby_match_rsp_cb::create_team_rsp, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("lobby_match_rsp_cb_create_team_err", std::bind(&lobby_match_rsp_cb::create_team_err, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("lobby_match_rsp_cb_agree_join_team_rsp", std::bind(&lobby_match_rsp_cb::agree_join_team_rsp, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("lobby_match_rsp_cb_agree_join_team_err", std::bind(&lobby_match_rsp_cb::agree_join_team_err, this, std::placeholders::_1));
        }

        void create_team_rsp(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto _team_info = match_team::protcol_to_match_team(inArray[1].object_items());
            auto rsp = try_get_and_del_create_team_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_create_team_cb.emit(_team_info);
            }
        }

        void create_team_err(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto _err = inArray[1].int32_value();
            auto rsp = try_get_and_del_create_team_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_create_team_err.emit(_err);
            }
        }

        void create_team_timeout(uint64_t cb_uuid){
            auto rsp = try_get_and_del_create_team_cb(cb_uuid);
            if (rsp != nullptr){
                rsp->sig_create_team_timeout.emit();
            }
        }

        std::shared_ptr<lobby_match_create_team_cb> try_get_and_del_create_team_cb(uint64_t uuid){
            std::lock_guard<std::mutex> l(mutex_map_create_team);
            if (map_create_team.find(uuid) != map_create_team.end()) {
                auto rsp = map_create_team[uuid];
                map_create_team.erase(uuid);
                return rsp;
            }
            return nullptr;
        }

        void agree_join_team_rsp(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto _team_info = match_team::protcol_to_match_team(inArray[1].object_items());
            auto rsp = try_get_and_del_agree_join_team_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_agree_join_team_cb.emit(_team_info);
            }
        }

        void agree_join_team_err(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto _err = inArray[1].int32_value();
            auto rsp = try_get_and_del_agree_join_team_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_agree_join_team_err.emit(_err);
            }
        }

        void agree_join_team_timeout(uint64_t cb_uuid){
            auto rsp = try_get_and_del_agree_join_team_cb(cb_uuid);
            if (rsp != nullptr){
                rsp->sig_agree_join_team_timeout.emit();
            }
        }

        std::shared_ptr<lobby_match_agree_join_team_cb> try_get_and_del_agree_join_team_cb(uint64_t uuid){
            std::lock_guard<std::mutex> l(mutex_map_agree_join_team);
            if (map_agree_join_team.find(uuid) != map_agree_join_team.end()) {
                auto rsp = map_agree_join_team[uuid];
                map_agree_join_team.erase(uuid);
                return rsp;
            }
            return nullptr;
        }

    };

    class lobby_match_hubproxy {
    public:
        std::string hub_name_b0a203a6_02bf_3843_ad2b_6f47eaac2bb1;

    private:
        std::atomic<uint64_t> uuid_b0a203a6_02bf_3843_ad2b_6f47eaac2bb1;
        std::shared_ptr<hub::hub_service> _hub_service;
        std::shared_ptr<lobby_match_rsp_cb> rsp_cb_lobby_match_handle;

    public:
        lobby_match_hubproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_match_rsp_cb> rsp_cb_lobby_match_handle_)
        {
            _hub_service = hub_service_;
            rsp_cb_lobby_match_handle = rsp_cb_lobby_match_handle_;

            uuid_b0a203a6_02bf_3843_ad2b_6f47eaac2bb1.store(random());
        }

        std::shared_ptr<lobby_match_create_team_cb> create_team(team_member leader){
            auto uuid_cc248fd2_32de_538a_bd33_e067e2904169 = uuid_b0a203a6_02bf_3843_ad2b_6f47eaac2bb1++;
            msgpack11::MsgPack::array _argv_c7a044a4_2986_34d5_91e9_b7fc9650e953;
            _argv_c7a044a4_2986_34d5_91e9_b7fc9650e953.push_back(uuid_cc248fd2_32de_538a_bd33_e067e2904169);
            _argv_c7a044a4_2986_34d5_91e9_b7fc9650e953.push_back(team_member::team_member_to_protcol(leader));
            _hub_service->_hubmng->call_hub(hub_name_b0a203a6_02bf_3843_ad2b_6f47eaac2bb1, "lobby_match_create_team", _argv_c7a044a4_2986_34d5_91e9_b7fc9650e953);

            auto cb_create_team_obj = std::make_shared<lobby_match_create_team_cb>(uuid_cc248fd2_32de_538a_bd33_e067e2904169, rsp_cb_lobby_match_handle);
            std::lock_guard<std::mutex> l(rsp_cb_lobby_match_handle->mutex_map_create_team);
            rsp_cb_lobby_match_handle->map_create_team.insert(std::make_pair(uuid_cc248fd2_32de_538a_bd33_e067e2904169, cb_create_team_obj));
            return cb_create_team_obj;
        }

        std::shared_ptr<lobby_match_agree_join_team_cb> agree_join_team(std::string team_id, team_member member){
            auto uuid_a1f36643_d727_5e90_9f1f_a24b980918b0 = uuid_b0a203a6_02bf_3843_ad2b_6f47eaac2bb1++;
            msgpack11::MsgPack::array _argv_e9c0865a_dff1_3200_85d2_d513428d7fb8;
            _argv_e9c0865a_dff1_3200_85d2_d513428d7fb8.push_back(uuid_a1f36643_d727_5e90_9f1f_a24b980918b0);
            _argv_e9c0865a_dff1_3200_85d2_d513428d7fb8.push_back(team_id);
            _argv_e9c0865a_dff1_3200_85d2_d513428d7fb8.push_back(team_member::team_member_to_protcol(member));
            _hub_service->_hubmng->call_hub(hub_name_b0a203a6_02bf_3843_ad2b_6f47eaac2bb1, "lobby_match_agree_join_team", _argv_e9c0865a_dff1_3200_85d2_d513428d7fb8);

            auto cb_agree_join_team_obj = std::make_shared<lobby_match_agree_join_team_cb>(uuid_a1f36643_d727_5e90_9f1f_a24b980918b0, rsp_cb_lobby_match_handle);
            std::lock_guard<std::mutex> l(rsp_cb_lobby_match_handle->mutex_map_agree_join_team);
            rsp_cb_lobby_match_handle->map_agree_join_team.insert(std::make_pair(uuid_a1f36643_d727_5e90_9f1f_a24b980918b0, cb_agree_join_team_obj));
            return cb_agree_join_team_obj;
        }

    };
    class lobby_match_caller {
    private:
        static std::shared_ptr<lobby_match_rsp_cb> rsp_cb_lobby_match_handle;

    private:
        std::shared_ptr<lobby_match_hubproxy> _hubproxy;

    public:
        lobby_match_caller(std::shared_ptr<hub::hub_service> _hub_service)
        {
            if (rsp_cb_lobby_match_handle == nullptr){
                rsp_cb_lobby_match_handle = std::make_shared<lobby_match_rsp_cb>();
                rsp_cb_lobby_match_handle->Init(_hub_service);
            }
            _hubproxy = std::make_shared<lobby_match_hubproxy>(_hub_service, rsp_cb_lobby_match_handle);
        }

        std::shared_ptr<lobby_match_hubproxy> get_hub(std::string hub_name) {
            _hubproxy->hub_name_b0a203a6_02bf_3843_ad2b_6f47eaac2bb1 = hub_name;
            return _hubproxy;
        }

    };

/*this cb code is codegen by abelkhan for cpp*/
    class match_lobby_rsp_cb : public common::imodule, public std::enable_shared_from_this<match_lobby_rsp_cb>{
    public:
        match_lobby_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class match_lobby_hubproxy {
    public:
        std::string hub_name_768c4683_c9d6_370d_89be_93d9c4df52c1;

    private:
        std::atomic<uint64_t> uuid_768c4683_c9d6_370d_89be_93d9c4df52c1;
        std::shared_ptr<hub::hub_service> _hub_service;
        std::shared_ptr<match_lobby_rsp_cb> rsp_cb_match_lobby_handle;

    public:
        match_lobby_hubproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<match_lobby_rsp_cb> rsp_cb_match_lobby_handle_)
        {
            _hub_service = hub_service_;
            rsp_cb_match_lobby_handle = rsp_cb_match_lobby_handle_;

            uuid_768c4683_c9d6_370d_89be_93d9c4df52c1.store(random());
        }

        void reg_match(int32_t team_role_num){
            msgpack11::MsgPack::array _argv_61e74cb7_02f2_34d0_a3ae_372ffdfe2ced;
            _argv_61e74cb7_02f2_34d0_a3ae_372ffdfe2ced.push_back(team_role_num);
            _hub_service->_hubmng->call_hub(hub_name_768c4683_c9d6_370d_89be_93d9c4df52c1, "match_lobby_reg_match", _argv_61e74cb7_02f2_34d0_a3ae_372ffdfe2ced);
        }

    };
    class match_lobby_caller {
    private:
        static std::shared_ptr<match_lobby_rsp_cb> rsp_cb_match_lobby_handle;

    private:
        std::shared_ptr<match_lobby_hubproxy> _hubproxy;

    public:
        match_lobby_caller(std::shared_ptr<hub::hub_service> _hub_service)
        {
            if (rsp_cb_match_lobby_handle == nullptr){
                rsp_cb_match_lobby_handle = std::make_shared<match_lobby_rsp_cb>();
                rsp_cb_match_lobby_handle->Init(_hub_service);
            }
            _hubproxy = std::make_shared<match_lobby_hubproxy>(_hub_service, rsp_cb_match_lobby_handle);
        }

        std::shared_ptr<match_lobby_hubproxy> get_hub(std::string hub_name) {
            _hubproxy->hub_name_768c4683_c9d6_370d_89be_93d9c4df52c1 = hub_name;
            return _hubproxy;
        }

    };

/*this module code is codegen by abelkhan codegen for cpp*/
    class lobby_match_create_team_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _hub_name_09c0dc59_61a6_3f59_8d7d_b23226768361;
        uint64_t uuid_c7a044a4_2986_34d5_91e9_b7fc9650e953;

    public:
        lobby_match_create_team_rsp(std::shared_ptr<hub::hub_service> _hub, std::string hub_name, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _hub_name_09c0dc59_61a6_3f59_8d7d_b23226768361 = hub_name;
            uuid_c7a044a4_2986_34d5_91e9_b7fc9650e953 = _uuid;
        }

        void rsp(match_team team_info){
            msgpack11::MsgPack::array _argv_09c0dc59_61a6_3f59_8d7d_b23226768361;
            _argv_09c0dc59_61a6_3f59_8d7d_b23226768361.push_back(uuid_c7a044a4_2986_34d5_91e9_b7fc9650e953);
            _argv_09c0dc59_61a6_3f59_8d7d_b23226768361.push_back(match_team::match_team_to_protcol(team_info));
            _hub_handle->_hubmng->call_hub(_hub_name_09c0dc59_61a6_3f59_8d7d_b23226768361, "lobby_match_rsp_cb_create_team_rsp", _argv_09c0dc59_61a6_3f59_8d7d_b23226768361);
        }

        void err(int32_t err){
            msgpack11::MsgPack::array _argv_09c0dc59_61a6_3f59_8d7d_b23226768361;
            _argv_09c0dc59_61a6_3f59_8d7d_b23226768361.push_back(uuid_c7a044a4_2986_34d5_91e9_b7fc9650e953);
            _argv_09c0dc59_61a6_3f59_8d7d_b23226768361.push_back(err);
            _hub_handle->_hubmng->call_hub(_hub_name_09c0dc59_61a6_3f59_8d7d_b23226768361, "lobby_match_rsp_cb_create_team_err", _argv_09c0dc59_61a6_3f59_8d7d_b23226768361);
        }

    };

    class lobby_match_agree_join_team_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _hub_name_0b5227cf_d7a5_34c3_9984_83f2137a2d91;
        uint64_t uuid_e9c0865a_dff1_3200_85d2_d513428d7fb8;

    public:
        lobby_match_agree_join_team_rsp(std::shared_ptr<hub::hub_service> _hub, std::string hub_name, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _hub_name_0b5227cf_d7a5_34c3_9984_83f2137a2d91 = hub_name;
            uuid_e9c0865a_dff1_3200_85d2_d513428d7fb8 = _uuid;
        }

        void rsp(match_team team_info){
            msgpack11::MsgPack::array _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91;
            _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91.push_back(uuid_e9c0865a_dff1_3200_85d2_d513428d7fb8);
            _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91.push_back(match_team::match_team_to_protcol(team_info));
            _hub_handle->_hubmng->call_hub(_hub_name_0b5227cf_d7a5_34c3_9984_83f2137a2d91, "lobby_match_rsp_cb_agree_join_team_rsp", _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91);
        }

        void err(int32_t err){
            msgpack11::MsgPack::array _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91;
            _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91.push_back(uuid_e9c0865a_dff1_3200_85d2_d513428d7fb8);
            _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91.push_back(err);
            _hub_handle->_hubmng->call_hub(_hub_name_0b5227cf_d7a5_34c3_9984_83f2137a2d91, "lobby_match_rsp_cb_agree_join_team_err", _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91);
        }

    };

    class lobby_match_module : public common::imodule, public std::enable_shared_from_this<lobby_match_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        lobby_match_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("lobby_match_create_team", std::bind(&lobby_match_module::create_team, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("lobby_match_agree_join_team", std::bind(&lobby_match_module::agree_join_team, this, std::placeholders::_1));
        }

        concurrent::signals<void(team_member)> sig_create_team;
        void create_team(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            auto _leader = team_member::protcol_to_team_member(inArray[1].object_items());
            rsp = std::make_shared<lobby_match_create_team_rsp>(hub_handle, hub_handle->_hubmng->current_hubproxy->_hub_name, _cb_uuid);
            sig_create_team.emit(_leader);
            rsp = nullptr;
        }

        concurrent::signals<void(std::string, team_member)> sig_agree_join_team;
        void agree_join_team(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            auto _team_id = inArray[1].string_value();
            auto _member = team_member::protcol_to_team_member(inArray[2].object_items());
            rsp = std::make_shared<lobby_match_agree_join_team_rsp>(hub_handle, hub_handle->_hubmng->current_hubproxy->_hub_name, _cb_uuid);
            sig_agree_join_team.emit(_team_id, _member);
            rsp = nullptr;
        }

    };
    class match_lobby_module : public common::imodule, public std::enable_shared_from_this<match_lobby_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        match_lobby_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("match_lobby_reg_match", std::bind(&match_lobby_module::reg_match, this, std::placeholders::_1));
        }

        concurrent::signals<void(int32_t)> sig_reg_match;
        void reg_match(const msgpack11::MsgPack::array& inArray){
            auto _team_role_num = inArray[0].int32_value();
            sig_reg_match.emit(_team_role_num);
        }

    };

}

#endif //_h_lcallmatch_6bdc160b_695b_3df8_bc8b_af9f6f7e2500_
