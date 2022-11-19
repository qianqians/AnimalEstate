using abelkhan;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace login
{
    public class player_proxy
    {
        private readonly abelkhan.login_player_caller _login_player_caller;
        private readonly hub.hubproxy _proxy;

        public string name
        {
            get
            {
                return _proxy.name;
            }
        }

        public player_proxy(abelkhan.login_player_caller caller, hub.hubproxy proxy)
        {
            _login_player_caller = caller;
            _proxy = proxy;
        }

        public login_player_player_login_cb player_login(string sdk_uuid)
        {
            return _login_player_caller.get_hub(_proxy.name).player_login(sdk_uuid);
        }
    }

    public class player_proxy_mng
    {
        private readonly login_player_caller _login_player_caller = new ();
        private readonly Dictionary<string, player_proxy> player_proxys = new ();

        public player_proxy_mng()
        {
        }

        public void reg_player_proxy(hub.hubproxy _proxy)
        {
            player_proxys[_proxy.name] = new player_proxy(_login_player_caller, _proxy);
        }

        public player_proxy get_player(string player_hub_name)
        {
            player_proxys.TryGetValue(player_hub_name, out player_proxy proxy);
            return proxy;
        }

        public async Task<player_proxy> random_idle_player()
        {
            var idle_player_proxys = new List<player_proxy>();
            foreach (var p in player_proxys)
            {
                var info = await login._redis_handle.GetData<player_svr_info>(p.Key);
                if (info.tick_time < 34)
                {
                    idle_player_proxys.Add(p.Value);
                }
            }

            if (idle_player_proxys.Count > 0)
            {
                uint count = (uint)idle_player_proxys.Count;
                return idle_player_proxys[(int)hub.hub.randmon_uint(count)];
            }

            return null; 
        }
    }
}
