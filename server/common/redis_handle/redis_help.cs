

using System;

namespace abelkhan
{
    public class redis_help
    {
        static public string BuildPlayerSvrCacheKey(string sdk_uuid)
        {
            return $"Player:PlayerCache:{sdk_uuid}";
        }

        static public string BuildPlayerRoomCacheKey(string sdk_uuid)
        {
            return $"Player:RoomCache:{sdk_uuid}";
        }

        static public string BuildPlayerGameCacheKey(Int64 guid)
        {
            return $"Player:GameCache:{guid}";
        }

        static public string BuildRoomSvrNameCacheKey(string room_id)
        {
            return $"Room:RoomCache:{room_id}";
        }
    }
}
