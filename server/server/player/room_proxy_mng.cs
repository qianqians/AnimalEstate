using abelkhan;
using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;

namespace player
{
    class room_proxy
    {
        private readonly player_room_caller player_Room_Caller;
        private readonly hub.hubproxy _proxy;

        public string name
        {
            get { return _proxy.name; }
        }

        public room_proxy(player_room_caller caller, hub.hubproxy proxy)
        {
            player_Room_Caller = caller;
            _proxy = proxy;
        }

        public player_room_create_room_cb create_room(playground _playground, player_inline_info room_owner)
        {
            return player_Room_Caller.get_hub(name).create_room(_playground, room_owner);
        }

        public player_room_agree_join_room_cb agree_join_room(string room_id, player_inline_info member)
        {
            return player_Room_Caller.get_hub(name).agree_join_room(room_id, member);
        }
    }

    class room_proxy_mng
    {
        private readonly player_room_caller _player_room_caller = new();
        private readonly List<room_proxy> room_proxys = new();
        private readonly Dictionary<string, room_proxy> room_proxys_dict = new();

        public void reg_room_proxy(hub.hubproxy _proxy)
        {
            var _room = new room_proxy(_player_room_caller, _proxy);
            room_proxys.Add(_room);
            room_proxys_dict.Add(_proxy.name, _room);
        }

        public room_proxy random_room()
        {
            uint count = (uint)room_proxys.Count;
            return room_proxys[(int)hub.hub.randmon_uint(count)];
        }

        public room_proxy get_room(string room_hub_name)
        {
            room_proxys_dict.TryGetValue(room_hub_name, out room_proxy room_proxy);
            return room_proxy;
        }
    }
}
