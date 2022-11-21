using abelkhan;
using log;
using MongoDB.Bson.Serialization;
using MongoDB.Bson;
using Newtonsoft.Json.Linq;
using System;
using System.Security.Cryptography;
using System.Security.Principal;
using System.Threading;
using System.Xml.Linq;
using System.IO;
using offline_msg;
using MsgPack.Serialization;

namespace player
{
    class client_msg_handle
    {
        private readonly player_login_module player_login_Module;
        private readonly client_match_module client_match_Module;
        private readonly client_room_player_module client_Room_Player_Module;
        private readonly client_friend_lobby_module client_Friend_Lobby_Module;

        public client_msg_handle()
        {
            player_login_Module = new ();
            player_login_Module.on_player_login += Login_Player_Module_on_player_login;
            player_login_Module.on_create_role += Player_login_Module_on_create_role;

            client_match_Module = new ();
            client_match_Module.on_start_match += Client_match_Module_on_start_match;

            client_Room_Player_Module = new ();
            client_Room_Player_Module.on_create_room += Client_Room_Player_Module_on_create_room;
            client_Room_Player_Module.on_invite_role_join_room += Client_Room_Player_Module_on_invite_role_join_room;
            client_Room_Player_Module.on_agree_join_room += Client_Room_Player_Module_on_agree_join_room;

            client_Friend_Lobby_Module = new ();
            client_Friend_Lobby_Module.on_find_role += Client_Friend_Lobby_Module_on_find_role;
            client_Friend_Lobby_Module.on_invite_role_friend += Client_Friend_Lobby_Module_on_invite_role_friend;
            client_Friend_Lobby_Module.on_agree_role_friend += Client_Friend_Lobby_Module_on_agree_role_friend;

            player.offline_Msg_Mng.register_offline_msg_callback("invite_friend_msg", process_invite_friend_msg);
            player.offline_Msg_Mng.register_offline_msg_callback("agree_friend_msg", process_agree_friend_msg);
        }

        public struct invite_friend_msg
        {
            public player_friend_info invite_role;
            public player_friend_info target_role;
        }

        private void process_invite_friend_msg(offline_msg.offline_msg_mng.offline_msg msg)
        {
            using (var _tmp = new MemoryStream())
            {
                _tmp.Write(msg.msg, 0, msg.msg.Length);
                _tmp.Position = 0;
                var _serializer = MessagePackSerializer.Get<invite_friend_msg>();
                var _invite_friend_msg = _serializer.Unpack(_tmp);

                var target_player = player.client_Mng.guid_get_client_proxy(long.Parse(msg.player_guid));
                target_player.be_invite(_invite_friend_msg.invite_role);

                client_mng.PlayerFriend_CliendCaller.get_client(target_player.uuid).invite_role_friend(_invite_friend_msg.invite_role).callBack(
                    () => {
                        player.offline_Msg_Mng.del_offline_msg(msg.msg_guid);
                    },
                    () => {
                        log.log.err($"_lobby_friend_client_caller invite_role_friend err! role.guid:{target_player.PlayerInfo.guid}");
                    }
                );
            }
        }

        public struct agree_friend_msg
        {
            public long be_invited_role_guid;
        }

        private void process_agree_friend_msg(offline_msg.offline_msg_mng.offline_msg msg)
        {
            using (var _tmp = new MemoryStream())
            {
                _tmp.Write(msg.msg, 0, msg.msg.Length);
                _tmp.Position = 0;
                var _serializer = MessagePackSerializer.Get<agree_friend_msg>();
                var _invite_friend_msg = _serializer.Unpack(_tmp);

                var invite_role = player.client_Mng.guid_get_client_proxy(long.Parse(msg.player_guid));
                var be_invited_role_info = invite_role.confirm_agree_invite_friend(_invite_friend_msg.be_invited_role_guid);

                client_mng.PlayerFriend_CliendCaller.get_client(invite_role.uuid).agree_role_friend(be_invited_role_info).callBack(
                    () => {
                        player.offline_Msg_Mng.del_offline_msg(msg.msg_guid);
                    },
                    () => {
                        log.log.err($"_lobby_friend_client_caller invite_role_friend err! role.guid:{invite_role.PlayerInfo.guid}");
                    }
                );
            }
        }

