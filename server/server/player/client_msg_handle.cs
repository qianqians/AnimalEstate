using abelkhan;
using log;
using Newtonsoft.Json.Linq;
using System;
using System.Security.Cryptography;
using System.Security.Principal;
using System.Threading;
using System.Xml.Linq;

namespace player
{
    class client_msg_handle
    {
        private readonly player_login_module player_login_Module;
        private readonly client_match_module client_match_Module;
        private readonly client_room_player_module client_Room_Player_Module;

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
                if (_proxy != null)
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
