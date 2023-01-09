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
    public class match_room_rsp_cb : common.imodule {
        public match_room_rsp_cb()
        {
        }

    }

    public class match_room_caller {
        public static match_room_rsp_cb rsp_cb_match_room_handle = null;
        private match_room_hubproxy _hubproxy;
        public match_room_caller()
        {
            if (rsp_cb_match_room_handle == null)
            {
                rsp_cb_match_room_handle = new match_room_rsp_cb();
            }
            _hubproxy = new match_room_hubproxy(rsp_cb_match_room_handle);
        }

        public match_room_hubproxy get_hub(string hub_name) {
            _hubproxy.hub_name_7be997e8_0e81_3728_9f6b_2f2429d08950 = hub_name;
            return _hubproxy;
        }

    }

    public class match_room_hubproxy {
        public string hub_name_7be997e8_0e81_3728_9f6b_2f2429d08950;
        private Int32 uuid_7be997e8_0e81_3728_9f6b_2f2429d08950 = (Int32)RandomUUID.random();

        private match_room_rsp_cb rsp_cb_match_room_handle;

        public match_room_hubproxy(match_room_rsp_cb rsp_cb_match_room_handle_)
        {
            rsp_cb_match_room_handle = rsp_cb_match_room_handle_;
        }

        public void start_game(string room_uuid, string game_hub_name){
            var _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747 = new ArrayList();
            _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747.Add(room_uuid);
            _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747.Add(game_hub_name);
            hub.hub._hubs.call_hub(hub_name_7be997e8_0e81_3728_9f6b_2f2429d08950, "match_room_start_game", _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747);
        }

    }
/*this cb code is codegen by abelkhan for c#*/
    public class match_player_rsp_cb : common.imodule {
        public match_player_rsp_cb()
        {
        }

    }

    public class match_player_caller {
        public static match_player_rsp_cb rsp_cb_match_player_handle = null;
        private match_player_hubproxy _hubproxy;
        public match_player_caller()
        {
            if (rsp_cb_match_player_handle == null)
            {
                rsp_cb_match_player_handle = new match_player_rsp_cb();
            }
            _hubproxy = new match_player_hubproxy(rsp_cb_match_player_handle);
        }

        public match_player_hubproxy get_hub(string hub_name) {
            _hubproxy.hub_name_da7b2c07_3c4d_366b_8def_7fa976df7502 = hub_name;
            return _hubproxy;
        }

    }

    public class match_player_hubproxy {
        public string hub_name_da7b2c07_3c4d_366b_8def_7fa976df7502;
        private Int32 uuid_da7b2c07_3c4d_366b_8def_7fa976df7502 = (Int32)RandomUUID.random();

        private match_player_rsp_cb rsp_cb_match_player_handle;

        public match_player_hubproxy(match_player_rsp_cb rsp_cb_match_player_handle_)
        {
            rsp_cb_match_player_handle = rsp_cb_match_player_handle_;
        }

        public void player_join_game(Int64 player_guid, string game_hub_name){
            var _argv_15145668_2422_3eb1_974a_76053d88b209 = new ArrayList();
            _argv_15145668_2422_3eb1_974a_76053d88b209.Add(player_guid);
            _argv_15145668_2422_3eb1_974a_76053d88b209.Add(game_hub_name);
            hub.hub._hubs.call_hub(hub_name_da7b2c07_3c4d_366b_8def_7fa976df7502, "match_player_player_join_game", _argv_15145668_2422_3eb1_974a_76053d88b209);
        }

    }
/*this module code is codegen by abelkhan codegen for c#*/
    public class match_room_module : common.imodule {
        public match_room_module() 
        {
            hub.hub._modules.add_mothed("match_room_start_game", start_game);
        }

        public event Action<string, string> on_start_game;
        public void start_game(IList<MsgPack.MessagePackObject> inArray){
            var _room_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsString();
            var _game_hub_name = ((MsgPack.MessagePackObject)inArray[1]).AsString();
            if (on_start_game != null){
                on_start_game(_room_uuid, _game_hub_name);
            }
        }

    }
    public class match_player_module : common.imodule {
        public match_player_module() 
        {
            hub.hub._modules.add_mothed("match_player_player_join_game", player_join_game);
        }

        public event Action<Int64, string> on_player_join_game;
        public void player_join_game(IList<MsgPack.MessagePackObject> inArray){
            var _player_guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            var _game_hub_name = ((MsgPack.MessagePackObject)inArray[1]).AsString();
            if (on_player_join_game != null){
                on_player_join_game(_player_guid, _game_hub_name);
            }
        }

    }

}
