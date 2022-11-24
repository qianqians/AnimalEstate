

using System;

namespace abelkhan
{
    public class redis_help
    {
        static public string BuildPlayerSvrCacheLockKey(string sdk_uuid)
        {
            return $"Player:PlayerSDKUUIDLockCache:{sdk_uuid}";
        }

        static public string BuildPlayerSvrCacheKey(string sdk_uuid)
        {
            return $"Player:PlayerSDKUUIDCache:{sdk_uuid}";
        }

        static public string BuildPlayerGuidCacheKey(long guid)
        {
            return $"Player:PlayerGuidCache:{guid}";
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
