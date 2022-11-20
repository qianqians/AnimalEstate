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
    public class player_player_room_rsp_cb : common.imodule {
        public player_player_room_rsp_cb()
        {
        }

    }

    public class player_player_room_caller {
        public static player_player_room_rsp_cb rsp_cb_player_player_room_handle = null;
        private player_player_room_hubproxy _hubproxy;
        public player_player_room_caller()
        {
            if (rsp_cb_player_player_room_handle == null)
            {
                rsp_cb_player_player_room_handle = new player_player_room_rsp_cb();
            }
            _hubproxy = new player_player_room_hubproxy(rsp_cb_player_player_room_handle);
        }

        public player_player_room_hubproxy get_hub(string hub_name) {
            _hubproxy.hub_name_2172ec02_bdf6_3291_b132_4247aea1be62 = hub_name;
            return _hubproxy;
        }

    }

    public class player_player_room_hubproxy {
        public string hub_name_2172ec02_bdf6_3291_b132_4247aea1be62;
        private Int64 uuid_2172ec02_bdf6_3291_b132_4247aea1be62 = (Int64)RandomUUID.random();

        private player_player_room_rsp_cb rsp_cb_player_player_room_handle;

        public player_player_room_hubproxy(player_player_room_rsp_cb rsp_cb_player_player_room_handle_)
        {
            rsp_cb_player_player_room_handle = rsp_cb_player_player_room_handle_;
        }

        public void invite_role_join_room(string sdk_uuid, string room_id, string invite_role_name){
            var _argv_4afdf6f4_2ff9_314b_9be9_c6d0fa96e4f8 = new ArrayList();
            _argv_4afdf6f4_2ff9_314b_9be9_c6d0fa96e4f8.Add(sdk_uuid);
            _argv_4afdf6f4_2ff9_314b_9be9_c6d0fa96e4f8.Add(room_id);
            _argv_4afdf6f4_2ff9_314b_9be9_c6d0fa96e4f8.Add(invite_role_name);
            hub.hub._hubs.call_hub(hub_name_2172ec02_bdf6_3291_b132_4247aea1be62, "player_player_room_invite_role_join_room", _argv_4afdf6f4_2ff9_314b_9be9_c6d0fa96e4f8);
        }

    }
/*this cb code is codegen by abelkhan for c#*/
    public class player_player_offline_msg_rsp_cb : common.imodule {
        public player_player_offline_msg_rsp_cb()
        {
        }

    }

    public class player_player_offline_msg_caller {
        public static player_player_offline_msg_rsp_cb rsp_cb_player_player_offline_msg_handle = null;
        private player_player_offline_msg_hubproxy _hubproxy;
        public player_player_offline_msg_caller()
        {
            if (rsp_cb_player_player_offline_msg_handle == null)
            {
                rsp_cb_player_player_offline_msg_handle = new player_player_offline_msg_rsp_cb();
            }
            _hubproxy = new player_player_offline_msg_hubproxy(rsp_cb_player_player_offline_msg_handle);
        }

        public player_player_offline_msg_hubproxy get_hub(string hub_name) {
            _hubproxy.hub_name_d5d0e1c9_52d5_396b_96e3_551f12e9aeb0 = hub_name;
            return _hubproxy;
        }

    }

    public class player_player_offline_msg_hubproxy {
        public string hub_name_d5d0e1c9_52d5_396b_96e3_551f12e9aeb0;
        private Int64 uuid_d5d0e1c9_52d5_396b_96e3_551f12e9aeb0 = (Int64)RandomUUID.random();

        private player_player_offline_msg_rsp_cb rsp_cb_player_player_offline_msg_handle;

        public player_player_offline_msg_hubproxy(player_player_offline_msg_rsp_cb rsp_cb_player_player_offline_msg_handle_)
        {
            rsp_cb_player_player_offline_msg_handle = rsp_cb_player_player_offline_msg_handle_;
        }

        public void player_have_offline_msg(Int64 guid){
            var _argv_0031381b_1b05_3a71_a318_b52adaa27ce5 = new ArrayList();
            _argv_0031381b_1b05_3a71_a318_b52adaa27ce5.Add(guid);
            hub.hub._hubs.call_hub(hub_name_d5d0e1c9_52d5_396b_96e3_551f12e9aeb0, "player_player_offline_msg_player_have_offline_msg", _argv_0031381b_1b05_3a71_a318_b52adaa27ce5);
        }

    }
/*this module code is codegen by abelkhan codegen for c#*/
    public class player_player_room_module : common.imodule {
        public player_player_room_module() 
        {
            hub.hub._modules.add_mothed("player_player_room_invite_role_join_room", invite_role_join_room);
        }

        public event Action<string, string, string> on_invite_role_join_room;
        public void invite_role_join_room(IList<MsgPack.MessagePackObject> inArray){
            var _sdk_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsString();
            var _room_id = ((MsgPack.MessagePackObject)inArray[1]).AsString();
            var _invite_role_name = ((MsgPack.MessagePackObject)inArray[2]).AsString();
            if (on_invite_role_join_room != null){
                on_invite_role_join_room(_sdk_uuid, _room_id, _invite_role_name);
            }
        }

    }
    public class player_player_offline_msg_module : common.imodule {
        public player_player_offline_msg_module() 
        {
            hub.hub._modules.add_mothed("player_player_offline_msg_player_have_offline_msg", player_have_offline_msg);
        }

        public event Action<Int64> on_player_have_offline_msg;
        public void player_have_offline_msg(IList<MsgPack.MessagePackObject> inArray){
            var _guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            if (on_player_have_offline_msg != null){
                on_player_have_offline_msg(_guid);
            }
        }

    }

}
