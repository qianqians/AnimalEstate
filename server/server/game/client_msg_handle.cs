using abelkhan;
using System;
using System.Security.Cryptography;
using System.Security.Principal;

namespace game
{
    class client_msg_handle
    {
        private game_module game_Module = new ();

        public client_msg_handle()
        {
            game_Module.on_into_game += Game_Module_on_into_game;
            game_Module.on_use_skill += Game_Module_on_use_skill;
            game_Module.on_throw_dice += Game_Module_on_throw_dice;
        }

        private void Game_Module_on_throw_dice()
        {
            log.log.trace($"on_throw_dice begin!");

            try
            {
                var uuid = hub.hub._gates.current_client_uuid;
                game._game_mng.player_throw_dice(uuid);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Game_Module_on_use_skill()
        {
            log.log.trace($"on_use_skill begin!");

            try
            {
                var uuid = hub.hub._gates.current_client_uuid;
                game._game_mng.player_use_skill(uuid);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Game_Module_on_into_game(long guid)
        {
            log.log.trace($"on_into_game begin! guid:{guid}");

            try
            {
                var uuid = hub.hub._gates.current_client_uuid;
                game._game_mng.player_into_game(guid, uuid);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }
    }
}
