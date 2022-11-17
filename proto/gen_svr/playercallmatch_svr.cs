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

    }
/*this module code is codegen by abelkhan codegen for c#*/
    public class player_match_module : common.imodule {
        public player_match_module() 
        {
        }

    }

}
