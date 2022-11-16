using System;
using System.Threading;

namespace login
{
    class Program
    {


		static void Main(string[] args)
		{
            var _hub = new hub.hub(args[0], args[1], "login");

            log.log.trace("player start ok");

            _hub.run();

            log.log.info("server closed, player server:{0}", hub.hub.name);
        }
	}
}
