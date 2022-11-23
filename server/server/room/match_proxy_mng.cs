using abelkhan;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace room
{
    public class match_proxy
    {
        private readonly room_match_caller _room_match_caller;
        private readonly hub.hubproxy _proxy;

        public string name
        {
            get
            {
                return _proxy.name;
            }
        }

        public match_proxy(room_match_caller caller, hub.hubproxy proxy)
        {
            _room_match_caller = caller;
            _proxy = proxy;
        }

        public void room_join_match(room_info info)
        {
            _room_match_caller.get_hub(_proxy.name).room_join_match(info);
        }
    }

    public class match_proxy_mng
    {
        private readonly room_match_caller _room_match_caller = new ();
        private readonly List<match_proxy> match_proxys = new ();

        public match_proxy_mng()
        {
        }

        public void reg_match_proxy(hub.hubproxy _proxy)
        {
            match_proxys.Add(new match_proxy(_room_match_caller, _proxy));
        }

        public match_proxy random_idle_match()
        {
            uint count = (uint)match_proxys.Count;
            return match_proxys[(int)hub.hub.randmon_uint(count)];
        }
    }
}
