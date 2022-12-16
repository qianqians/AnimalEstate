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
        public Int32 continued_rounds;
        public static MsgPack.MessagePackObjectDictionary effect_info_to_protcol(effect_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            var _array_grids = new List<MsgPack.MessagePackObject>();
            foreach(var v_ in _struct.grids){
                _array_grids.Add(v_);
            }
            _protocol.Add("grids", new MsgPack.MessagePackObject(_array_grids));
            _protocol.Add("effect_id", (Int32)_struct.effect_id);
            _protocol.Add("continued_rounds", _struct.continued_rounds);
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
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "continued_rounds"){
                    _struct3934263e_8a7e_3773_9a47_c85f982b70f5.continued_rounds = ((MsgPack.MessagePackObject)i.Value).AsInt32();
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
            _client_handle.modulemanager.add_mothed("game_client_game_wait_start_info", game_wait_start_info);
            _client_handle.modulemanager.add_mothed("game_client_game_info", game_info);
            _client_handle.modulemanager.add_mothed("game_client_ntf_effect_info", ntf_effect_info);
            _client_handle.modulemanager.add_mothed("game_client_ntf_new_effect_info", ntf_new_effect_info);
            _client_handle.modulemanager.add_mothed("game_client_turn_player_round", turn_player_round);
            _client_handle.modulemanager.add_mothed("game_client_throw_dice", throw_dice);
            _client_handle.modulemanager.add_mothed("game_client_move", move);
            _client_handle.modulemanager.add_mothed("game_client_relay", relay);
            _client_handle.modulemanager.add_mothed("game_client_use_skill", use_skill);
            _client_handle.modulemanager.add_mothed("game_client_effect_move", effect_move);
        }

        public event Action<Int32, playground, List<player_game_info>> on_game_wait_start_info;
        public void game_wait_start_info(IList<MsgPack.MessagePackObject> inArray){
            var _countdown = ((MsgPack.MessagePackObject)inArray[0]).AsInt32();
            var __playground = (playground)((MsgPack.MessagePackObject)inArray[1]).AsInt32();
            var _info = new List<player_game_info>();
            var _protocol_arrayinfo = ((MsgPack.MessagePackObject)inArray[2]).AsList();
            foreach (var v_d856b000_56e0_5f62_a6f3_e6a0c7859745 in _protocol_arrayinfo){
                _info.Add(player_game_info.protcol_to_player_game_info(((MsgPack.MessagePackObject)v_d856b000_56e0_5f62_a6f3_e6a0c7859745).AsDictionary()));
            }
            if (on_game_wait_start_info != null){
                on_game_wait_start_info(_countdown, __playground, _info);
            }
        }

        public event Action<playground, List<player_game_info>, Int64> on_game_info;
        public void game_info(IList<MsgPack.MessagePackObject> inArray){
            var __playground = (playground)((MsgPack.MessagePackObject)inArray[0]).AsInt32();
            var _info = new List<player_game_info>();
            var _protocol_arrayinfo = ((MsgPack.MessagePackObject)inArray[1]).AsList();
            foreach (var v_d856b000_56e0_5f62_a6f3_e6a0c7859745 in _protocol_arrayinfo){
                _info.Add(player_game_info.protcol_to_player_game_info(((MsgPack.MessagePackObject)v_d856b000_56e0_5f62_a6f3_e6a0c7859745).AsDictionary()));
            }
            var _round_player_guid = ((MsgPack.MessagePackObject)inArray[2]).AsInt64();
            if (on_game_info != null){
                on_game_info(__playground, _info, _round_player_guid);
            }
        }

        public event Action<List<effect_info>> on_ntf_effect_info;
        public void ntf_effect_info(IList<MsgPack.MessagePackObject> inArray){
            var _info = new List<effect_info>();
            var _protocol_arrayinfo = ((MsgPack.MessagePackObject)inArray[0]).AsList();
            foreach (var v_d856b000_56e0_5f62_a6f3_e6a0c7859745 in _protocol_arrayinfo){
                _info.Add(effect_info.protcol_to_effect_info(((MsgPack.MessagePackObject)v_d856b000_56e0_5f62_a6f3_e6a0c7859745).AsDictionary()));
            }
            if (on_ntf_effect_info != null){
                on_ntf_effect_info(_info);
            }
        }

        public event Action<effect_info> on_ntf_new_effect_info;
        public void ntf_new_effect_info(IList<MsgPack.MessagePackObject> inArray){
            var _info = effect_info.protcol_to_effect_info(((MsgPack.MessagePackObject)inArray[0]).AsDictionary());
            if (on_ntf_new_effect_info != null){
                on_ntf_new_effect_info(_info);
            }
        }

        public event Action<Int64> on_turn_player_round;
        public void turn_player_round(IList<MsgPack.MessagePackObject> inArray){
            var _guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            if (on_turn_player_round != null){
                on_turn_player_round(_guid);
            }
        }

        public event Action<Int64, List<Int32>> on_throw_dice;
        public void throw_dice(IList<MsgPack.MessagePackObject> inArray){
            var _guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            var _dice = new List<Int32>();
            var _protocol_arraydice = ((MsgPack.MessagePackObject)inArray[1]).AsList();
            foreach (var v_9bcc4d08_9a5f_58b1_8d7e_695c05d8e04f in _protocol_arraydice){
                _dice.Add(((MsgPack.MessagePackObject)v_9bcc4d08_9a5f_58b1_8d7e_695c05d8e04f).AsInt32());
            }
            if (on_throw_dice != null){
                on_throw_dice(_guid, _dice);
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

        public event Action<Int64, Int64, Int16> on_use_skill;
        public void use_skill(IList<MsgPack.MessagePackObject> inArray){
            var _guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            var _target_guid = ((MsgPack.MessagePackObject)inArray[1]).AsInt64();
            var _target_animal_index = ((MsgPack.MessagePackObject)inArray[2]).AsInt16();
            if (on_use_skill != null){
                on_use_skill(_guid, _target_guid, _target_animal_index);
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
