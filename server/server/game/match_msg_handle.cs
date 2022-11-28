using abelkhan;
using System.Collections.Generic;

namespace game
{
    class match_msg_handle
    {
        private match_game_module match_Game_Module = new ();

        public match_msg_handle()
        {
            match_Game_Module.on_start_game += Match_Game_Module_on_start_game;
        }

        private void Match_Game_Module_on_start_game(playground _playground, List<player_inline_info> room_player_list)
        {
            log.log.trace("on_start_game begin!");

            var rsp = match_Game_Module.rsp as match_game_start_game_rsp;

            try
            {
                if (hub.hub.tick > 500)
                {
                    rsp.err((int)error.server_busy);
                }
                else
                {
                    game._game_mng.create_game(_playground, room_player_list);
                    rsp.rsp();
                }
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
                rsp.err((int)error.db_error);
            }
        }
    }
}
