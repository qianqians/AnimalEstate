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
    public enum effect{
        muddy = 1,
        banana_peel = 2,
        golden_apple = 3,
        rice_ear = 4,
        monkey_wine = 5,
        mouse_trap = 100
    }
    public enum playground{
        random = 0,
        lakeside = 1,
        grassland = 2,
        hill = 3,
        snow = 4,
        desert = 5
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
        public List<player_friend_info> invite_list;
        public List<player_friend_info> be_invited_list;
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
            var _array_invite_list = new List<MsgPack.MessagePackObject>();
            foreach(var v_ in _struct.invite_list){
                _array_invite_list.Add( new MsgPack.MessagePackObject(player_friend_info.player_friend_info_to_protcol(v_)));
            }
            _protocol.Add("invite_list", new MsgPack.MessagePackObject(_array_invite_list));
            var _array_be_invited_list = new List<MsgPack.MessagePackObject>();
            foreach(var v_ in _struct.be_invited_list){
                _array_be_invited_list.Add( new MsgPack.MessagePackObject(player_friend_info.player_friend_info_to_protcol(v_)));
            }
            _protocol.Add("be_invited_list", new MsgPack.MessagePackObject(_array_be_invited_list));
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
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "invite_list"){
                    _structba9db598_9e11_365a_9abc_c16f0f380537.invite_list = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _structba9db598_9e11_365a_9abc_c16f0f380537.invite_list.Add(player_friend_info.protcol_to_player_friend_info(((MsgPack.MessagePackObject)v_).AsDictionary()));
                    }
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "be_invited_list"){
                    _structba9db598_9e11_365a_9abc_c16f0f380537.be_invited_list = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _structba9db598_9e11_365a_9abc_c16f0f380537.be_invited_list.Add(player_friend_info.protcol_to_player_friend_info(((MsgPack.MessagePackObject)v_).AsDictionary()));
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
        public List<animal> hero_list;
        public List<skin> skin_list;
        public List<playground> playground_list;
        public static MsgPack.MessagePackObjectDictionary player_inline_info_to_protcol(player_inline_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            _protocol.Add("uuid", _struct.uuid);
            _protocol.Add("guid", _struct.guid);
            _protocol.Add("name", _struct.name);
            _protocol.Add("coin", _struct.coin);
            _protocol.Add("score", _struct.score);
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
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "hero_list"){
                    _structcdacc51b_f718_3ebb_ad22_096d86e7efee.hero_list = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _structcdacc51b_f718_3ebb_ad22_096d86e7efee.hero_list.Add((animal)((MsgPack.MessagePackObject)v_).AsInt32());
                    }
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "skin_list"){
                    _structcdacc51b_f718_3ebb_ad22_096d86e7efee.skin_list = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _structcdacc51b_f718_3ebb_ad22_096d86e7efee.skin_list.Add((skin)((MsgPack.MessagePackObject)v_).AsInt32());
                    }
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "playground_list"){
                    _structcdacc51b_f718_3ebb_ad22_096d86e7efee.playground_list = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _structcdacc51b_f718_3ebb_ad22_096d86e7efee.playground_list.Add((playground)((MsgPack.MessagePackObject)v_).AsInt32());
                    }
                }
            }
            return _structcdacc51b_f718_3ebb_ad22_096d86e7efee;
        }
    }

    public class room_info
    {
        public string room_uuid;
        public Int64 room_owner_guid;
        public playground _playground;
        public List<player_inline_info> room_player_list;
        public static MsgPack.MessagePackObjectDictionary room_info_to_protcol(room_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            _protocol.Add("room_uuid", _struct.room_uuid);
            _protocol.Add("room_owner_guid", _struct.room_owner_guid);
            _protocol.Add("_playground", (Int32)_struct._playground);
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
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "_playground"){
                    _struct6bdeecee_07e7_32d2_a4bc_6ebc8b13f116._playground = (playground)((MsgPack.MessagePackObject)i.Value).AsInt32();
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

    public class animal_game_info
    {
        public animal animal_id;
        public skin skin_id;
        public static MsgPack.MessagePackObjectDictionary animal_game_info_to_protcol(animal_game_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            _protocol.Add("animal_id", (Int32)_struct.animal_id);
            _protocol.Add("skin_id", (Int32)_struct.skin_id);
            return _protocol;
        }
        public static animal_game_info protcol_to_animal_game_info(MsgPack.MessagePackObjectDictionary _protocol){
            var _struct0f490332_8543_30ad_92b2_6c49981b121d = new animal_game_info();
            foreach (var i in _protocol){
                if (((MsgPack.MessagePackObject)i.Key).AsString() == "animal_id"){
                    _struct0f490332_8543_30ad_92b2_6c49981b121d.animal_id = (animal)((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "skin_id"){
                    _struct0f490332_8543_30ad_92b2_6c49981b121d.skin_id = (skin)((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
            }
            return _struct0f490332_8543_30ad_92b2_6c49981b121d;
        }
    }

    public class player_game_info
    {
        public string uuid;
        public Int64 guid;
        public string name;
        public List<animal_game_info> animal_info;
        public Int16 current_animal_index;
        public Int16 current_pos;
        public static MsgPack.MessagePackObjectDictionary player_game_info_to_protcol(player_game_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            _protocol.Add("uuid", _struct.uuid);
            _protocol.Add("guid", _struct.guid);
            _protocol.Add("name", _struct.name);
            var _array_animal_info = new List<MsgPack.MessagePackObject>();
            foreach(var v_ in _struct.animal_info){
                _array_animal_info.Add( new MsgPack.MessagePackObject(animal_game_info.animal_game_info_to_protcol(v_)));
            }
            _protocol.Add("animal_info", new MsgPack.MessagePackObject(_array_animal_info));
            _protocol.Add("current_animal_index", _struct.current_animal_index);
            _protocol.Add("current_pos", _struct.current_pos);
            return _protocol;
        }
        public static player_game_info protcol_to_player_game_info(MsgPack.MessagePackObjectDictionary _protocol){
            var _structa9e105de_cbf5_3520_93fb_036b8466d4f5 = new player_game_info();
            foreach (var i in _protocol){
                if (((MsgPack.MessagePackObject)i.Key).AsString() == "uuid"){
                    _structa9e105de_cbf5_3520_93fb_036b8466d4f5.uuid = ((MsgPack.MessagePackObject)i.Value).AsString();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "guid"){
                    _structa9e105de_cbf5_3520_93fb_036b8466d4f5.guid = ((MsgPack.MessagePackObject)i.Value).AsInt64();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "name"){
                    _structa9e105de_cbf5_3520_93fb_036b8466d4f5.name = ((MsgPack.MessagePackObject)i.Value).AsString();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "animal_info"){
                    _structa9e105de_cbf5_3520_93fb_036b8466d4f5.animal_info = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _structa9e105de_cbf5_3520_93fb_036b8466d4f5.animal_info.Add(animal_game_info.protcol_to_animal_game_info(((MsgPack.MessagePackObject)v_).AsDictionary()));
                    }
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "current_animal_index"){
                    _structa9e105de_cbf5_3520_93fb_036b8466d4f5.current_animal_index = ((MsgPack.MessagePackObject)i.Value).AsInt16();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "current_pos"){
                    _structa9e105de_cbf5_3520_93fb_036b8466d4f5.current_pos = ((MsgPack.MessagePackObject)i.Value).AsInt16();
                }
            }
            return _structa9e105de_cbf5_3520_93fb_036b8466d4f5;
        }
    }

    public class game_player_settle_info
    {
        public Int64 guid;
        public string name;
        public Int32 rank;
        public Int32 award_coin;
        public Int32 award_score;
        public static MsgPack.MessagePackObjectDictionary game_player_settle_info_to_protcol(game_player_settle_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            _protocol.Add("guid", _struct.guid);
            _protocol.Add("name", _struct.name);
            _protocol.Add("rank", _struct.rank);
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
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "rank"){
                    _structeb1fe0ef_fca5_358c_91c2_45f20a7adbea.rank = ((MsgPack.MessagePackObject)i.Value).AsInt32();
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

    public class svr_info
    {
        public Int32 tick_time;
        public Int32 player_num;
        public static MsgPack.MessagePackObjectDictionary svr_info_to_protcol(svr_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            _protocol.Add("tick_time", _struct.tick_time);
            _protocol.Add("player_num", _struct.player_num);
            return _protocol;
        }
        public static svr_info protcol_to_svr_info(MsgPack.MessagePackObjectDictionary _protocol){
            var _struct13f334ce_724e_3749_be0d_3222168d7a26 = new svr_info();
            foreach (var i in _protocol){
                if (((MsgPack.MessagePackObject)i.Key).AsString() == "tick_time"){
                    _struct13f334ce_724e_3749_be0d_3222168d7a26.tick_time = ((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "player_num"){
                    _struct13f334ce_724e_3749_be0d_3222168d7a26.player_num = ((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
            }
            return _struct13f334ce_724e_3749_be0d_3222168d7a26;
        }
    }

/*this caller code is codegen by abelkhan codegen for c#*/
/*this module code is codegen by abelkhan codegen for c#*/

}
