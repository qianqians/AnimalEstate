using abelkhan;
using log;
using offline_msg;
using service;
using System;
using System.Threading;

namespace player
{
    class player
    {
        public static string guid_key;
        public static redis_handle _redis_handle;

        public static readonly client_mng client_Mng = new ();

        public static readonly match_proxy_mng match_Proxy_Mng = new ();
        public static readonly room_proxy_mng room_Proxy_Mng = new ();
        public static readonly player_proxy_mng player_Proxy_Mng = new ();

        public static offline_msg_mng offline_Msg_Mng = new (constant.constant.player_db_name, constant.constant.player_db_offline_msg_collection);

		static void Main(string[] args)
		{
            var _hub = new hub.hub(args[0], args[1], "player");
            guid_key = hub.hub._config.get_value_string("guid_key");
            _redis_handle = new redis_handle(hub.hub._root_config.get_value_string("redis_for_cache"));

            var _client_msg_handle = new client_msg_handle();
            var _login_msg_handle = new login_msg_handle();
            var _match_msg_handle = new match_msg_handle();
            var _player_msg_handle = new player_msg_handle();
            var _game_msg_handle = new game_msg_handle();

            _hub.on_hubproxy += on_hubproxy;
            _hub.on_hubproxy_reconn += on_hubproxy;

            _hub.on_client_msg += (uuid) =>
            {
                try
                {
                    var _client = client_Mng.uuid_get_client_proxy(uuid);
                    _client.LastActiveTime = timerservice.Tick;
                }
                catch (System.Exception ex)
                {
                    log.log.err($"{ex}");
                }
            };

            hub.hub._timer.addticktime(300000, tick_set_player_svr_info);

            log.log.trace("player start ok");

            _hub.run();

            log.log.info("server closed, player server:{0}", hub.hub.name);
        }

        private static void tick_set_player_svr_info(long tick_time)
        {
            player._redis_handle.SetData(redis_help.BuildPlayerSvrInfoCacheKey(hub.hub.name), new svr_info { tick_time = (int)hub.hub.tick, player_num = client_Mng.Count });

            hub.hub._timer.addticktime(300000, tick_set_player_svr_info);
        }

        private static void on_hubproxy(hub.hubproxy _proxy)
        {
            if (_proxy.type == "match")
            {
                match_Proxy_Mng.reg_match_proxy(_proxy);
            }
            else if (_proxy.type == "room")
            {
                room_Proxy_Mng.reg_room_proxy(_proxy);
            }
            else if (_proxy.type == "player")
            {
                player_Proxy_Mng.reg_player_proxy(_proxy);
            }
        }
    }
}
