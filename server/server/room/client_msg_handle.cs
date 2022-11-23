using abelkhan;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Security.Principal;

namespace room
{
    class client_msg_handle
    {
        private client_room_match_module client_Room_Match_Module;

        public client_msg_handle()
        {
            client_Room_Match_Module = new ();

            client_Room_Match_Module.on_into_room += Client_Room_Match_Module_on_into_room;
            client_Room_Match_Module.on_chat += Client_Room_Match_Module_on_chat;
            client_Room_Match_Module.on_leave_room += Client_Room_Match_Module_on_leave_room;
            client_Room_Match_Module.on_kick_out += Client_Room_Match_Module_on_kick_out;
            client_Room_Match_Module.on_disband += Client_Room_Match_Module_on_disband;
            client_Room_Match_Module.on_start_match += Client_Room_Match_Module_on_start_match;
        }

        private void Client_Room_Match_Module_on_start_match()
        {
            log.log.trace("on_start_match begin!");

            var owner_player_uuid = hub.hub._gates.current_client_uuid;
            try
            {
                var _owner = room._room_mng.get_client_proxy(owner_player_uuid);
                if (_owner.RoomImpl.OwnerID != _owner.guid)
                {
                    log.log.err($"start_match but not owner guid:{_owner.guid}");
                    return;
                }
                room.match_Proxy_Mng.random_idle_match().room_join_match(_owner.RoomImpl.RoomInfo);
                _owner.RoomImpl.team_into_match();
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Client_Room_Match_Module_on_disband()
        {
            log.log.trace("on_disband begin!");

            var owner_player_uuid = hub.hub._gates.current_client_uuid;
            try
            {
                var _owner = room._room_mng.get_client_proxy(owner_player_uuid);
                if (_owner.RoomImpl.OwnerID != _owner.guid)
                {
                    log.log.err($"kick_out player but not owner guid:{_owner.guid}");
                    return;
                }
                room._room_mng.disband_room(_owner.RoomImpl.RoomID);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Client_Room_Match_Module_on_kick_out(long player_guid)
        {
            log.log.trace("on_kick_out begin!");

            var owner_player_uuid = hub.hub._gates.current_client_uuid;
            try
            {
                var _owner = room._room_mng.get_client_proxy(owner_player_uuid);
                if (_owner.RoomImpl.OwnerID != _owner.guid)
                {
                    log.log.err($"kick_out player but not owner guid:{_owner.guid}");
                    return;
                }

                _owner.RoomImpl.kick_out(player_guid);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Client_Room_Match_Module_on_leave_room()
        {
            log.log.trace("on_leave_room begin!");

            var leave_player_uuid = hub.hub._gates.current_client_uuid;
            try
            {
                room._room_mng.leave_room(leave_player_uuid);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Client_Room_Match_Module_on_chat(string chat_str)
        {
            log.log.trace("on_chat begin!");

            var chat_player_uuid = hub.hub._gates.current_client_uuid;
            try
            {
                var _client = room._room_mng.get_client_proxy(chat_player_uuid);
                _client.RoomImpl.chat(_client.guid, chat_str);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }

        private void Client_Room_Match_Module_on_into_room()
        {
            log.log.trace("on_into_room begin!");

            try
            {
                var player_uuid = hub.hub._gates.current_client_uuid;
                var _client = room._room_mng.get_client_proxy(player_uuid);
                room_mng.RoomClientCaller.get_multicast(new List<string> { player_uuid }).refresh_room_info(_client.RoomImpl.RoomInfo);
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
        }
    }
}
