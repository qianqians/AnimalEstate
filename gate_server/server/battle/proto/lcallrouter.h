#ifndef _h_lcallrouter_cf3c6add_cd4d_30d9_a24b_f3a7130d6ac8_
#define _h_lcallrouter_cf3c6add_cd4d_30d9_a24b_f3a7130d6ac8_

#include <hub_service.h>
#include <signals.h>


namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
    class lobby_router_info {
    public:
        std::string lobby_hub_name;
        bool is_busy;

    public:
        static msgpack11::MsgPack::object lobby_router_info_to_protcol(lobby_router_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("lobby_hub_name", _struct.lobby_hub_name));
            _protocol.insert(std::make_pair("is_busy", _struct.is_busy));
            return _protocol;
        }

        static lobby_router_info protcol_to_lobby_router_info(const msgpack11::MsgPack::object& _protocol){
            lobby_router_info _struct259e74ef_ae36_3ef2_91dc_76173bf1f409;
            for(auto i : _protocol){
                if (i.first == "lobby_hub_name"){
                    _struct259e74ef_ae36_3ef2_91dc_76173bf1f409.lobby_hub_name = i.second.string_value();
                }
                else if (i.first == "is_busy"){
                    _struct259e74ef_ae36_3ef2_91dc_76173bf1f409.is_busy = i.second.bool_value();
                }
            }
            return _struct259e74ef_ae36_3ef2_91dc_76173bf1f409;
        }
    };

/*this caller code is codegen by abelkhan codegen for cpp*/
/*this cb code is codegen by abelkhan for cpp*/
    class lobby_router_rsp_cb : public common::imodule, public std::enable_shared_from_this<lobby_router_rsp_cb>{
    public:
        lobby_router_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class lobby_router_hubproxy {
    public:
        std::string hub_name_230a7a4c_5015_39ce_8c9a_5f3f111c4672;

    private:
        std::atomic<uint64_t> uuid_230a7a4c_5015_39ce_8c9a_5f3f111c4672;
        std::shared_ptr<hub::hub_service> _hub_service;
        std::shared_ptr<lobby_router_rsp_cb> rsp_cb_lobby_router_handle;

    public:
        lobby_router_hubproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_router_rsp_cb> rsp_cb_lobby_router_handle_)
        {
            _hub_service = hub_service_;
            rsp_cb_lobby_router_handle = rsp_cb_lobby_router_handle_;

            uuid_230a7a4c_5015_39ce_8c9a_5f3f111c4672.store(random());
        }

        void lobby_info(lobby_router_info _lobby_info){
            msgpack11::MsgPack::array _argv_d0ab469b_4310_37f7_b3b0_4014148b8441;
            _argv_d0ab469b_4310_37f7_b3b0_4014148b8441.push_back(lobby_router_info::lobby_router_info_to_protcol(_lobby_info));
            _hub_service->_hubmng->call_hub(hub_name_230a7a4c_5015_39ce_8c9a_5f3f111c4672, "lobby_router_lobby_info", _argv_d0ab469b_4310_37f7_b3b0_4014148b8441);
        }

    };
    class lobby_router_caller {
    private:
        static std::shared_ptr<lobby_router_rsp_cb> rsp_cb_lobby_router_handle;

    private:
        std::shared_ptr<lobby_router_hubproxy> _hubproxy;

    public:
        lobby_router_caller(std::shared_ptr<hub::hub_service> _hub_service)
        {
            if (rsp_cb_lobby_router_handle == nullptr){
                rsp_cb_lobby_router_handle = std::make_shared<lobby_router_rsp_cb>();
                rsp_cb_lobby_router_handle->Init(_hub_service);
            }
            _hubproxy = std::make_shared<lobby_router_hubproxy>(_hub_service, rsp_cb_lobby_router_handle);
        }

        std::shared_ptr<lobby_router_hubproxy> get_hub(std::string hub_name) {
            _hubproxy->hub_name_230a7a4c_5015_39ce_8c9a_5f3f111c4672 = hub_name;
            return _hubproxy;
        }

    };

/*this module code is codegen by abelkhan codegen for cpp*/
    class lobby_router_module : public common::imodule, public std::enable_shared_from_this<lobby_router_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        lobby_router_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("lobby_router_lobby_info", std::bind(&lobby_router_module::lobby_info, this, std::placeholders::_1));
        }

        concurrent::signals<void(lobby_router_info)> sig_lobby_info;
        void lobby_info(const msgpack11::MsgPack::array& inArray){
            auto __lobby_info = lobby_router_info::protcol_to_lobby_router_info(inArray[0].object_items());
            sig_lobby_info.emit(__lobby_info);
        }

    };

}

#endif //_h_lcallrouter_cf3c6add_cd4d_30d9_a24b_f3a7130d6ac8_
