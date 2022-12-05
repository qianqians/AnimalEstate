#ifndef _h_error_66566095_dd45_355d_89de_bccddc9e727f_
#define _h_error_66566095_dd45_355d_89de_bccddc9e727f_

#include <hub_service.h>
#include <signals.h>


namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

    enum class error{
        timeout = -2,
        db_error = -1,
        success = 0,
        invalid_team = 2,
        not_leader = 3,
        more_team_members = 4,
        in_game = 5,
        not_in_match = 6,
        wait_into_game = 7,
        is_in_match = 8,
        is_ready = 9,
        not_all_ready = 10,
        drop_box_too_far = 11,
        invalid_drop_box = 12,
        box_is_occupied = 13,
        not_open_drop_box = 14,
        drop_box_not_have_this_item = 15,
        invalid_drop_team = 16,
        not_at_door = 17,
        battle_is_end = 18,
        team_is_full = 19,
        invalid_role = 20
    };

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this caller code is codegen by abelkhan codegen for cpp*/
/*this cb code is codegen by abelkhan for cpp*/
    class error_code_ntf_rsp_cb : public common::imodule, public std::enable_shared_from_this<error_code_ntf_rsp_cb>{
    public:
        error_code_ntf_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class error_code_ntf_clientproxy
{
    public:
        std::string client_uuid_f657c200_2a33_308f_b478_82cef68fbca2;
        std::atomic<uint64_t> uuid_f657c200_2a33_308f_b478_82cef68fbca2;

        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<error_code_ntf_rsp_cb> rsp_cb_error_code_ntf_handle;

        error_code_ntf_clientproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<error_code_ntf_rsp_cb> rsp_cb_error_code_ntf_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_error_code_ntf_handle = rsp_cb_error_code_ntf_handle_;
            uuid_f657c200_2a33_308f_b478_82cef68fbca2.store(random());

        }

        void error_code(int32_t error){
            msgpack11::MsgPack::array _argv_b2890040_4e10_3967_a5ca_fac1ca306870;
            _argv_b2890040_4e10_3967_a5ca_fac1ca306870.push_back(error);
            _hub_handle->_gatemng->call_client(client_uuid_f657c200_2a33_308f_b478_82cef68fbca2, "error_code_ntf_error_code", _argv_b2890040_4e10_3967_a5ca_fac1ca306870);
        }

    };

    class error_code_ntf_multicast
{
    public:
        std::vector<std::string> client_uuids_f657c200_2a33_308f_b478_82cef68fbca2;
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<error_code_ntf_rsp_cb> rsp_cb_error_code_ntf_handle;

        error_code_ntf_multicast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<error_code_ntf_rsp_cb> rsp_cb_error_code_ntf_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_error_code_ntf_handle = rsp_cb_error_code_ntf_handle_;
        }

    };

    class error_code_ntf_broadcast
{
    public:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<error_code_ntf_rsp_cb> rsp_cb_error_code_ntf_handle;

        error_code_ntf_broadcast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<error_code_ntf_rsp_cb> rsp_cb_error_code_ntf_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_error_code_ntf_handle = rsp_cb_error_code_ntf_handle_;
        }

    };

    class error_code_ntf_clientproxy;
    class error_code_ntf_multicast;
    class error_code_ntf_broadcast;
    class error_code_ntf_caller {
    private:
        static std::shared_ptr<error_code_ntf_rsp_cb> rsp_cb_error_code_ntf_handle;

    private:
        std::shared_ptr<error_code_ntf_clientproxy> _clientproxy;
        std::shared_ptr<error_code_ntf_multicast> _multicast;
        std::shared_ptr<error_code_ntf_broadcast> _broadcast;

    public:
        error_code_ntf_caller(std::shared_ptr<hub::hub_service> hub_service_) 
        {
            if (rsp_cb_error_code_ntf_handle == nullptr) {
                rsp_cb_error_code_ntf_handle = std::make_shared<error_code_ntf_rsp_cb>();
                rsp_cb_error_code_ntf_handle->Init(hub_service_);
            }
            _clientproxy = std::make_shared<error_code_ntf_clientproxy>(hub_service_, rsp_cb_error_code_ntf_handle);
            _multicast = std::make_shared<error_code_ntf_multicast>(hub_service_, rsp_cb_error_code_ntf_handle);
            _broadcast = std::make_shared<error_code_ntf_broadcast>(hub_service_, rsp_cb_error_code_ntf_handle);
        }

        std::shared_ptr<error_code_ntf_clientproxy> get_client(std::string client_uuid) {
            _clientproxy->client_uuid_f657c200_2a33_308f_b478_82cef68fbca2 = client_uuid;
            return _clientproxy;
        }

        std::shared_ptr<error_code_ntf_multicast> get_multicast(std::vector<std::string> client_uuids) {
            _multicast->client_uuids_f657c200_2a33_308f_b478_82cef68fbca2 = client_uuids;
            return _multicast;
        }

        std::shared_ptr<error_code_ntf_broadcast> get_broadcast() {
            return _broadcast;
        }

    };

}

#endif //_h_error_66566095_dd45_355d_89de_bccddc9e727f_
