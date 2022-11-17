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
        private Int64 uuid_7be997e8_0e81_3728_9f6b_2f2429d08950 = (Int64)RandomUUID.random();

        private match_room_rsp_cb rsp_cb_match_room_handle;

        public match_room_hubproxy(match_room_rsp_cb rsp_cb_match_room_handle_)
        {
            rsp_cb_match_room_handle = rsp_cb_match_room_handle_;
        }

        public void room_match_join_room(string target_room_uuid, room_info info){
            var _argv_ac2531ad_d64e_3198_8082_8618ce9270ca = new ArrayList();
            _argv_ac2531ad_d64e_3198_8082_8618ce9270ca.Add(target_room_uuid);
            _argv_ac2531ad_d64e_3198_8082_8618ce9270ca.Add(room_info.room_info_to_protcol(info));
            hub.hub._hubs.call_hub(hub_name_7be997e8_0e81_3728_9f6b_2f2429d08950, "match_room_room_match_join_room", _argv_ac2531ad_d64e_3198_8082_8618ce9270ca);
        }

        public void room_match_join_room_release(string room_uuid){
            var _argv_9d12c629_dc63_36d7_aec3_eb4c3330b42e = new ArrayList();
            _argv_9d12c629_dc63_36d7_aec3_eb4c3330b42e.Add(room_uuid);
            hub.hub._hubs.call_hub(hub_name_7be997e8_0e81_3728_9f6b_2f2429d08950, "match_room_room_match_join_room_release", _argv_9d12c629_dc63_36d7_aec3_eb4c3330b42e);
        }

        public void player_join_room(string target_room_uuid, player_inline_info info){
            var _argv_c7931b32_1f6d_3e14_ba23_5d00c3db1d8e = new ArrayList();
            _argv_c7931b32_1f6d_3e14_ba23_5d00c3db1d8e.Add(target_room_uuid);
            _argv_c7931b32_1f6d_3e14_ba23_5d00c3db1d8e.Add(player_inline_info.player_inline_info_to_protcol(info));
            hub.hub._hubs.call_hub(hub_name_7be997e8_0e81_3728_9f6b_2f2429d08950, "match_room_player_join_room", _argv_c7931b32_1f6d_3e14_ba23_5d00c3db1d8e);
        }

        public void start_game(string room_uuid, string game_hub_name){
            var _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747 = new ArrayList();
            _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747.Add(room_uuid);
            _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747.Add(game_hub_name);
            hub.hub._hubs.call_hub(hub_name_7be997e8_0e81_3728_9f6b_2f2429d08950, "match_room_start_game", _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747);
        }

    }
/*this module code is codegen by abelkhan codegen for c#*/
    public class match_room_module : common.imodule {
        public match_room_module() 
        {
            hub.hub._modules.add_mothed("match_room_room_match_join_room", room_match_join_room);
            hub.hub._modules.add_mothed("match_room_room_match_join_room_release", room_match_join_room_release);
            hub.hub._modules.add_mothed("match_room_player_join_room", player_join_room);
            hub.hub._modules.add_mothed("match_room_start_game", start_game);
        }

        public event Action<string, room_info> on_room_match_join_room;
        public void room_match_join_room(IList<MsgPack.MessagePackObject> inArray){
            var _target_room_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsString();
            var _info = room_info.protcol_to_room_info(((MsgPack.MessagePackObject)inArray[1]).AsDictionary());
            if (on_room_match_join_room != null){
                on_room_match_join_room(_target_room_uuid, _info);
            }
        }

        public event Action<string> on_room_match_join_room_release;
        public void room_match_join_room_release(IList<MsgPack.MessagePackObject> inArray){
            var _room_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsString();
            if (on_room_match_join_room_release != null){
                on_room_match_join_room_release(_room_uuid);
            }
        }

        public event Action<string, player_inline_info> on_player_join_room;
        public void player_join_room(IList<MsgPack.MessagePackObject> inArray){
            var _target_room_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsString();
            var _info = player_inline_info.protcol_to_player_inline_info(((MsgPack.MessagePackObject)inArray[1]).AsDictionary());
            if (on_player_join_room != null){
                on_player_join_room(_target_room_uuid, _info);
            }
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

}
