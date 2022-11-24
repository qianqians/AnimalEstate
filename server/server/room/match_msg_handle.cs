using abelkhan;
using System.Security.Cryptography;
using System.Security.Principal;
using static MongoDB.Bson.Serialization.Serializers.SerializerHelper;

namespace room
{
    class match_msg_handle
    {
        private readonly match_room_module match_Room_Module = new ();

        public match_msg_handle()
        {
            match_Room_Module.on_start_game += Match_Room_Module_on_start_game;
        }

        private void Match_Room_Module_on_start_game(string room_uuid, string game_hub_name)
        {
            log.log.trace("on_start_game begin!");

            try
            {
                var _room = room._room_mng.get_room(room_uuid);
                _room.role_into_game(game_hub_name);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }
    }
}
