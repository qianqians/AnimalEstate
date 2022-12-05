#ifndef _h_ccallrouter_e7ac9084_c12f_34f4_b016_93c916485c96_
#define _h_ccallrouter_e7ac9084_c12f_34f4_b016_93c916485c96_

#include <hub_service.h>
#include <signals.h>


namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this module code is codegen by abelkhan codegen for cpp*/
    class router_module : public common::imodule, public std::enable_shared_from_this<router_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        router_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("router_router_player_no_author", std::bind(&router_module::router_player_no_author, this, std::placeholders::_1));
        }

        concurrent::signals<void(std::string)> sig_router_player_no_author;
        void router_player_no_author(const msgpack11::MsgPack::array& inArray){
            auto _account = inArray[0].string_value();
            sig_router_player_no_author.emit(_account);
        }

    };

}

#endif //_h_ccallrouter_e7ac9084_c12f_34f4_b016_93c916485c96_
