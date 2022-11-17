

using System;

namespace abelkhan
{
    public class redis_help
    {
        static public string BuildPlayerSvrCacheKey(string sdk_uuid)
        {
            return string.Format("Player:PlayerCache:{0}", sdk_uuid);
        }

        static public string BuildPlayerGameCacheKey(Int64 guid)
        {
            return string.Format("Player:GameCache:{0}", guid);
        }
    }
}