        private void Client_Friend_Lobby_Module_on_agree_role_friend(long invite_guid, bool be_agree)
        {
            log.log.trace("on_agree_role_friend begin!");

            var uuid = hub.hub._gates.current_client_uuid;
            var _player = player.client_Mng.uuid_get_client_proxy(uuid);
            _player.agree_invite_friend(invite_guid, be_agree);

            if (be_agree)
            {
                var _msg = new agree_friend_msg
                {
                    be_invited_role_guid = _player.PlayerInfo.guid
                };
                var st = new MemoryStream();
                var _serializer = MessagePackSerializer.Get<invite_friend_msg>();
                _serializer.Pack(st, _msg);

                var _offline_msg = new offline_msg_mng.offline_msg()
                {
                    msg_guid = Guid.NewGuid().ToString("N"),
                    player_guid = invite_guid.ToString(),
                    send_timetmp = service.timerservice.Tick,
                    msg_type = "agree_friend_msg",
                    msg = st.ToArray(),
                };
                forward_offline_msg(_offline_msg);
            }
        }

        private void Client_Friend_Lobby_Module_on_invite_role_friend(player_friend_info self_info, player_friend_info target_info)
        {
            log.log.trace("on_invite_role_friend begin!");

            var uuid = hub.hub._gates.current_client_uuid;
            var _player = player.client_Mng.uuid_get_client_proxy(uuid);
            _player.invite(target_info);

            var _msg = new invite_friend_msg()
            {
                invite_role = self_info,
                target_role = target_info,
            };
            var st = new MemoryStream();
            var _serializer = MessagePackSerializer.Get<invite_friend_msg>();
            _serializer.Pack(st, _msg);

            var _offline_msg = new offline_msg_mng.offline_msg()
            {
                msg_guid = Guid.NewGuid().ToString("N"),
                player_guid = target_info.guid.ToString(),
                send_timetmp = service.timerservice.Tick,
                msg_type = "invite_friend_msg",
                msg = st.ToArray(),
            };
            forward_offline_msg(_offline_msg);
        }

        private async void forward_offline_msg(offline_msg_mng.offline_msg _offline_msg)
        {
            if (await player.offline_Msg_Mng.send_offline_msg(_offline_msg))
            {
                var player_guid = long.Parse(_offline_msg.player_guid);
                var player_svr_key = redis_help.BuildPlayerGuidCacheKey(player_guid);
                string player_hub_name = await player._redis_handle.GetStrData(player_svr_key);
                if (player_hub_name != hub.hub.name)
                {
                    var player_proxy = player.player_Proxy_Mng.get_player_proxy(player_hub_name);
                    player_proxy.player_have_offline_msg(player_guid);
                }
                else
                {
                    var target_role = player.client_Mng.guid_get_client_proxy(player_guid);
                    if (target_role != null)
                    {
                        await player.offline_Msg_Mng.process_offline_msg(_offline_msg.player_guid);
                    }
                }
            }
        }

