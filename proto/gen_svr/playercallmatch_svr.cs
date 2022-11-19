using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using MsgPack.Serialization;

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for c#*/

/*this struct code is codegen by abelkhan codegen for c#*/
/*this caller code is codegen by abelkhan codegen for c#*/
/*this cb code is codegen by abelkhan for c#*/
    public class player_match_rsp_cb : common.imodule {
        public player_match_rsp_cb()
        {
        }

    }

    public class player_match_caller {
        public static player_match_rsp_cb rsp_cb_player_match_handle = null;
        private player_match_hubproxy _hubproxy;
        public player_match_caller()
        {
            if (rsp_cb_player_match_handle == null)
            {
                rsp_cb_player_match_handle = new player_match_rsp_cb();
            }
            _hubproxy = new player_match_hubproxy(rsp_cb_player_match_handle);
        }

        public player_match_hubproxy get_hub(string hub_name) {
            _hubproxy.hub_name_f08f93cd_bfea_3bf2_ae83_42be38c1f420 = hub_name;
            return _hubproxy;
        }

    }

    public class player_match_hubproxy {
        public string hub_name_f08f93cd_bfea_3bf2_ae83_42be38c1f420;
        private Int64 uuid_f08f93cd_bfea_3bf2_ae83_42be38c1f420 = (Int64)RandomUUID.random();

        private player_match_rsp_cb rsp_cb_player_match_handle;

        public player_match_hubproxy(player_match_rsp_cb rsp_cb_player_match_handle_)
        {
            rsp_cb_player_match_handle = rsp_cb_player_match_handle_;
        }

        public void player_join_match(player_inline_info player_info){
            var _argv_53045b75_544f_3315_95b9_4f6ed684c17d = new ArrayList();
            _argv_53045b75_544f_3315_95b9_4f6ed684c17d.Add(player_inline_info.player_inline_info_to_protcol(player_info));
            hub.hub._hubs.call_hub(hub_name_f08f93cd_bfea_3bf2_ae83_42be38c1f420, "player_match_player_join_match", _argv_53045b75_544f_3315_95b9_4f6ed684c17d);
        }

    }
/*this module code is codegen by abelkhan codegen for c#*/
    public class player_match_module : common.imodule {
        public player_match_module() 
        {
            hub.hub._modules.add_mothed("player_match_player_join_match", player_join_match);
        }

        public event Action<player_inline_info> on_player_join_match;
        public void player_join_match(IList<MsgPack.MessagePackObject> inArray){
            var _player_info = player_inline_info.protcol_to_player_inline_info(((MsgPack.MessagePackObject)inArray[0]).AsDictionary());
            if (on_player_join_match != null){
                on_player_join_match(_player_info);
            }
        }

    }

}
