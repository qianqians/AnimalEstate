﻿using abelkhan;
using System.Numerics;

namespace game
{
    class game
    {
        public static redis_handle _redis_handle;
        public static player_proxy_mng _player_proxy_mng = new ();
        public static game_mng _game_mng = new ();

        static void Main(string[] args)
		{
            var _hub = new hub.hub(args[0], args[1], "login");
            _redis_handle = new redis_handle(hub.hub._root_config.get_value_string("redis_for_cache"));

            var _client_msg_handle = new client_msg_handle();
            var _match_msg_handle = new match_msg_handle();

            _hub.on_hubproxy += on_hubproxy;
            _hub.on_hubproxy_reconn += on_hubproxy;

            _hub.onCloseServer += () => {
                _hub.closeSvr();
            };

            hub.hub._timer.addticktime(300000, tick_set_game_svr_info);

            log.log.trace("login start ok");

            _hub.run();

            log.log.info("server closed, login server:{0}", hub.hub.name);
        }

        private static void tick_set_game_svr_info(long tick_time)
        {
            game._redis_handle.SetData(redis_help.BuildGameSvrInfoCacheKey(hub.hub.name), new svr_info { tick_time = (int)hub.hub.tick, player_num = _game_mng.Count });

            hub.hub._timer.addticktime(300000, tick_set_game_svr_info);
        }

        private static void on_hubproxy(hub.hubproxy _proxy)
        {
            if (_proxy.type == "player")
            {
                _player_proxy_mng.reg_player_proxy(_proxy);
            }
        }
    }
}