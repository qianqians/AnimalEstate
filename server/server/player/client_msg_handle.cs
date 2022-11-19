using abelkhan;
using Newtonsoft.Json.Linq;
using System;
using System.Security.Cryptography;
using System.Threading;
using System.Xml.Linq;

namespace player
{
    class client_msg_handle
    {
        private readonly player_login_module player_login_Module;
        private readonly client_match_module client_match_Module;

        public client_msg_handle()
        {
            player_login_Module = new ();
            player_login_Module.on_player_login += Login_Player_Module_on_player_login;
            player_login_Module.on_create_role += Player_login_Module_on_create_role;

            client_match_Module = new ();
            client_match_Module.on_start_match += Client_match_Module_on_start_match;
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

        private void Login_Player_Module_on_player_login(string token)
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
