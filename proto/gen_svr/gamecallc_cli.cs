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
    public class game_client_module : common.imodule {
        public client.client _client_handle;
        public game_client_module(client.client client_handle_) 
        {
            _client_handle = client_handle_;
            _client_handle.modulemanager.add_mothed("game_client_game_info", game_info);
            _client_handle.modulemanager.add_mothed("game_client_move", move);
        }

        public event Action<List<player_game_info>> on_game_info;
        public void game_info(IList<MsgPack.MessagePackObject> inArray){
            var _info = new List<player_game_info>();
            var _protocol_arrayinfo = ((MsgPack.MessagePackObject)inArray[0]).AsList();
            foreach (var v_d856b000_56e0_5f62_a6f3_e6a0c7859745 in _protocol_arrayinfo){
                _info.Add(player_game_info.protcol_to_player_game_info(((MsgPack.MessagePackObject)v_d856b000_56e0_5f62_a6f3_e6a0c7859745).AsDictionary()));
            }
            if (on_game_info != null){
                on_game_info(_info);
            }
        }

        public event Action<Int64, Int32, Int32> on_move;
        public void move(IList<MsgPack.MessagePackObject> inArray){
            var _guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            var _from = ((MsgPack.MessagePackObject)inArray[1]).AsInt32();
            var _to = ((MsgPack.MessagePackObject)inArray[2]).AsInt32();
            if (on_move != null){
                on_move(_guid, _from, _to);
            }
        }

    }

}
