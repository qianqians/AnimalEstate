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
    public class room_match_rsp_cb : common.imodule {
        public room_match_rsp_cb()
        {
        }

    }

    public class room_match_caller {
        public static room_match_rsp_cb rsp_cb_room_match_handle = null;
        private room_match_hubproxy _hubproxy;
        public room_match_caller()
        {
            if (rsp_cb_room_match_handle == null)
            {
                rsp_cb_room_match_handle = new room_match_rsp_cb();
            }
            _hubproxy = new room_match_hubproxy(rsp_cb_room_match_handle);
        }

        public room_match_hubproxy get_hub(string hub_name) {
            _hubproxy.hub_name_b422163b_ba16_33dc_9805_fb7de83348f5 = hub_name;
            return _hubproxy;
        }

    }

    public class room_match_hubproxy {
        public string hub_name_b422163b_ba16_33dc_9805_fb7de83348f5;
        private Int32 uuid_b422163b_ba16_33dc_9805_fb7de83348f5 = (Int32)RandomUUID.random();

        private room_match_rsp_cb rsp_cb_room_match_handle;

        public room_match_hubproxy(room_match_rsp_cb rsp_cb_room_match_handle_)
        {
            rsp_cb_room_match_handle = rsp_cb_room_match_handle_;
        }

        public void room_join_match(room_info info){
            var _argv_ff48d6b0_af9f_3d8e_8b49_b3f5f2657cb2 = new ArrayList();
            _argv_ff48d6b0_af9f_3d8e_8b49_b3f5f2657cb2.Add(room_info.room_info_to_protcol(info));
            hub.hub._hubs.call_hub(hub_name_b422163b_ba16_33dc_9805_fb7de83348f5, "room_match_room_join_match", _argv_ff48d6b0_af9f_3d8e_8b49_b3f5f2657cb2);
        }

    }
/*this module code is codegen by abelkhan codegen for c#*/
    public class room_match_module : common.imodule {
        public room_match_module() 
        {
            hub.hub._modules.add_mothed("room_match_room_join_match", room_join_match);
        }

        public event Action<room_info> on_room_join_match;
        public void room_join_match(IList<MsgPack.MessagePackObject> inArray){
            var _info = room_info.protcol_to_room_info(((MsgPack.MessagePackObject)inArray[0]).AsDictionary());
            if (on_room_join_match != null){
                on_room_join_match(_info);
            }
        }

    }

}
