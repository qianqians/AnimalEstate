#ifndef _h_rcalllobby_89866680_810f_31a2_9cb9_837cba354292_
#define _h_rcalllobby_89866680_810f_31a2_9cb9_837cba354292_

#include <hub_service.h>
#include <signals.h>


namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this caller code is codegen by abelkhan codegen for cpp*/
    class router_lobby_rsp_cb;
    class router_lobby_role_login_cb : public std::enable_shared_from_this<router_lobby_role_login_cb>{
    private:
        uint64_t cb_uuid;
        std::shared_ptr<router_lobby_rsp_cb> module_rsp_cb;

    public:
        router_lobby_role_login_cb(uint64_t _cb_uuid, std::shared_ptr<router_lobby_rsp_cb> _module_rsp_cb);
    public:
        concurrent::signals<void(bool)> sig_role_login_cb;
        concurrent::signals<void(int32_t)> sig_role_login_err;
        concurrent::signals<void()> sig_role_login_timeout;

        std::shared_ptr<router_lobby_role_login_cb> callBack(std::function<void(bool is_busy)> cb, std::function<void(int32_t err)> err);
        void timeout(uint64_t tick, std::function<void()> timeout_cb);
    };

/*this cb code is codegen by abelkhan for cpp*/
    class router_lobby_rsp_cb : public common::imodule, public std::enable_shared_from_this<router_lobby_rsp_cb>{
    public:
        std::mutex mutex_map_role_login;
        std::unordered_map<uint64_t, std::shared_ptr<router_lobby_role_login_cb> > map_role_login;
        router_lobby_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            _hub_service->modules.add_mothed("router_lobby_rsp_cb_role_login_rsp", std::bind(&router_lobby_rsp_cb::role_login_rsp, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("router_lobby_rsp_cb_role_login_err", std::bind(&router_lobby_rsp_cb::role_login_err, this, std::placeholders::_1));
        }

        void role_login_rsp(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto _is_busy = inArray[1].bool_value();
            auto rsp = try_get_and_del_role_login_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_role_login_cb.emit(_is_busy);
            }
        }

        void role_login_err(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto _err = inArray[1].int32_value();
            auto rsp = try_get_and_del_role_login_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_role_login_err.emit(_err);
            }
        }

        void role_login_timeout(uint64_t cb_uuid){
            auto rsp = try_get_and_del_role_login_cb(cb_uuid);
            if (rsp != nullptr){
                rsp->sig_role_login_timeout.emit();
            }
        }

        std::shared_ptr<router_lobby_role_login_cb> try_get_and_del_role_login_cb(uint64_t uuid){
            std::lock_guard<std::mutex> l(mutex_map_role_login);
            if (map_role_login.find(uuid) != map_role_login.end()) {
                auto rsp = map_role_login[uuid];
                map_role_login.erase(uuid);
                return rsp;
            }
            return nullptr;
        }

    };

    class router_lobby_hubproxy {
    public:
        std::string hub_name_ef3f41ca_a805_3ce2_8c7a_5b87498e59a9;

    private:
        std::atomic<uint64_t> uuid_ef3f41ca_a805_3ce2_8c7a_5b87498e59a9;
        std::shared_ptr<hub::hub_service> _hub_service;
        std::shared_ptr<router_lobby_rsp_cb> rsp_cb_router_lobby_handle;

    public:
        router_lobby_hubproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<router_lobby_rsp_cb> rsp_cb_router_lobby_handle_)
        {
            _hub_service = hub_service_;
            rsp_cb_router_lobby_handle = rsp_cb_router_lobby_handle_;

            uuid_ef3f41ca_a805_3ce2_8c7a_5b87498e59a9.store(random());
        }

        std::shared_ptr<router_lobby_role_login_cb> role_login(std::string session_uuid, std::string account){
            auto uuid_f08c22e8_6dbc_5343_b420_3427e980e19f = uuid_ef3f41ca_a805_3ce2_8c7a_5b87498e59a9++;
            msgpack11::MsgPack::array _argv_6fc0cc1a_c738_364e_b9f9_f0ad3d1fdd64;
            _argv_6fc0cc1a_c738_364e_b9f9_f0ad3d1fdd64.push_back(uuid_f08c22e8_6dbc_5343_b420_3427e980e19f);
            _argv_6fc0cc1a_c738_364e_b9f9_f0ad3d1fdd64.push_back(session_uuid);
            _argv_6fc0cc1a_c738_364e_b9f9_f0ad3d1fdd64.push_back(account);
            _hub_service->_hubmng->call_hub(hub_name_ef3f41ca_a805_3ce2_8c7a_5b87498e59a9, "router_lobby_role_login", _argv_6fc0cc1a_c738_364e_b9f9_f0ad3d1fdd64);

            auto cb_role_login_obj = std::make_shared<router_lobby_role_login_cb>(uuid_f08c22e8_6dbc_5343_b420_3427e980e19f, rsp_cb_router_lobby_handle);
            std::lock_guard<std::mutex> l(rsp_cb_router_lobby_handle->mutex_map_role_login);
            rsp_cb_router_lobby_handle->map_role_login.insert(std::make_pair(uuid_f08c22e8_6dbc_5343_b420_3427e980e19f, cb_role_login_obj));
            return cb_role_login_obj;
        }

    };
    class router_lobby_caller {
    private:
        static std::shared_ptr<router_lobby_rsp_cb> rsp_cb_router_lobby_handle;

    private:
        std::shared_ptr<router_lobby_hubproxy> _hubproxy;

    public:
        router_lobby_caller(std::shared_ptr<hub::hub_service> _hub_service)
        {
            if (rsp_cb_router_lobby_handle == nullptr){
                rsp_cb_router_lobby_handle = std::make_shared<router_lobby_rsp_cb>();
                rsp_cb_router_lobby_handle->Init(_hub_service);
            }
            _hubproxy = std::make_shared<router_lobby_hubproxy>(_hub_service, rsp_cb_router_lobby_handle);
        }

        std::shared_ptr<router_lobby_hubproxy> get_hub(std::string hub_name) {
            _hubproxy->hub_name_ef3f41ca_a805_3ce2_8c7a_5b87498e59a9 = hub_name;
            return _hubproxy;
        }

    };

