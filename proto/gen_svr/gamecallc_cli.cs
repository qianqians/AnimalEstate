using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using MsgPack.Serialization;

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for c#*/

/*this struct code is codegen by abelkhan codegen for c#*/
    public class effect_info
    {
        public List<Int16> grids;
        public effect effect_id;
        public static MsgPack.MessagePackObjectDictionary effect_info_to_protcol(effect_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            var _array_grids = new List<MsgPack.MessagePackObject>();
            foreach(var v_ in _struct.grids){
                _array_grids.Add(v_);
            }
            _protocol.Add("grids", new MsgPack.MessagePackObject(_array_grids));
            _protocol.Add("effect_id", (Int32)_struct.effect_id);
            return _protocol;
        }
        public static effect_info protcol_to_effect_info(MsgPack.MessagePackObjectDictionary _protocol){
            var _struct3934263e_8a7e_3773_9a47_c85f982b70f5 = new effect_info();
            foreach (var i in _protocol){
                if (((MsgPack.MessagePackObject)i.Key).AsString() == "grids"){
                    _struct3934263e_8a7e_3773_9a47_c85f982b70f5.grids = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _struct3934263e_8a7e_3773_9a47_c85f982b70f5.grids.Add(((MsgPack.MessagePackObject)v_).AsInt16());
                    }
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "effect_id"){
                    _struct3934263e_8a7e_3773_9a47_c85f982b70f5.effect_id = (effect)((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
            }
            return _struct3934263e_8a7e_3773_9a47_c85f982b70f5;
        }
    }

/*this module code is codegen by abelkhan codegen for c#*/
    public class game_client_module : common.imodule {
        public client.client _client_handle;
        public game_client_module(client.client client_handle_) 
        {
            _client_handle = client_handle_;
            _client_handle.modulemanager.add_mothed("game_client_game_info", game_info);
            _client_handle.modulemanager.add_mothed("game_client_move", move);
            _client_handle.modulemanager.add_mothed("game_client_relay", relay);
            _client_handle.modulemanager.add_mothed("game_client_effect", effect);
            _client_handle.modulemanager.add_mothed("game_client_use_skill", use_skill);
            _client_handle.modulemanager.add_mothed("game_client_effect_move", effect_move);
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

        public event Action<Int64, Int16> on_relay;
        public void relay(IList<MsgPack.MessagePackObject> inArray){
            var _guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            var _new_animal_index = ((MsgPack.MessagePackObject)inArray[1]).AsInt16();
            if (on_relay != null){
                on_relay(_guid, _new_animal_index);
            }
        }

        public event Action<effect_info> on_effect;
        public void effect(IList<MsgPack.MessagePackObject> inArray){
            var _info = effect_info.protcol_to_effect_info(((MsgPack.MessagePackObject)inArray[0]).AsDictionary());
            if (on_effect != null){
                on_effect(_info);
            }
        }

        public event Action<Int64> on_use_skill;
        public void use_skill(IList<MsgPack.MessagePackObject> inArray){
            var _guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            if (on_use_skill != null){
                on_use_skill(_guid);
            }
        }

        public event Action<Int64, effect, Int32, Int32> on_effect_move;
        public void effect_move(IList<MsgPack.MessagePackObject> inArray){
            var _guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            var _effect_id = (effect)((MsgPack.MessagePackObject)inArray[1]).AsInt32();
            var _from = ((MsgPack.MessagePackObject)inArray[2]).AsInt32();
            var _to = ((MsgPack.MessagePackObject)inArray[3]).AsInt32();
            if (on_effect_move != null){
                on_effect_move(_guid, _effect_id, _from, _to);
            }
        }

    }

}
