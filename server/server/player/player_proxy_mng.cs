using abelkhan;
using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;

namespace player
{
    class player_proxy
    {
        private readonly player_player_room_caller player_Player_Room_Caller;
        private readonly player_player_offline_msg_caller player_Player_Offline_Msg_Caller;
        private readonly hub.hubproxy _proxy;

        public string name
        {
            get { return _proxy.name; }
        }

        public player_proxy(player_player_room_caller caller, player_player_offline_msg_caller offline_caller, hub.hubproxy proxy)
        {
            player_Player_Room_Caller = caller;
            player_Player_Offline_Msg_Caller = offline_caller;
            _proxy = proxy;
        }

        public void invite_role_join_room(string sdk_uuid, string room_id, string invite_role_name)
        {
            player_Player_Room_Caller.get_hub(name).invite_role_join_room(sdk_uuid, room_id, invite_role_name);
        }

        public void player_have_offline_msg(long guid)
        {
            player_Player_Offline_Msg_Caller.get_hub(name).player_have_offline_msg(guid);
        }
    }

    class player_proxy_mng
    {
        private readonly player_player_room_caller _player_player_room_caller = new();
        private readonly player_player_offline_msg_caller _player_offline_msg_caller = new();

        private readonly Dictionary<string, player_proxy> player_proxys = new();

        public void reg_player_proxy(hub.hubproxy _proxy)
        {
            player_proxys.Add(_proxy.name, new player_proxy(_player_player_room_caller, _player_offline_msg_caller, _proxy));
        }

        public player_proxy get_player_proxy(string player_hub_name)
        {
            player_proxys.TryGetValue(player_hub_name, out player_proxy proxy);
            return proxy;
        }
    }
}
