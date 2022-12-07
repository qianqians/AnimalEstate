using abelkhan;
using log;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace match
{
    public class game_proxy
    {
        private readonly match_game_caller _match_game_caller;
        private readonly hub.hubproxy _proxy;

        public string name
        {
            get
            {
                return _proxy.name;
            }
        }

        public game_proxy(match_game_caller caller, hub.hubproxy proxy)
        {
            _match_game_caller = caller;
            _proxy = proxy;
        }

        public match_game_start_game_cb start_game(playground _playground, List<player_inline_info> room_player_list)
        {
            return _match_game_caller.get_hub(_proxy.name).start_game(_playground, room_player_list);
        }
    }

    public class game_proxy_mng
    {
        private readonly match_game_caller _match_game_caller = new ();
        private readonly Dictionary<string, game_proxy> game_proxys = new ();

        public game_proxy_mng()
        {
        }

        public void reg_game_proxy(hub.hubproxy _proxy)
        {
            game_proxys[_proxy.name] = new game_proxy(_match_game_caller, _proxy);
        }

        public async Task<List<game_proxy> > get_idle_game()
        {
            var idle_game_proxys = new List<game_proxy>();
            foreach (var p in game_proxys)
            {
                var info = await match._redis_handle.GetData<svr_info>(redis_help.BuildGameSvrInfoCacheKey(p.Key));
                if (info?.tick_time < 34)
                {
                    idle_game_proxys.Add(p.Value);
                }
            }

            return idle_game_proxys;
        }
    }
}
