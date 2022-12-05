#ifndef _h_lcalllobby_6a4f4933_7ea7_3318_baec_98cd082feea5_
#define _h_lcalllobby_6a4f4933_7ea7_3318_baec_98cd082feea5_

#include <hub_service.h>
#include <signals.h>


namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this caller code is codegen by abelkhan codegen for cpp*/
/*this cb code is codegen by abelkhan for cpp*/
    class lobby_lobby_rsp_cb : public common::imodule, public std::enable_shared_from_this<lobby_lobby_rsp_cb>{
    public:
        lobby_lobby_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class lobby_lobby_hubproxy {
    public:
        std::string hub_name_2ff2fc56_612d_3e1e_bbc8_cf575bdfd6a7;

    private:
        std::atomic<uint64_t> uuid_2ff2fc56_612d_3e1e_bbc8_cf575bdfd6a7;
        std::shared_ptr<hub::hub_service> _hub_service;
        std::shared_ptr<lobby_lobby_rsp_cb> rsp_cb_lobby_lobby_handle;

    public:
        lobby_lobby_hubproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_lobby_rsp_cb> rsp_cb_lobby_lobby_handle_)
        {
            _hub_service = hub_service_;
            rsp_cb_lobby_lobby_handle = rsp_cb_lobby_lobby_handle_;

            uuid_2ff2fc56_612d_3e1e_bbc8_cf575bdfd6a7.store(random());
        }

        void invite_role_join_team(std::string account, int32_t team_role_num, std::string team_id, std::string invite_role_name){
            msgpack11::MsgPack::array _argv_29707771_ccbe_3ac7_adb1_a24ff0d29d04;
            _argv_29707771_ccbe_3ac7_adb1_a24ff0d29d04.push_back(account);
            _argv_29707771_ccbe_3ac7_adb1_a24ff0d29d04.push_back(team_role_num);
            _argv_29707771_ccbe_3ac7_adb1_a24ff0d29d04.push_back(team_id);
            _argv_29707771_ccbe_3ac7_adb1_a24ff0d29d04.push_back(invite_role_name);
            _hub_service->_hubmng->call_hub(hub_name_2ff2fc56_612d_3e1e_bbc8_cf575bdfd6a7, "lobby_lobby_invite_role_join_team", _argv_29707771_ccbe_3ac7_adb1_a24ff0d29d04);
        }

    };
    class lobby_lobby_caller {
    private:
        static std::shared_ptr<lobby_lobby_rsp_cb> rsp_cb_lobby_lobby_handle;

    private:
        std::shared_ptr<lobby_lobby_hubproxy> _hubproxy;

    public:
        lobby_lobby_caller(std::shared_ptr<hub::hub_service> _hub_service)
        {
            if (rsp_cb_lobby_lobby_handle == nullptr){
                rsp_cb_lobby_lobby_handle = std::make_shared<lobby_lobby_rsp_cb>();
                rsp_cb_lobby_lobby_handle->Init(_hub_service);
            }
            _hubproxy = std::make_shared<lobby_lobby_hubproxy>(_hub_service, rsp_cb_lobby_lobby_handle);
        }

        std::shared_ptr<lobby_lobby_hubproxy> get_hub(std::string hub_name) {
            _hubproxy->hub_name_2ff2fc56_612d_3e1e_bbc8_cf575bdfd6a7 = hub_name;
            return _hubproxy;
        }

    };

