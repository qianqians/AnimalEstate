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
    public class game_player_rsp_cb : common.imodule {
        public game_player_rsp_cb()
        {
        }

    }

    public class game_player_caller {
        public static game_player_rsp_cb rsp_cb_game_player_handle = null;
        private game_player_hubproxy _hubproxy;
        public game_player_caller()
        {
            if (rsp_cb_game_player_handle == null)
            {
                rsp_cb_game_player_handle = new game_player_rsp_cb();
            }
            _hubproxy = new game_player_hubproxy(rsp_cb_game_player_handle);
        }

        public game_player_hubproxy get_hub(string hub_name) {
            _hubproxy.hub_name_509ddebd_919b_368c_9f04_f1fcb015afc4 = hub_name;
            return _hubproxy;
        }

    }

    public class game_player_hubproxy {
        public string hub_name_509ddebd_919b_368c_9f04_f1fcb015afc4;
        private Int64 uuid_509ddebd_919b_368c_9f04_f1fcb015afc4 = (Int64)RandomUUID.random();

        private game_player_rsp_cb rsp_cb_game_player_handle;

        public game_player_hubproxy(game_player_rsp_cb rsp_cb_game_player_handle_)
        {
            rsp_cb_game_player_handle = rsp_cb_game_player_handle_;
        }

        public void settle(game_settle_info settle_info){
            var _argv_b28d056f_3d2a_3ca4_91e6_47b841274e0b = new ArrayList();
            _argv_b28d056f_3d2a_3ca4_91e6_47b841274e0b.Add(game_settle_info.game_settle_info_to_protcol(settle_info));
            hub.hub._hubs.call_hub(hub_name_509ddebd_919b_368c_9f04_f1fcb015afc4, "game_player_settle", _argv_b28d056f_3d2a_3ca4_91e6_47b841274e0b);
        }

    }
/*this module code is codegen by abelkhan codegen for c#*/
    public class game_player_module : common.imodule {
        public game_player_module() 
        {
            hub.hub._modules.add_mothed("game_player_settle", settle);
        }

        public event Action<game_settle_info> on_settle;
        public void settle(IList<MsgPack.MessagePackObject> inArray){
            var _settle_info = game_settle_info.protcol_to_game_settle_info(((MsgPack.MessagePackObject)inArray[0]).AsDictionary());
            if (on_settle != null){
                on_settle(_settle_info);
            }
        }

    }

}
