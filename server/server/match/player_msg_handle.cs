using abelkhan;
using System.Security.Cryptography;
using System.Security.Principal;

namespace match
{
    class player_msg_handle
    {
        private readonly player_match_module player_Match_Module = new ();

        public player_msg_handle()
        {
            player_Match_Module.on_player_join_match += Player_Match_Module_on_player_join_match;
        }

        private void Player_Match_Module_on_player_join_match(player_inline_info player_info)
        {
            log.log.trace("on_player_join_match begin!");

            try
            {
                match.match_Mng.player_join_match(hub.hub._hubs.current_hubproxy.name, player_info);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }
    }
}
