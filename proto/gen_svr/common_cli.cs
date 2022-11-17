using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using MsgPack.Serialization;

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for c#*/

    public enum animal{
        chicken = 1,
        monkey = 2,
        rabbit = 3,
        duck = 4,
        mouse = 5,
        bear = 6,
        tiger = 7,
        lion = 8
    }
    public enum skin{
        chicken = 101,
        monkey = 201,
        rabbit = 301,
        duck = 401,
        mouse = 501,
        bear = 601,
        tiger = 701,
        lion = 801
    }
    public enum playground{
        grassland = 1,
        hill = 2,
        snow = 3,
        desert = 4
    }
/*this struct code is codegen by abelkhan codegen for c#*/
    public class player_friend_info
    {
        public Int64 guid;
        public string name;
        public Int32 coin;
        public Int32 score;
        public static MsgPack.MessagePackObjectDictionary player_friend_info_to_protcol(player_friend_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            _protocol.Add("guid", _struct.guid);
            _protocol.Add("name", _struct.name);
            _protocol.Add("coin", _struct.coin);
            _protocol.Add("score", _struct.score);
            return _protocol;
        }
        public static player_friend_info protcol_to_player_friend_info(MsgPack.MessagePackObjectDictionary _protocol){
            var _struct9b9e8b33_ad4e_3bf3_b537_d892bf5094fa = new player_friend_info();
            foreach (var i in _protocol){
                if (((MsgPack.MessagePackObject)i.Key).AsString() == "guid"){
                    _struct9b9e8b33_ad4e_3bf3_b537_d892bf5094fa.guid = ((MsgPack.MessagePackObject)i.Value).AsInt64();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "name"){
                    _struct9b9e8b33_ad4e_3bf3_b537_d892bf5094fa.name = ((MsgPack.MessagePackObject)i.Value).AsString();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "coin"){
                    _struct9b9e8b33_ad4e_3bf3_b537_d892bf5094fa.coin = ((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "score"){
                    _struct9b9e8b33_ad4e_3bf3_b537_d892bf5094fa.score = ((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
            }
            return _struct9b9e8b33_ad4e_3bf3_b537_d892bf5094fa;
        }
    }

    public class player_info
    {
        public Int64 guid;
        public string sdk_uuid;
        public string name;
        public Int32 coin;
        public Int32 score;
        public List<player_friend_info> friend_list;
        public List<animal> hero_list;
        public List<skin> skin_list;
        public List<playground> playground_list;
        public static MsgPack.MessagePackObjectDictionary player_info_to_protcol(player_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            _protocol.Add("guid", _struct.guid);
            _protocol.Add("sdk_uuid", _struct.sdk_uuid);
            _protocol.Add("name", _struct.name);
            _protocol.Add("coin", _struct.coin);
            _protocol.Add("score", _struct.score);
            var _array_friend_list = new List<MsgPack.MessagePackObject>();
            foreach(var v_ in _struct.friend_list){
                _array_friend_list.Add( new MsgPack.MessagePackObject(player_friend_info.player_friend_info_to_protcol(v_)));
            }
            _protocol.Add("friend_list", new MsgPack.MessagePackObject(_array_friend_list));
            var _array_hero_list = new List<MsgPack.MessagePackObject>();
            foreach(var v_ in _struct.hero_list){
                _array_hero_list.Add((Int32)v_);
            }
            _protocol.Add("hero_list", new MsgPack.MessagePackObject(_array_hero_list));
            var _array_skin_list = new List<MsgPack.MessagePackObject>();
            foreach(var v_ in _struct.skin_list){
                _array_skin_list.Add((Int32)v_);
            }
            _protocol.Add("skin_list", new MsgPack.MessagePackObject(_array_skin_list));
            var _array_playground_list = new List<MsgPack.MessagePackObject>();
            foreach(var v_ in _struct.playground_list){
                _array_playground_list.Add((Int32)v_);
            }
            _protocol.Add("playground_list", new MsgPack.MessagePackObject(_array_playground_list));
            return _protocol;
        }
        public static player_info protcol_to_player_info(MsgPack.MessagePackObjectDictionary _protocol){
            var _structba9db598_9e11_365a_9abc_c16f0f380537 = new player_info();
            foreach (var i in _protocol){
                if (((MsgPack.MessagePackObject)i.Key).AsString() == "guid"){
                    _structba9db598_9e11_365a_9abc_c16f0f380537.guid = ((MsgPack.MessagePackObject)i.Value).AsInt64();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "sdk_uuid"){
                    _structba9db598_9e11_365a_9abc_c16f0f380537.sdk_uuid = ((MsgPack.MessagePackObject)i.Value).AsString();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "name"){
                    _structba9db598_9e11_365a_9abc_c16f0f380537.name = ((MsgPack.MessagePackObject)i.Value).AsString();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "coin"){
                    _structba9db598_9e11_365a_9abc_c16f0f380537.coin = ((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "score"){
                    _structba9db598_9e11_365a_9abc_c16f0f380537.score = ((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "friend_list"){
                    _structba9db598_9e11_365a_9abc_c16f0f380537.friend_list = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _structba9db598_9e11_365a_9abc_c16f0f380537.friend_list.Add(player_friend_info.protcol_to_player_friend_info(((MsgPack.MessagePackObject)v_).AsDictionary()));
                    }
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "hero_list"){
                    _structba9db598_9e11_365a_9abc_c16f0f380537.hero_list = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _structba9db598_9e11_365a_9abc_c16f0f380537.hero_list.Add((animal)((MsgPack.MessagePackObject)v_).AsInt32());
                    }
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "skin_list"){
                    _structba9db598_9e11_365a_9abc_c16f0f380537.skin_list = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _structba9db598_9e11_365a_9abc_c16f0f380537.skin_list.Add((skin)((MsgPack.MessagePackObject)v_).AsInt32());
                    }
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "playground_list"){
                    _structba9db598_9e11_365a_9abc_c16f0f380537.playground_list = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _structba9db598_9e11_365a_9abc_c16f0f380537.playground_list.Add((playground)((MsgPack.MessagePackObject)v_).AsInt32());
                    }
                }
            }
            return _structba9db598_9e11_365a_9abc_c16f0f380537;
        }
    }

    public class player_inline_info
    {
        public string uuid;
        public Int64 guid;
        public string name;
        public Int32 coin;
        public Int32 score;
        public static MsgPack.MessagePackObjectDictionary player_inline_info_to_protcol(player_inline_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            _protocol.Add("uuid", _struct.uuid);
            _protocol.Add("guid", _struct.guid);
            _protocol.Add("name", _struct.name);
            _protocol.Add("coin", _struct.coin);
            _protocol.Add("score", _struct.score);
            return _protocol;
        }
        public static player_inline_info protcol_to_player_inline_info(MsgPack.MessagePackObjectDictionary _protocol){
            var _structcdacc51b_f718_3ebb_ad22_096d86e7efee = new player_inline_info();
            foreach (var i in _protocol){
                if (((MsgPack.MessagePackObject)i.Key).AsString() == "uuid"){
                    _structcdacc51b_f718_3ebb_ad22_096d86e7efee.uuid = ((MsgPack.MessagePackObject)i.Value).AsString();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "guid"){
                    _structcdacc51b_f718_3ebb_ad22_096d86e7efee.guid = ((MsgPack.MessagePackObject)i.Value).AsInt64();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "name"){
                    _structcdacc51b_f718_3ebb_ad22_096d86e7efee.name = ((MsgPack.MessagePackObject)i.Value).AsString();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "coin"){
                    _structcdacc51b_f718_3ebb_ad22_096d86e7efee.coin = ((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "score"){
                    _structcdacc51b_f718_3ebb_ad22_096d86e7efee.score = ((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
            }
            return _structcdacc51b_f718_3ebb_ad22_096d86e7efee;
        }
    }

    public class room_info
    {
        public string room_uuid;
        public Int64 room_owner_guid;
        public List<player_inline_info> room_player_list;
        public static MsgPack.MessagePackObjectDictionary room_info_to_protcol(room_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            _protocol.Add("room_uuid", _struct.room_uuid);
            _protocol.Add("room_owner_guid", _struct.room_owner_guid);
            var _array_room_player_list = new List<MsgPack.MessagePackObject>();
            foreach(var v_ in _struct.room_player_list){
                _array_room_player_list.Add( new MsgPack.MessagePackObject(player_inline_info.player_inline_info_to_protcol(v_)));
            }
            _protocol.Add("room_player_list", new MsgPack.MessagePackObject(_array_room_player_list));
            return _protocol;
        }
        public static room_info protcol_to_room_info(MsgPack.MessagePackObjectDictionary _protocol){
            var _struct6bdeecee_07e7_32d2_a4bc_6ebc8b13f116 = new room_info();
            foreach (var i in _protocol){
                if (((MsgPack.MessagePackObject)i.Key).AsString() == "room_uuid"){
                    _struct6bdeecee_07e7_32d2_a4bc_6ebc8b13f116.room_uuid = ((MsgPack.MessagePackObject)i.Value).AsString();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "room_owner_guid"){
                    _struct6bdeecee_07e7_32d2_a4bc_6ebc8b13f116.room_owner_guid = ((MsgPack.MessagePackObject)i.Value).AsInt64();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "room_player_list"){
                    _struct6bdeecee_07e7_32d2_a4bc_6ebc8b13f116.room_player_list = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _struct6bdeecee_07e7_32d2_a4bc_6ebc8b13f116.room_player_list.Add(player_inline_info.protcol_to_player_inline_info(((MsgPack.MessagePackObject)v_).AsDictionary()));
                    }
                }
            }
            return _struct6bdeecee_07e7_32d2_a4bc_6ebc8b13f116;
        }
    }

    public class game_player_settle_info
    {
        public Int64 guid;
        public string name;
        public Int32 award_coin;
        public Int32 award_score;
        public static MsgPack.MessagePackObjectDictionary game_player_settle_info_to_protcol(game_player_settle_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            _protocol.Add("guid", _struct.guid);
            _protocol.Add("name", _struct.name);
            _protocol.Add("award_coin", _struct.award_coin);
            _protocol.Add("award_score", _struct.award_score);
            return _protocol;
        }
        public static game_player_settle_info protcol_to_game_player_settle_info(MsgPack.MessagePackObjectDictionary _protocol){
            var _structeb1fe0ef_fca5_358c_91c2_45f20a7adbea = new game_player_settle_info();
            foreach (var i in _protocol){
                if (((MsgPack.MessagePackObject)i.Key).AsString() == "guid"){
                    _structeb1fe0ef_fca5_358c_91c2_45f20a7adbea.guid = ((MsgPack.MessagePackObject)i.Value).AsInt64();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "name"){
                    _structeb1fe0ef_fca5_358c_91c2_45f20a7adbea.name = ((MsgPack.MessagePackObject)i.Value).AsString();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "award_coin"){
                    _structeb1fe0ef_fca5_358c_91c2_45f20a7adbea.award_coin = ((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "award_score"){
                    _structeb1fe0ef_fca5_358c_91c2_45f20a7adbea.award_score = ((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
            }
            return _structeb1fe0ef_fca5_358c_91c2_45f20a7adbea;
        }
    }

    public class game_settle_info
    {
        public List<game_player_settle_info> settle_info;
        public static MsgPack.MessagePackObjectDictionary game_settle_info_to_protcol(game_settle_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            var _array_settle_info = new List<MsgPack.MessagePackObject>();
            foreach(var v_ in _struct.settle_info){
                _array_settle_info.Add( new MsgPack.MessagePackObject(game_player_settle_info.game_player_settle_info_to_protcol(v_)));
            }
            _protocol.Add("settle_info", new MsgPack.MessagePackObject(_array_settle_info));
            return _protocol;
        }
        public static game_settle_info protcol_to_game_settle_info(MsgPack.MessagePackObjectDictionary _protocol){
            var _structc73167a1_d0f0_32a5_8b31_3928f54f36c2 = new game_settle_info();
            foreach (var i in _protocol){
                if (((MsgPack.MessagePackObject)i.Key).AsString() == "settle_info"){
                    _structc73167a1_d0f0_32a5_8b31_3928f54f36c2.settle_info = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _structc73167a1_d0f0_32a5_8b31_3928f54f36c2.settle_info.Add(game_player_settle_info.protcol_to_game_player_settle_info(((MsgPack.MessagePackObject)v_).AsDictionary()));
                    }
                }
            }
            return _structc73167a1_d0f0_32a5_8b31_3928f54f36c2;
        }
    }

/*this module code is codegen by abelkhan codegen for c#*/

}
