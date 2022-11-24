using abelkhan;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace match
{
    public class room_proxy
    {
        private readonly match_room_caller _match_room_caller;
        private readonly hub.hubproxy _proxy;

        public string name
        {
            get
            {
                return _proxy.name;
            }
        }

        public room_proxy(match_room_caller caller, hub.hubproxy proxy)
        {
            _match_room_caller = caller;
            _proxy = proxy;
        }

        public void start_game(string room_uuid, string game_hub_name)
        {
            _match_room_caller.get_hub(_proxy.name).start_game(room_uuid, game_hub_name);
        }
    }

    public class room_proxy_mng
    {
        private readonly match_room_caller _match_room_caller = new ();
        private readonly Dictionary<string, room_proxy> room_proxys = new ();

        public room_proxy_mng()
        {
        }

        public void reg_room_proxy(hub.hubproxy _proxy)
        {
            room_proxys[_proxy.name] = new room_proxy(_match_room_caller, _proxy);
        }

        public room_proxy get_room(string room_hub_name)
        {
            room_proxys.TryGetValue(room_hub_name, out room_proxy proxy);
            return proxy;
        }
    }
}