        private void Client_Friend_Lobby_Module_on_find_role(long guid)
        {
            log.log.trace("on_find_role begin!");

            var rsp = client_Friend_Lobby_Module.rsp as client_friend_lobby_find_role_rsp;

            try
            {
                var _query = new DBQueryHelper();
                _query.condition("guid", guid);

                client_mng.GetPlayerCollection.getObjectInfo(_query.query(), (player_info_list) => { 
                    if (player_info_list.Count == 1)
                    {
                        var player_info_bson = player_info_list[0];
                        var player_info = BsonSerializer.Deserialize<player_info>(player_info_bson as BsonDocument);

                        var info = new player_friend_info()
                        {
                            guid = player_info.guid,
                            name = player_info.name,
                            coin = player_info.coin,
                            score = player_info.score
                        };
                        rsp.rsp(info);
                    }
                    else if (player_info_list.Count == 0)
                    {
                        rsp.err((int)error.unregistered_palyer);
                    }
                    else if (player_info_list.Count > 1)
                    {
                        rsp.err((int)error.db_error);
                    }
                
                }, () => { });
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private async void Client_Room_Player_Module_on_agree_join_room(string room_id)
        {
            log.log.trace("on_agree_join_room begin!");

            var rsp = client_Room_Player_Module.rsp as client_room_player_agree_join_room_rsp;
            var uuid = hub.hub._gates.current_client_uuid;

            try
            {
                var _player = player.client_Mng.uuid_get_client_proxy(uuid);

                var _room_key = redis_help.BuildRoomSvrNameCacheKey(room_id);
                var _room_hub_name = await player._redis_handle.GetStrData(_room_key);
                var _room_proxy = player.room_Proxy_Mng.get_room(_room_hub_name);

                if (_room_proxy != null)
                {
                    _room_proxy.agree_join_room(room_id, _player.PlayerInlineInfo).callBack((info) =>
                    {
                        rsp.rsp(_room_hub_name, info);

                        _player.RoomID = room_id;

                        var key = redis_help.BuildPlayerRoomCacheKey(_player.PlayerInfo.sdk_uuid);
                        player._redis_handle.SetStrData(key, _room_proxy.name);

                    }, (err) =>
                    {
                        rsp.err(err);

                    }).timeout(1000, () =>
                    {
                        rsp.err((int)error.timeout);
                    });
                }
                else
                {
                    rsp.err((int)error.room_is_destroy);
                }
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
                rsp.err((int)error.db_error);
            }
        }

        private async void Client_Room_Player_Module_on_invite_role_join_room(string sdk_uuid)
        {
            log.log.trace("on_invite_role_join_room begin!");

            var uuid = hub.hub._gates.current_client_uuid;

            try
            {
                var _player = player.client_Mng.uuid_get_client_proxy(uuid);

                var player_key = redis_help.BuildPlayerSvrCacheKey(sdk_uuid);
                var _player_proxy_name = await player._redis_handle.GetStrData(player_key);
                var _player_hub_proxy = player.player_Proxy_Mng.get_player_proxy(_player_proxy_name);

                _player_hub_proxy.invite_role_join_room(sdk_uuid, _player.RoomID, _player.PlayerInfo.name);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Client_Room_Player_Module_on_create_room()
        {
            log.log.trace("on_create_room begin!");

            var rsp = client_Room_Player_Module.rsp as client_room_player_create_room_rsp;
            var uuid = hub.hub._gates.current_client_uuid;

            try
            {
                var _player_proxy = player.client_Mng.uuid_get_client_proxy(uuid);
                var _room_proxy = player.room_Proxy_Mng.random_room();

                var key = redis_help.BuildPlayerRoomCacheKey(_player_proxy.PlayerInfo.sdk_uuid);
                player._redis_handle.SetStrData(key, _room_proxy.name);

                _room_proxy.create_room(_player_proxy.PlayerInlineInfo).callBack((_room_info) => {
                    rsp.rsp(_room_proxy.name, _room_info);
                    
                    _player_proxy.RoomID = _room_info.room_uuid;

                }, (err) => {
                    rsp.err(err);
                }).timeout(1000, () => {
                    rsp.err((int)error.timeout);
                });
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Client_match_Module_on_start_match()
        {
            log.log.trace("on_start_match begin!");

            var uuid = hub.hub._gates.current_client_uuid;

            try
            {
                var _proxy = player.client_Mng.uuid_get_client_proxy(uuid);
                player.match_Proxy_Mng.random_match().player_join_match(_proxy.PlayerInlineInfo);
            }
            catch (GetPlayerException ex)
            {
                log.log.err(ex.ErrorInfo);
                hub.hub._gates.disconnect_client(uuid);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Player_login_Module_on_create_role(string name)
        {
            log.log.trace("on_player_login begin!");

            var rsp = player_login_Module.rsp as player_login_create_role_rsp;
            var uuid = hub.hub._gates.current_client_uuid;

            try
            {
                var _proxy = player.client_Mng.create_player(uuid, name);
                rsp.rsp(_proxy.PlayerInfo);
            }
            catch (LoginException ex)
            {
                log.log.err(ex.ErrorInfo);
                hub.hub._gates.disconnect_client(uuid);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private async void Login_Player_Module_on_player_login(string token)
        {
            log.log.trace("on_player_login begin!");

            var rsp = player_login_Module.rsp as player_login_player_login_rsp;
            var uuid = hub.hub._gates.current_client_uuid;

            try
            {
                var _proxy = player.client_Mng.token_get_client_proxy(uuid, token);
                if (_proxy != null && _proxy.PlayerInfo != null)
                {
                    rsp.rsp(_proxy.PlayerInfo);

                    var room_key = redis_help.BuildPlayerRoomCacheKey(_proxy.PlayerInfo.sdk_uuid);
                    var room_hub_name = await player._redis_handle.GetStrData(room_key);
                    if (!string.IsNullOrEmpty(room_hub_name))
                    {
                        client_mng.PlayerGameClientCaller.get_client(_proxy.uuid).room_svr(room_hub_name);
                    }

                    var game_key = redis_help.BuildPlayerGameCacheKey(_proxy.PlayerInfo.guid);
                    var game_hub_name = await player._redis_handle.GetStrData(game_key);
                    if (!string.IsNullOrEmpty(game_hub_name))
                    {
                        client_mng.PlayerGameClientCaller.get_client(_proxy.uuid).game_svr(game_hub_name);
                    }

                    await player.offline_Msg_Mng.process_offline_msg(_proxy.PlayerInfo.guid.ToString());
                }
                else
                {
                    rsp.err((int)error.unregistered_palyer);
                }
            }
            catch (LoginException ex)
            {
                log.log.err(ex.ErrorInfo);
                hub.hub._gates.disconnect_client(uuid);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }
    }
}
