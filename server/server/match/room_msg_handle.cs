using abelkhan;
using System.Security.Cryptography;
using System.Security.Principal;

namespace match
{
    class room_msg_handle
    {
        private readonly room_match_module room_Match_Module = new ();

        public room_msg_handle()
        {
            room_Match_Module.on_room_join_match += Room_Match_Module_on_room_join_match;
        }

        private void Room_Match_Module_on_room_join_match(room_info info)
        {
            log.log.trace("on_room_join_match begin!");

            try
            {
                match.match_Mng.room_join_match(hub.hub._hubs.current_hubproxy.name, info);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }
    }
}
