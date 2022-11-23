using abelkhan;

namespace room
{
    class room
    {
        public static redis_handle _redis_handle;
        public static room_mng _room_mng = new ();
        public static match_proxy_mng match_Proxy_Mng = new ();

        static void Main(string[] args)
		{
            var _hub = new hub.hub(args[0], args[1], "room");
            _redis_handle = new redis_handle(hub.hub._root_config.get_value_string("redis_for_cache"));

            var _client_msg_handle = new client_msg_handle();

            _hub.on_hubproxy += on_hubproxy;
            _hub.on_hubproxy_reconn += on_hubproxy;

            log.log.trace("room start ok");

            _hub.run();

            log.log.info("server closed, room server:{0}", hub.hub.name);
        }

        private static void on_hubproxy(hub.hubproxy _proxy)
        {
            if (_proxy.type == "match")
            {
                match_Proxy_Mng.reg_match_proxy(_proxy);
            }
        }
    }
}
