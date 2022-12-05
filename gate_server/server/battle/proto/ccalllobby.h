#ifndef _h_ccalllobby_8c33abd5_fa3f_386a_9f23_accf5124bf51_
#define _h_ccalllobby_8c33abd5_fa3f_386a_9f23_accf5124bf51_

#include <hub_service.h>
#include <signals.h>

#include "common.h"

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this module code is codegen by abelkhan codegen for cpp*/
    class login_create_role_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _client_cuuid_30293c4a_8f5b_307e_a08a_ff76e003f95d;
        uint64_t uuid_9b570d40_93db_3172_b2b2_238a3ebca94b;

    public:
        login_create_role_rsp(std::shared_ptr<hub::hub_service> _hub, std::string client_cuuid, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _client_cuuid_30293c4a_8f5b_307e_a08a_ff76e003f95d = client_cuuid;
            uuid_9b570d40_93db_3172_b2b2_238a3ebca94b = _uuid;
        }

        void rsp(role_lobby_info _info){
            msgpack11::MsgPack::array _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d;
            _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d.push_back(uuid_9b570d40_93db_3172_b2b2_238a3ebca94b);
            _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d.push_back(role_lobby_info::role_lobby_info_to_protcol(_info));
            _hub_handle->_gatemng->call_client(_client_cuuid_30293c4a_8f5b_307e_a08a_ff76e003f95d, "login_rsp_cb_create_role_rsp", _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d);
        }

        void err(int32_t err){
            msgpack11::MsgPack::array _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d;
            _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d.push_back(uuid_9b570d40_93db_3172_b2b2_238a3ebca94b);
            _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d.push_back(err);
            _hub_handle->_gatemng->call_client(_client_cuuid_30293c4a_8f5b_307e_a08a_ff76e003f95d, "login_rsp_cb_create_role_err", _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d);
        }

    };

    class login_module : public common::imodule, public std::enable_shared_from_this<login_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        login_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("login_login_no_author", std::bind(&login_module::login_no_author, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("login_create_role", std::bind(&login_module::create_role, this, std::placeholders::_1));
        }

        concurrent::signals<void()> sig_login_no_author;
        void login_no_author(const msgpack11::MsgPack::array& inArray){
            sig_login_no_author.emit();
        }

        concurrent::signals<void(std::string, int32_t, int32_t, int32_t)> sig_create_role;
        void create_role(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            auto _name = inArray[1].string_value();
            auto _head_id = inArray[2].int32_value();
            auto _body_id = inArray[3].int32_value();
            auto _foot_id = inArray[4].int32_value();
            rsp = std::make_shared<login_create_role_rsp>(hub_handle, hub_handle->_gatemng->current_client_cuuid, _cb_uuid);
            sig_create_role.emit(_name, _head_id, _body_id, _foot_id);
            rsp = nullptr;
        }

    };
    class client_team_lobby_create_team_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _client_cuuid_09c0dc59_61a6_3f59_8d7d_b23226768361;
        uint64_t uuid_c7a044a4_2986_34d5_91e9_b7fc9650e953;

    public:
        client_team_lobby_create_team_rsp(std::shared_ptr<hub::hub_service> _hub, std::string client_cuuid, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _client_cuuid_09c0dc59_61a6_3f59_8d7d_b23226768361 = client_cuuid;
            uuid_c7a044a4_2986_34d5_91e9_b7fc9650e953 = _uuid;
        }

        void rsp(std::string match_hub_name, match_team team_info){
            msgpack11::MsgPack::array _argv_09c0dc59_61a6_3f59_8d7d_b23226768361;
            _argv_09c0dc59_61a6_3f59_8d7d_b23226768361.push_back(uuid_c7a044a4_2986_34d5_91e9_b7fc9650e953);
            _argv_09c0dc59_61a6_3f59_8d7d_b23226768361.push_back(match_hub_name);
            _argv_09c0dc59_61a6_3f59_8d7d_b23226768361.push_back(match_team::match_team_to_protcol(team_info));
            _hub_handle->_gatemng->call_client(_client_cuuid_09c0dc59_61a6_3f59_8d7d_b23226768361, "client_team_lobby_rsp_cb_create_team_rsp", _argv_09c0dc59_61a6_3f59_8d7d_b23226768361);
        }

        void err(int32_t err){
            msgpack11::MsgPack::array _argv_09c0dc59_61a6_3f59_8d7d_b23226768361;
            _argv_09c0dc59_61a6_3f59_8d7d_b23226768361.push_back(uuid_c7a044a4_2986_34d5_91e9_b7fc9650e953);
            _argv_09c0dc59_61a6_3f59_8d7d_b23226768361.push_back(err);
            _hub_handle->_gatemng->call_client(_client_cuuid_09c0dc59_61a6_3f59_8d7d_b23226768361, "client_team_lobby_rsp_cb_create_team_err", _argv_09c0dc59_61a6_3f59_8d7d_b23226768361);
        }

    };

    class client_team_lobby_agree_join_team_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _client_cuuid_0b5227cf_d7a5_34c3_9984_83f2137a2d91;
        uint64_t uuid_e9c0865a_dff1_3200_85d2_d513428d7fb8;

    public:
        client_team_lobby_agree_join_team_rsp(std::shared_ptr<hub::hub_service> _hub, std::string client_cuuid, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _client_cuuid_0b5227cf_d7a5_34c3_9984_83f2137a2d91 = client_cuuid;
            uuid_e9c0865a_dff1_3200_85d2_d513428d7fb8 = _uuid;
        }

        void rsp(std::string match_hub_name, match_team team_info){
            msgpack11::MsgPack::array _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91;
            _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91.push_back(uuid_e9c0865a_dff1_3200_85d2_d513428d7fb8);
            _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91.push_back(match_hub_name);
            _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91.push_back(match_team::match_team_to_protcol(team_info));
            _hub_handle->_gatemng->call_client(_client_cuuid_0b5227cf_d7a5_34c3_9984_83f2137a2d91, "client_team_lobby_rsp_cb_agree_join_team_rsp", _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91);
        }

        void err(int32_t err){
            msgpack11::MsgPack::array _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91;
            _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91.push_back(uuid_e9c0865a_dff1_3200_85d2_d513428d7fb8);
            _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91.push_back(err);
            _hub_handle->_gatemng->call_client(_client_cuuid_0b5227cf_d7a5_34c3_9984_83f2137a2d91, "client_team_lobby_rsp_cb_agree_join_team_err", _argv_0b5227cf_d7a5_34c3_9984_83f2137a2d91);
        }

    };

    class client_team_lobby_module : public common::imodule, public std::enable_shared_from_this<client_team_lobby_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        client_team_lobby_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("client_team_lobby_create_team", std::bind(&client_team_lobby_module::create_team, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("client_team_lobby_invite_role_join_team", std::bind(&client_team_lobby_module::invite_role_join_team, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("client_team_lobby_agree_join_team", std::bind(&client_team_lobby_module::agree_join_team, this, std::placeholders::_1));
        }

        concurrent::signals<void(int32_t)> sig_create_team;
        void create_team(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            auto _team_roel_num = inArray[1].int32_value();
            rsp = std::make_shared<client_team_lobby_create_team_rsp>(hub_handle, hub_handle->_gatemng->current_client_cuuid, _cb_uuid);
            sig_create_team.emit(_team_roel_num);
            rsp = nullptr;
        }

        concurrent::signals<void(std::string)> sig_invite_role_join_team;
        void invite_role_join_team(const msgpack11::MsgPack::array& inArray){
            auto _account = inArray[0].string_value();
            sig_invite_role_join_team.emit(_account);
        }

        concurrent::signals<void(int32_t, std::string)> sig_agree_join_team;
        void agree_join_team(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            auto _team_roel_num = inArray[1].int32_value();
            auto _team_id = inArray[2].string_value();
            rsp = std::make_shared<client_team_lobby_agree_join_team_rsp>(hub_handle, hub_handle->_gatemng->current_client_cuuid, _cb_uuid);
            sig_agree_join_team.emit(_team_roel_num, _team_id);
            rsp = nullptr;
        }

    };
    class client_friend_lobby_find_role_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _client_cuuid_ba126e3b_fd75_3aa1_a5be_1d096547ca8f;
        uint64_t uuid_7cf098ce_38ef_30c0_b061_6a65be582555;

    public:
        client_friend_lobby_find_role_rsp(std::shared_ptr<hub::hub_service> _hub, std::string client_cuuid, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _client_cuuid_ba126e3b_fd75_3aa1_a5be_1d096547ca8f = client_cuuid;
            uuid_7cf098ce_38ef_30c0_b061_6a65be582555 = _uuid;
        }

        void rsp(role_find_info find_info){
            msgpack11::MsgPack::array _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f;
            _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f.push_back(uuid_7cf098ce_38ef_30c0_b061_6a65be582555);
            _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f.push_back(role_find_info::role_find_info_to_protcol(find_info));
            _hub_handle->_gatemng->call_client(_client_cuuid_ba126e3b_fd75_3aa1_a5be_1d096547ca8f, "client_friend_lobby_rsp_cb_find_role_rsp", _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f);
        }

        void err(int32_t err){
            msgpack11::MsgPack::array _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f;
            _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f.push_back(uuid_7cf098ce_38ef_30c0_b061_6a65be582555);
            _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f.push_back(err);
            _hub_handle->_gatemng->call_client(_client_cuuid_ba126e3b_fd75_3aa1_a5be_1d096547ca8f, "client_friend_lobby_rsp_cb_find_role_err", _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f);
        }

    };

    class client_friend_lobby_module : public common::imodule, public std::enable_shared_from_this<client_friend_lobby_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        client_friend_lobby_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("client_friend_lobby_find_role", std::bind(&client_friend_lobby_module::find_role, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("client_friend_lobby_invite_role_friend", std::bind(&client_friend_lobby_module::invite_role_friend, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("client_friend_lobby_agree_role_friend", std::bind(&client_friend_lobby_module::agree_role_friend, this, std::placeholders::_1));
        }

        concurrent::signals<void(std::string)> sig_find_role;
        void find_role(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            auto _guid = inArray[1].string_value();
            rsp = std::make_shared<client_friend_lobby_find_role_rsp>(hub_handle, hub_handle->_gatemng->current_client_cuuid, _cb_uuid);
            sig_find_role.emit(_guid);
            rsp = nullptr;
        }

        concurrent::signals<void(role_friend_info, role_friend_info)> sig_invite_role_friend;
        void invite_role_friend(const msgpack11::MsgPack::array& inArray){
            auto _self_account = role_friend_info::protcol_to_role_friend_info(inArray[0].object_items());
            auto _target_account = role_friend_info::protcol_to_role_friend_info(inArray[1].object_items());
            sig_invite_role_friend.emit(_self_account, _target_account);
        }

        concurrent::signals<void(std::string, bool)> sig_agree_role_friend;
        void agree_role_friend(const msgpack11::MsgPack::array& inArray){
            auto _invite_account = inArray[0].string_value();
            auto _be_agree = inArray[1].bool_value();
            sig_agree_role_friend.emit(_invite_account, _be_agree);
        }

    };

}

#endif //_h_ccalllobby_8c33abd5_fa3f_386a_9f23_accf5124bf51_
