using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using MsgPack.Serialization;

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for c#*/

/*this struct code is codegen by abelkhan codegen for c#*/
/*this module code is codegen by abelkhan codegen for c#*/
    public class room_client_module : common.imodule {
        public client.client _client_handle;
        public room_client_module(client.client client_handle_) 
        {
            _client_handle = client_handle_;
            _client_handle.modulemanager.add_mothed("room_client_refresh_room_info", refresh_room_info);
            _client_handle.modulemanager.add_mothed("room_client_transfer_refresh_room_info", transfer_refresh_room_info);
            _client_handle.modulemanager.add_mothed("room_client_chat", chat);
            _client_handle.modulemanager.add_mothed("room_client_room_is_free", room_is_free);
            _client_handle.modulemanager.add_mothed("room_client_player_leave_room_success", player_leave_room_success);
            _client_handle.modulemanager.add_mothed("room_client_be_kicked", be_kicked);
            _client_handle.modulemanager.add_mothed("room_client_team_into_match", team_into_match);
        }

        public event Action<room_info> on_refresh_room_info;
        public void refresh_room_info(IList<MsgPack.MessagePackObject> inArray){
            var _info = room_info.protcol_to_room_info(((MsgPack.MessagePackObject)inArray[0]).AsDictionary());
            if (on_refresh_room_info != null){
                on_refresh_room_info(_info);
            }
        }

        public event Action<string, room_info> on_transfer_refresh_room_info;
        public void transfer_refresh_room_info(IList<MsgPack.MessagePackObject> inArray){
            var _room_hub_name = ((MsgPack.MessagePackObject)inArray[0]).AsString();
            var _info = room_info.protcol_to_room_info(((MsgPack.MessagePackObject)inArray[1]).AsDictionary());
            if (on_transfer_refresh_room_info != null){
                on_transfer_refresh_room_info(_room_hub_name, _info);
            }
        }

        public event Action<Int64, string> on_chat;
        public void chat(IList<MsgPack.MessagePackObject> inArray){
            var _chat_player_guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            var _chat_str = ((MsgPack.MessagePackObject)inArray[1]).AsString();
            if (on_chat != null){
                on_chat(_chat_player_guid, _chat_str);
            }
        }

        public event Action on_room_is_free;
        public void room_is_free(IList<MsgPack.MessagePackObject> inArray){
            if (on_room_is_free != null){
                on_room_is_free();
            }
        }

        public event Action on_player_leave_room_success;
        public void player_leave_room_success(IList<MsgPack.MessagePackObject> inArray){
            if (on_player_leave_room_success != null){
                on_player_leave_room_success();
            }
        }

        public event Action on_be_kicked;
        public void be_kicked(IList<MsgPack.MessagePackObject> inArray){
            if (on_be_kicked != null){
                on_be_kicked();
            }
        }

        public event Action on_team_into_match;
        public void team_into_match(IList<MsgPack.MessagePackObject> inArray){
            if (on_team_into_match != null){
                on_team_into_match();
            }
        }

    }
    public class room_match_client_module : common.imodule {
        public client.client _client_handle;
        public room_match_client_module(client.client client_handle_) 
        {
            _client_handle = client_handle_;
            _client_handle.modulemanager.add_mothed("room_match_client_role_into_game", role_into_game);
        }

        public event Action<string> on_role_into_game;
        public void role_into_game(IList<MsgPack.MessagePackObject> inArray){
            var _game_hub_name = ((MsgPack.MessagePackObject)inArray[0]).AsString();
            if (on_role_into_game != null){
                on_role_into_game(_game_hub_name);
            }
        }

    }

}
