using abelkhan;
using System.Security.Cryptography;
using System.Security.Principal;

namespace room
{
    class player_msg_handle
    {
        private readonly player_room_module player_Room_Module = new ();

        public player_msg_handle()
        {
            player_Room_Module.on_create_room += Player_Room_Module_on_create_room;
            player_Room_Module.on_agree_join_room += Player_Room_Module_on_agree_join_room;
        }

        private void Player_Room_Module_on_agree_join_room(string room_id, player_inline_info member)
        {
            log.log.trace("on_agree_join_room begin!");

            var rsp = player_Room_Module.rsp as player_room_agree_join_room_rsp;
            try
            {
                var _room = room._room_mng.join_room(room_id, member);
                rsp.rsp(_room.RoomInfo);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
                rsp.err((int)error.db_error);
            }
        }

        private void Player_Room_Module_on_create_room(playground _playground, player_inline_info room_owner)
        {
            log.log.trace("on_create_room begin!");

            var rsp = player_Room_Module.rsp as player_room_create_room_rsp;
            try
            {
                var _room = room._room_mng.create_room(_playground, room_owner);
                rsp.rsp(_room.RoomInfo);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
                rsp.err((int)error.db_error);
            }
        }
    }
}
