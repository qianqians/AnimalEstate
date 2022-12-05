#ifndef _h_lcallbattle_5b7669e5_be70_35e9_aa8d_6c1eb3c194a6_
#define _h_lcallbattle_5b7669e5_be70_35e9_aa8d_6c1eb3c194a6_

#include <hub_service.h>
#include <signals.h>


namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this caller code is codegen by abelkhan codegen for cpp*/
/*this cb code is codegen by abelkhan for cpp*/
    class lobby_battle_rsp_cb : public common::imodule, public std::enable_shared_from_this<lobby_battle_rsp_cb>{
    public:
        lobby_battle_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class lobby_battle_hubproxy {
    public:
        std::string hub_name_593dd3d1_4d8d_3d36_adbc_61bd9b0d02fb;

    private:
        std::atomic<uint64_t> uuid_593dd3d1_4d8d_3d36_adbc_61bd9b0d02fb;
        std::shared_ptr<hub::hub_service> _hub_service;
        std::shared_ptr<lobby_battle_rsp_cb> rsp_cb_lobby_battle_handle;

    public:
        lobby_battle_hubproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_battle_rsp_cb> rsp_cb_lobby_battle_handle_)
        {
            _hub_service = hub_service_;
            rsp_cb_lobby_battle_handle = rsp_cb_lobby_battle_handle_;

            uuid_593dd3d1_4d8d_3d36_adbc_61bd9b0d02fb.store(random());
        }

    };
    class lobby_battle_caller {
    private:
        static std::shared_ptr<lobby_battle_rsp_cb> rsp_cb_lobby_battle_handle;

    private:
        std::shared_ptr<lobby_battle_hubproxy> _hubproxy;

    public:
        lobby_battle_caller(std::shared_ptr<hub::hub_service> _hub_service)
        {
            if (rsp_cb_lobby_battle_handle == nullptr){
                rsp_cb_lobby_battle_handle = std::make_shared<lobby_battle_rsp_cb>();
                rsp_cb_lobby_battle_handle->Init(_hub_service);
            }
            _hubproxy = std::make_shared<lobby_battle_hubproxy>(_hub_service, rsp_cb_lobby_battle_handle);
        }

        std::shared_ptr<lobby_battle_hubproxy> get_hub(std::string hub_name) {
            _hubproxy->hub_name_593dd3d1_4d8d_3d36_adbc_61bd9b0d02fb = hub_name;
            return _hubproxy;
        }

    };

/*this module code is codegen by abelkhan codegen for cpp*/
    class lobby_battle_module : public common::imodule, public std::enable_shared_from_this<lobby_battle_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        lobby_battle_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
        }

    };

}

#endif //_h_lcallbattle_5b7669e5_be70_35e9_aa8d_6c1eb3c194a6_
