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
            match_Room_Module.on_room_match_join_room += Match_Room_Module_on_room_match_join_room;
            match_Room_Module.on_room_match_join_room_release += Match_Room_Module_on_room_match_join_room_release;
            match_Room_Module.on_player_join_room += Match_Room_Module_on_player_join_room;
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

        private void Match_Room_Module_on_player_join_room(string target_room_uuid, player_inline_info info)
        {
            log.log.trace("on_player_join_room begin!");

            try
            {
                var _room = room._room_mng.join_room(target_room_uuid, info);
                _room.refresh_room_info();
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Match_Room_Module_on_room_match_join_room_release(string room_uuid)
        {
            log.log.trace("on_room_match_join_room_release begin!");

            try
            {
                room._room_mng.room_match_join_room_release(room_uuid);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Match_Room_Module_on_room_match_join_room(string target_room_uuid, room_info info)
        {
            log.log.trace("on_room_match_join_room begin!");

            try
            {
                room._room_mng.room_join_room(target_room_uuid, info);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }


    }
}
