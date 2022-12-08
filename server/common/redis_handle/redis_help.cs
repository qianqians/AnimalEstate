

using System;

namespace abelkhan
{
    public class redis_help
    {
        static public string BuildGameSvrInfoCacheKey(string game_hub_name)
        {
            return $"Svr:GameSvrInfoCache:{game_hub_name}";
        }

        static public string BuildPlayerSvrInfoCacheKey(string player_hub_name)
        {
            return $"Svr:PlayerSvrInfoCache:{player_hub_name}";
        }

        static public string BuildPlayerGateCacheKey(string sdk_uuid)
        {
            return $"Player:GateSDKUUIDCache:{sdk_uuid}";
        }

        static public string BuildPlayerSDKUUIDCacheKey(string uuid)
        {
            return $"Player:PlayerUUIDSDKUUIDCache:{uuid}";
        }

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

        static public string BuildPlayerRoomCacheKey(Int64 guid)
        {
            return $"Player:RoomCache:{guid}";
        }

        static public string BuildPlayerGameCacheLockKey(Int64 guid)
        {
            return $"Player:GameLockCache:{guid}";
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