/*this cb code is codegen by abelkhan for cpp*/
    class lobby_lobby_offline_msg_rsp_cb : public common::imodule, public std::enable_shared_from_this<lobby_lobby_offline_msg_rsp_cb>{
    public:
        lobby_lobby_offline_msg_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class lobby_lobby_offline_msg_hubproxy {
    public:
        std::string hub_name_3f78c39c_2ba3_30a8_8cc7_65680224e8ee;

    private:
        std::atomic<uint64_t> uuid_3f78c39c_2ba3_30a8_8cc7_65680224e8ee;
        std::shared_ptr<hub::hub_service> _hub_service;
        std::shared_ptr<lobby_lobby_offline_msg_rsp_cb> rsp_cb_lobby_lobby_offline_msg_handle;

    public:
        lobby_lobby_offline_msg_hubproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_lobby_offline_msg_rsp_cb> rsp_cb_lobby_lobby_offline_msg_handle_)
        {
            _hub_service = hub_service_;
            rsp_cb_lobby_lobby_offline_msg_handle = rsp_cb_lobby_lobby_offline_msg_handle_;

            uuid_3f78c39c_2ba3_30a8_8cc7_65680224e8ee.store(random());
        }

        void role_have_offline_msg(std::string account){
            msgpack11::MsgPack::array _argv_74616d88_6da6_3100_a2fd_0a01e57ddf2e;
            _argv_74616d88_6da6_3100_a2fd_0a01e57ddf2e.push_back(account);
            _hub_service->_hubmng->call_hub(hub_name_3f78c39c_2ba3_30a8_8cc7_65680224e8ee, "lobby_lobby_offline_msg_role_have_offline_msg", _argv_74616d88_6da6_3100_a2fd_0a01e57ddf2e);
        }

    };
    class lobby_lobby_offline_msg_caller {
    private:
        static std::shared_ptr<lobby_lobby_offline_msg_rsp_cb> rsp_cb_lobby_lobby_offline_msg_handle;

    private:
        std::shared_ptr<lobby_lobby_offline_msg_hubproxy> _hubproxy;

    public:
        lobby_lobby_offline_msg_caller(std::shared_ptr<hub::hub_service> _hub_service)
        {
            if (rsp_cb_lobby_lobby_offline_msg_handle == nullptr){
                rsp_cb_lobby_lobby_offline_msg_handle = std::make_shared<lobby_lobby_offline_msg_rsp_cb>();
                rsp_cb_lobby_lobby_offline_msg_handle->Init(_hub_service);
            }
            _hubproxy = std::make_shared<lobby_lobby_offline_msg_hubproxy>(_hub_service, rsp_cb_lobby_lobby_offline_msg_handle);
        }

        std::shared_ptr<lobby_lobby_offline_msg_hubproxy> get_hub(std::string hub_name) {
            _hubproxy->hub_name_3f78c39c_2ba3_30a8_8cc7_65680224e8ee = hub_name;
            return _hubproxy;
        }

    };

/*this module code is codegen by abelkhan codegen for cpp*/
    class lobby_lobby_module : public common::imodule, public std::enable_shared_from_this<lobby_lobby_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        lobby_lobby_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("lobby_lobby_invite_role_join_team", std::bind(&lobby_lobby_module::invite_role_join_team, this, std::placeholders::_1));
        }

        concurrent::signals<void(std::string, int32_t, std::string, std::string)> sig_invite_role_join_team;
        void invite_role_join_team(const msgpack11::MsgPack::array& inArray){
            auto _account = inArray[0].string_value();
            auto _team_role_num = inArray[1].int32_value();
            auto _team_id = inArray[2].string_value();
            auto _invite_role_name = inArray[3].string_value();
            sig_invite_role_join_team.emit(_account, _team_role_num, _team_id, _invite_role_name);
        }

    };
    class lobby_lobby_offline_msg_module : public common::imodule, public std::enable_shared_from_this<lobby_lobby_offline_msg_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        lobby_lobby_offline_msg_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("lobby_lobby_offline_msg_role_have_offline_msg", std::bind(&lobby_lobby_offline_msg_module::role_have_offline_msg, this, std::placeholders::_1));
        }

        concurrent::signals<void(std::string)> sig_role_have_offline_msg;
        void role_have_offline_msg(const msgpack11::MsgPack::array& inArray){
            auto _account = inArray[0].string_value();
            sig_role_have_offline_msg.emit(_account);
        }

    };

}

#endif //_h_lcalllobby_6a4f4933_7ea7_3318_baec_98cd082feea5_
