using abelkhan;
using System;
using System.Threading;

namespace player
{
    class player
    {
        public static string guid_key;
        public static redis_handle _redis_handle;
        public static readonly client_mng client_Mng = new ();

		static void Main(string[] args)
		{
            var _hub = new hub.hub(args[0], args[1], "player");
            guid_key = hub.hub._config.get_value_string("guid_key");
            _redis_handle = new redis_handle(hub.hub._root_config.get_value_string("redis_for_cache"));

            log.log.trace("player start ok");

            _hub.run();

            log.log.info("server closed, player server:{0}", hub.hub.name);
        }
	}
}