/*this module code is codegen by abelkhan codegen for cpp*/
    class router_lobby_role_login_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _hub_name_000f578e_fe60_32c9_b462_0ecdece1f8a5;
        uint64_t uuid_6fc0cc1a_c738_364e_b9f9_f0ad3d1fdd64;

    public:
        router_lobby_role_login_rsp(std::shared_ptr<hub::hub_service> _hub, std::string hub_name, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _hub_name_000f578e_fe60_32c9_b462_0ecdece1f8a5 = hub_name;
            uuid_6fc0cc1a_c738_364e_b9f9_f0ad3d1fdd64 = _uuid;
        }

        void rsp(bool is_busy){
            msgpack11::MsgPack::array _argv_000f578e_fe60_32c9_b462_0ecdece1f8a5;
            _argv_000f578e_fe60_32c9_b462_0ecdece1f8a5.push_back(uuid_6fc0cc1a_c738_364e_b9f9_f0ad3d1fdd64);
            _argv_000f578e_fe60_32c9_b462_0ecdece1f8a5.push_back(is_busy);
            _hub_handle->_hubmng->call_hub(_hub_name_000f578e_fe60_32c9_b462_0ecdece1f8a5, "router_lobby_rsp_cb_role_login_rsp", _argv_000f578e_fe60_32c9_b462_0ecdece1f8a5);
        }

        void err(int32_t err){
            msgpack11::MsgPack::array _argv_000f578e_fe60_32c9_b462_0ecdece1f8a5;
            _argv_000f578e_fe60_32c9_b462_0ecdece1f8a5.push_back(uuid_6fc0cc1a_c738_364e_b9f9_f0ad3d1fdd64);
            _argv_000f578e_fe60_32c9_b462_0ecdece1f8a5.push_back(err);
            _hub_handle->_hubmng->call_hub(_hub_name_000f578e_fe60_32c9_b462_0ecdece1f8a5, "router_lobby_rsp_cb_role_login_err", _argv_000f578e_fe60_32c9_b462_0ecdece1f8a5);
        }

    };

    class router_lobby_module : public common::imodule, public std::enable_shared_from_this<router_lobby_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        router_lobby_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("router_lobby_role_login", std::bind(&router_lobby_module::role_login, this, std::placeholders::_1));
        }

        concurrent::signals<void(std::string, std::string)> sig_role_login;
        void role_login(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            auto _session_uuid = inArray[1].string_value();
            auto _account = inArray[2].string_value();
            rsp = std::make_shared<router_lobby_role_login_rsp>(hub_handle, hub_handle->_hubmng->current_hubproxy->_hub_name, _cb_uuid);
            sig_role_login.emit(_session_uuid, _account);
            rsp = nullptr;
        }

    };

}

#endif //_h_rcalllobby_89866680_810f_31a2_9cb9_837cba354292_
