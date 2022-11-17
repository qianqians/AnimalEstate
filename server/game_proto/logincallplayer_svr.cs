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
    public class login_player_rsp_cb : common.imodule {
        public login_player_rsp_cb()
        {
        }

    }

    public class login_player_caller {
        public static login_player_rsp_cb rsp_cb_login_player_handle = null;
        private login_player_hubproxy _hubproxy;
        public login_player_caller()
        {
            if (rsp_cb_login_player_handle == null)
            {
                rsp_cb_login_player_handle = new login_player_rsp_cb();
            }
            _hubproxy = new login_player_hubproxy(rsp_cb_login_player_handle);
        }

        public login_player_hubproxy get_hub(string hub_name) {
            _hubproxy.hub_name_79224a74_5cd5_3ad0_9351_c5e8d06e5c92 = hub_name;
            return _hubproxy;
        }

    }

    public class login_player_hubproxy {
        public string hub_name_79224a74_5cd5_3ad0_9351_c5e8d06e5c92;
        private Int64 uuid_79224a74_5cd5_3ad0_9351_c5e8d06e5c92 = (Int64)RandomUUID.random();

        private login_player_rsp_cb rsp_cb_login_player_handle;

        public login_player_hubproxy(login_player_rsp_cb rsp_cb_login_player_handle_)
        {
            rsp_cb_login_player_handle = rsp_cb_login_player_handle_;
        }

        public void player_login(string sdk_uuid, string token){
            var _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b = new ArrayList();
            _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b.Add(sdk_uuid);
            _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b.Add(token);
            hub.hub._hubs.call_hub(hub_name_79224a74_5cd5_3ad0_9351_c5e8d06e5c92, "login_player_player_login", _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b);
        }

    }
/*this module code is codegen by abelkhan codegen for c#*/
    public class login_player_module : common.imodule {
        public login_player_module() 
        {
            hub.hub._modules.add_mothed("login_player_player_login", player_login);
        }

        public event Action<string, string> on_player_login;
        public void player_login(IList<MsgPack.MessagePackObject> inArray){
            var _sdk_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsString();
            var _token = ((MsgPack.MessagePackObject)inArray[1]).AsString();
            if (on_player_login != null){
                on_player_login(_sdk_uuid, _token);
            }
        }

    }

}
