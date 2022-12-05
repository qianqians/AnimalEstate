#ifndef _h_ccallmatch_aa2d2106_3e1b_38bf_8e7c_c03809cf322b_
#define _h_ccallmatch_aa2d2106_3e1b_38bf_8e7c_c03809cf322b_

#include <hub_service.h>
#include <signals.h>

#include "common.h"

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this module code is codegen by abelkhan codegen for cpp*/
    class client_team_match_module : public common::imodule, public std::enable_shared_from_this<client_team_match_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        client_team_match_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("client_team_match_leave_team", std::bind(&client_team_match_module::leave_team, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("client_team_match_free_team", std::bind(&client_team_match_module::free_team, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("client_team_match_ready", std::bind(&client_team_match_module::ready, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("client_team_match_unready", std::bind(&client_team_match_module::unready, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("client_team_match_kick", std::bind(&client_team_match_module::kick, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("client_team_match_start_match", std::bind(&client_team_match_module::start_match, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("client_team_match_stop_match", std::bind(&client_team_match_module::stop_match, this, std::placeholders::_1));
        }

        concurrent::signals<void()> sig_leave_team;
        void leave_team(const msgpack11::MsgPack::array& inArray){
            sig_leave_team.emit();
        }

        concurrent::signals<void()> sig_free_team;
        void free_team(const msgpack11::MsgPack::array& inArray){
            sig_free_team.emit();
        }

        concurrent::signals<void()> sig_ready;
        void ready(const msgpack11::MsgPack::array& inArray){
            sig_ready.emit();
        }

        concurrent::signals<void()> sig_unready;
        void unready(const msgpack11::MsgPack::array& inArray){
            sig_unready.emit();
        }

        concurrent::signals<void(std::string)> sig_kick;
        void kick(const msgpack11::MsgPack::array& inArray){
            auto _be_kicked_account = inArray[0].string_value();
            sig_kick.emit(_be_kicked_account);
        }

        concurrent::signals<void()> sig_start_match;
        void start_match(const msgpack11::MsgPack::array& inArray){
            sig_start_match.emit();
        }

        concurrent::signals<void()> sig_stop_match;
        void stop_match(const msgpack11::MsgPack::array& inArray){
            sig_stop_match.emit();
        }

    };

}

#endif //_h_ccallmatch_aa2d2106_3e1b_38bf_8e7c_c03809cf322b_
