using abelkhan;
using Newtonsoft.Json.Linq;
using System;
using System.Threading;

namespace player
{
    class player_msg_handle
    {
        private readonly player_player_room_module player_Player_Room_Module;
        private readonly player_player_offline_msg_module player_offline_msg_Module;

        public player_msg_handle()
        {
            player_Player_Room_Module = new ();
            player_Player_Room_Module.on_invite_role_join_room += Player_Player_Room_Module_on_invite_role_join_room;

            player_offline_msg_Module = new ();
            player_offline_msg_Module.on_player_have_offline_msg += Player_offline_msg_Module_on_player_have_offline_msg;
        }

        private async void Player_offline_msg_Module_on_player_have_offline_msg(long guid)
        {
            log.log.trace("on_player_have_offline_msg begin!");

            try
            {
                await player.offline_Msg_Mng.process_offline_msg(guid.ToString());
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private async void Player_Player_Room_Module_on_invite_role_join_room(string sdk_uuid, string room_id, string invite_role_name)
        {
            log.log.err("on_invite_role_join_room begin!");

            try
            {
                var _player_proxy = await player.client_Mng.sdk_uuid_get_client_proxy(sdk_uuid);
                client_mng.PlayerRoomClientCaller.get_client(_player_proxy.uuid).invite_role_join_room(room_id, invite_role_name);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }
    }
}
