using abelkhan;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace match
{
    public class player_proxy
    {
        private readonly match_player_caller _match_player_caller;
        private readonly hub.hubproxy _proxy;

        public string name
        {
            get
            {
                return _proxy.name;
            }
        }

        public player_proxy(match_player_caller caller, hub.hubproxy proxy)
        {
            _match_player_caller = caller;
            _proxy = proxy;
        }

        public void player_join_game(long player_guid, string game_hub_name)
        {
            _match_player_caller.get_hub(_proxy.name).player_join_game(player_guid, game_hub_name);
        }
    }

    public class player_proxy_mng
    {
        private readonly match_player_caller _match_player_caller = new ();
        private readonly Dictionary<string, player_proxy> player_proxys = new ();

        public player_proxy_mng()
        {
        }

        public void reg_player_proxy(hub.hubproxy _proxy)
        {
            player_proxys[_proxy.name] = new player_proxy(_match_player_caller, _proxy);
        }

        public player_proxy get_player(string player_hub_name)
        {
            player_proxys.TryGetValue(player_hub_name, out player_proxy proxy);
            return proxy;
        }
    }
}
