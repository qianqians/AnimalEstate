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
            game_Module.on_play_order += Game_Module_on_play_order;
            game_Module.on_ready += Game_Module_on_ready;
            game_Module.on_use_skill += Game_Module_on_use_skill;
            game_Module.on_use_props += Game_Module_on_use_props;
            game_Module.on_throw_dice += Game_Module_on_throw_dice;
        }

        private void Game_Module_on_ready()
        {
            log.log.trace($"on_play_order begin!");

            var uuid = hub.hub._gates.current_client_uuid;
            var _client = game._game_mng.get_player(uuid);
            try
            {
                _client.set_ready();
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Game_Module_on_use_props(props _props_id, long _target_guid, short _target_animal_index)
        {
            log.log.trace($"on_use_props begin!");

            try
            {
                var uuid = hub.hub._gates.current_client_uuid;
                game._game_mng.player_use_props(uuid, _props_id, _target_guid, _target_animal_index);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Game_Module_on_play_order(System.Collections.Generic.List<animal_game_info> animal_info)
        {
            log.log.trace($"on_play_order begin!");

            var uuid = hub.hub._gates.current_client_uuid;
            var _client = game._game_mng.get_player(uuid);
            try
            {
                _client.set_animal_order(animal_info);
                _client.GameImpl.ntf_animal_order(_client.PlayerGameInfo.guid);
            }
            catch (SetAnimalOrderError)
            {
                _client?.ntf_error_code(error.animal_order_len_not_four);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
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

        private void Game_Module_on_use_skill(long _target_guid, short _target_animal_index)
        {
            log.log.trace($"on_use_skill begin!");

            try
            {
                var uuid = hub.hub._gates.current_client_uuid;
                game._game_mng.player_use_skill(uuid, _target_guid, _target_animal_index);
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
