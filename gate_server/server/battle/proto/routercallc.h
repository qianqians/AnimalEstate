#ifndef _h_routercallc_0689260b_2fbc_3776_b113_5a254354772e_
#define _h_routercallc_0689260b_2fbc_3776_b113_5a254354772e_

#include <hub_service.h>
#include <signals.h>


namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this caller code is codegen by abelkhan codegen for cpp*/
/*this cb code is codegen by abelkhan for cpp*/
    class router_client_rsp_cb : public common::imodule, public std::enable_shared_from_this<router_client_rsp_cb>{
    public:
        router_client_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class router_client_clientproxy
{
    public:
        std::string client_uuid_2c453a4d_80da_39e7_8da3_fb54d89c5f3c;
        std::atomic<uint64_t> uuid_2c453a4d_80da_39e7_8da3_fb54d89c5f3c;

        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<router_client_rsp_cb> rsp_cb_router_client_handle;

        router_client_clientproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<router_client_rsp_cb> rsp_cb_router_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_router_client_handle = rsp_cb_router_client_handle_;
            uuid_2c453a4d_80da_39e7_8da3_fb54d89c5f3c.store(random());

        }

        void server_busy_into_line_up(int32_t rank){
            msgpack11::MsgPack::array _argv_bb8561a8_a31a_33e4_93b7_1fc1039ed322;
            _argv_bb8561a8_a31a_33e4_93b7_1fc1039ed322.push_back(rank);
            _hub_handle->_gatemng->call_client(client_uuid_2c453a4d_80da_39e7_8da3_fb54d89c5f3c, "router_client_server_busy_into_line_up", _argv_bb8561a8_a31a_33e4_93b7_1fc1039ed322);
        }

        void into_lobby(std::string lobby_name){
            msgpack11::MsgPack::array _argv_98d9e3e8_5d35_38d0_b30a_7e20158c3094;
            _argv_98d9e3e8_5d35_38d0_b30a_7e20158c3094.push_back(lobby_name);
            _hub_handle->_gatemng->call_client(client_uuid_2c453a4d_80da_39e7_8da3_fb54d89c5f3c, "router_client_into_lobby", _argv_98d9e3e8_5d35_38d0_b30a_7e20158c3094);
        }

    };

    class router_client_multicast
{
    public:
        std::vector<std::string> client_uuids_2c453a4d_80da_39e7_8da3_fb54d89c5f3c;
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<router_client_rsp_cb> rsp_cb_router_client_handle;

        router_client_multicast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<router_client_rsp_cb> rsp_cb_router_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_router_client_handle = rsp_cb_router_client_handle_;
        }

    };

    class router_client_broadcast
{
    public:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<router_client_rsp_cb> rsp_cb_router_client_handle;

        router_client_broadcast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<router_client_rsp_cb> rsp_cb_router_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_router_client_handle = rsp_cb_router_client_handle_;
        }

    };

    class router_client_clientproxy;
    class router_client_multicast;
    class router_client_broadcast;
    class router_client_caller {
    private:
        static std::shared_ptr<router_client_rsp_cb> rsp_cb_router_client_handle;

    private:
        std::shared_ptr<router_client_clientproxy> _clientproxy;
        std::shared_ptr<router_client_multicast> _multicast;
        std::shared_ptr<router_client_broadcast> _broadcast;

    public:
        router_client_caller(std::shared_ptr<hub::hub_service> hub_service_) 
        {
            if (rsp_cb_router_client_handle == nullptr) {
                rsp_cb_router_client_handle = std::make_shared<router_client_rsp_cb>();
                rsp_cb_router_client_handle->Init(hub_service_);
            }
            _clientproxy = std::make_shared<router_client_clientproxy>(hub_service_, rsp_cb_router_client_handle);
            _multicast = std::make_shared<router_client_multicast>(hub_service_, rsp_cb_router_client_handle);
            _broadcast = std::make_shared<router_client_broadcast>(hub_service_, rsp_cb_router_client_handle);
        }

        std::shared_ptr<router_client_clientproxy> get_client(std::string client_uuid) {
            _clientproxy->client_uuid_2c453a4d_80da_39e7_8da3_fb54d89c5f3c = client_uuid;
            return _clientproxy;
        }

        std::shared_ptr<router_client_multicast> get_multicast(std::vector<std::string> client_uuids) {
            _multicast->client_uuids_2c453a4d_80da_39e7_8da3_fb54d89c5f3c = client_uuids;
            return _multicast;
        }

        std::shared_ptr<router_client_broadcast> get_broadcast() {
            return _broadcast;
        }

    };

}

#endif //_h_routercallc_0689260b_2fbc_3776_b113_5a254354772e_
