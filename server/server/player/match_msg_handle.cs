using abelkhan;
using Newtonsoft.Json.Linq;
using System;
using System.Threading;

namespace player
{
    class match_msg_handle
    {
        private readonly match_player_module match_player_Module;

        public match_msg_handle()
        {
            match_player_Module = new ();

            match_player_Module.on_player_join_game += Match_player_Module_on_player_join_game;
        }

        private void Match_player_Module_on_player_join_game(long player_guid, string game_hub_name)
        {
            log.log.trace("on_player_join_room begin!");

            try
            {
                var _proxy = player.client_Mng.guid_get_client_proxy(player_guid);
                client_mng.PlayerGameClientCaller.get_client(_proxy.uuid).game_svr(game_hub_name);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }
    }
}
