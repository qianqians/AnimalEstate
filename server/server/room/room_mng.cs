using abelkhan;
using Pipelines.Sockets.Unofficial.Buffers;
using StackExchange.Redis;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Threading.Tasks;
using static MongoDB.Bson.Serialization.Serializers.SerializerHelper;

namespace room
{
   public class client_proxy
    {
        private readonly player_inline_info player_inline_info;
        public player_inline_info PlayerInlineInfo
        {
            get
            {
                return player_inline_info;
            }
        }
        public string uuid
        {
            get
            {
                return player_inline_info.uuid;
            }
        }
        public long guid
        {
            get
            {
                return player_inline_info.guid;
            }
        }

        private readonly room_impl _room_impl;
        public room_impl RoomImpl
        {
            get
            {
                return _room_impl;
            }
        }

        public client_proxy(player_inline_info info, room_impl impl)
        {
            player_inline_info = info;
            _room_impl = impl;
        }
    }

    public class room_impl
    {
        private readonly string room_id = Guid.NewGuid().ToString();
        public string RoomID
        {
            get
            {
                return room_id;
            }
        }

        private client_proxy _owner;
        public long OwnerID
        {
            get
            {
                return _owner.guid;
            }
        }

        private readonly Dictionary<string, client_proxy> uuid_clients = new();
        public int Count
        {
            get
            {
                return uuid_clients.Count;
            }
        }
        public List<string> RoomClientUUIDList
        {
            get
            {
                return uuid_clients.Keys.ToList();
            }
        }

        private playground _playground = playground.random;
        public room_info RoomInfo
        {
            get
            {
                var info = new room_info();
                info.room_uuid = room_id;
                info.room_owner_guid = _owner.guid;
                info._playground = _playground;
                info.room_player_list = new ();
                foreach (var it in uuid_clients)
                {
                    info.room_player_list.Add(it.Value.PlayerInlineInfo);
                }

                return info;
            }
        }

        public void create_room(playground ground, client_proxy owner)
        {
            _playground = ground;
            _owner = owner;
            uuid_clients[owner.uuid] = owner;

            var room_key = redis_help.BuildRoomSvrNameCacheKey(room_id);
            room._redis_handle.SetStrData(room_key, hub.hub.name);
        }

        public void join_room(client_proxy _client)
        {
            uuid_clients[_client.uuid] = _client;
        }

        public void chat(long chat_player_guid, string chat_str)
        {
            room_mng.RoomClientCaller.get_multicast(RoomClientUUIDList).chat(chat_player_guid, chat_str);
        }

        public void leave_room(string leave_player_uuid)
        {
            uuid_clients.Remove(leave_player_uuid, out client_proxy _leave_player);
            if (uuid_clients.Count > 0 && _owner.uuid == leave_player_uuid)
            {
                _owner = uuid_clients.Values.First();
                room_mng.RoomClientCaller.get_multicast(RoomClientUUIDList).refresh_room_info(RoomInfo);
            }
            room_mng.RoomClientCaller.get_client(leave_player_uuid).player_leave_room_success();

            var player_room_key = redis_help.BuildPlayerRoomCacheKey(_leave_player.guid);
            room._redis_handle.DelData(player_room_key);
        }

        public void kick_out(long player_guid)
        {
            foreach (var _client in uuid_clients.Values)
            {
                if (_client.guid == player_guid)
                {
                    uuid_clients.Remove(_client.uuid);

                    room_mng.RoomClientCaller.get_multicast(RoomClientUUIDList).refresh_room_info(RoomInfo);
                    room_mng.RoomClientCaller.get_client(_client.uuid).be_kicked();

                    var player_room_key = redis_help.BuildPlayerRoomCacheKey(player_guid);
                    room._redis_handle.DelData(player_room_key);

                    return;
                }
            }
            log.log.info($"be kick out player not in room player_guid:{player_guid}");
        }

        public void disband()
        {
            foreach (var _client in uuid_clients.Values)
            {
                var player_room_key = redis_help.BuildPlayerRoomCacheKey(_client.guid);
                room._redis_handle.DelData(player_room_key);
            }

            room_mng.RoomClientCaller.get_multicast(RoomClientUUIDList).room_is_free();
            uuid_clients.Clear();
        }
        
        public void team_into_match()
        {
            room_mng.RoomClientCaller.get_multicast(RoomClientUUIDList).team_into_match();
        }

        public void refresh_room_info()
        {
            room_mng.RoomClientCaller.get_multicast(RoomClientUUIDList).refresh_room_info(RoomInfo);
        }

        public void role_into_game(string game_hub_name)
        {
            room_mng.RoomMatchClientCaller.get_multicast(RoomClientUUIDList).role_into_game(game_hub_name);
        }
    }

    public class room_mng
    {
        private readonly Dictionary<string, client_proxy> uuid_clients = new();
        private readonly Dictionary<string, room_impl> guid_room = new ();

        private static readonly room_client_caller room_Client_Caller = new();
        public static room_client_caller RoomClientCaller
        {
            get
            {
                return room_Client_Caller;
            }
        }

        private static readonly room_match_client_caller room_Match_Client_Caller = new ();
        public static room_match_client_caller RoomMatchClientCaller
        {
            get
            {
                return room_Match_Client_Caller;
            }
        }

        public room_impl create_room(playground _playground, player_inline_info room_owner)
        {
            var _room = new room_impl();
            var _client = new client_proxy(room_owner, _room);

            _room.create_room(_playground, _client);

            uuid_clients.Add(room_owner.uuid, _client);
            guid_room.Add(_room.RoomID, _room);

            return _room;
        }

        public room_impl join_room(string room_id, player_inline_info member)
        {
            if (guid_room.TryGetValue(room_id, out room_impl _room))
            {
                var _client = new client_proxy(member, _room);
                uuid_clients.Add(member.uuid, _client);

                _room.join_room(_client);
            }
            return _room;
        }

        public client_proxy get_client_proxy(string client_uuid)
        {
            uuid_clients.TryGetValue(client_uuid, out client_proxy _proxy);
            return _proxy;
        }

        private void del_room_cache(string room_id)
        {
            var room_key = redis_help.BuildRoomSvrNameCacheKey(room_id);
            room._redis_handle.DelData(room_key);
        }

        public void leave_room(string leave_player_uuid)
        {
            if (uuid_clients.Remove(leave_player_uuid, out client_proxy _client))
            {
                _client.RoomImpl.leave_room(leave_player_uuid);
                if (_client.RoomImpl.Count <= 0)
                {
                    guid_room.Remove(_client.RoomImpl.RoomID);
                    del_room_cache(_client.RoomImpl.RoomID);
                }
            }
        }

        public void disband_room(string room_id)
        {
            if (guid_room.Remove(room_id, out room_impl _room))
            {
                _room.disband();
                del_room_cache(room_id);
            }
        }

        public room_impl get_room(string room_uuid)
        {
            guid_room.TryGetValue(room_uuid, out room_impl _room);
            return _room;
        }
    }

}
