using abelkhan;
using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;

namespace player
{
    class match_proxy
    {
        private readonly player_match_caller player_Match_Caller;
        private readonly hub.hubproxy _proxy;

        public string name
        {
            get { return _proxy.name; }
        }

        public match_proxy(player_match_caller caller, hub.hubproxy proxy)
        {
            player_Match_Caller = caller;
            _proxy = proxy;
        }

        public void player_join_match(playground _playground, player_inline_info info)
        {
            player_Match_Caller.get_hub(name).player_join_match(_playground, info);
        }
    }

    class match_proxy_mng
    {
        private readonly player_match_caller _player_match_caller = new();
        private readonly List<match_proxy> match_proxys = new();

        public void reg_match_proxy(hub.hubproxy _proxy)
        {
            match_proxys.Add(new match_proxy(_player_match_caller, _proxy));
        }

        public match_proxy random_match()
        {
            uint count = (uint)match_proxys.Count;
            return match_proxys[(int)hub.hub.randmon_uint(count)];
        }
    }
}
