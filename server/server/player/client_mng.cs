using abelkhan;
using hub;
using MongoDB.Bson;
using MongoDB.Bson.Serialization;
using Newtonsoft.Json.Linq;
using StackExchange.Redis;
using System;
using System.Collections.Generic;
using System.Security.Principal;
using System.Threading;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace player
{
    public class LoginException : System.Exception
    {
        public string ErrorInfo;
        public LoginException(string err) : base(err)
        {
            ErrorInfo = err;
        }
    }

    public class GetPlayerException : System.Exception
    {
        public string ErrorInfo;
        public GetPlayerException(string err) : base(err)
        {
            ErrorInfo = err;
        }
    }

    public class GetGuidFromDBError : System.Exception
    {
        public string error;

        public GetGuidFromDBError(string err) : base(err)
        {
            error = err;
        }
    }

    public class client_proxy
    {
        private readonly string _sdk_uuid;

        private string _uuid;
        public string uuid
        {
            set
            {
                _uuid = value;
            }
            get
            {
                return _uuid;
            }
        }

        private player_info _info;
        public player_info PlayerInfo
        {
            get
            {
                return _info;
            }
        }

        public player_inline_info PlayerInlineInfo
        {
            get
            {
                var info = new player_inline_info();
                info.uuid = _uuid;
                info.name = _info.name;
                info.guid = _info.guid;
                info.coin = _info.coin;
                info.score = _info.score;
                return info;
            }
        }

        private string room_id;
        public string RoomID
        {
            set
            {
                room_id = value;
            }
            get
            {
                return room_id;
            }
        }

        private dbproxyproxy.Collection GuidCollection
        {
            get { return hub.hub.get_random_dbproxyproxy().getCollection(constant.constant.player_db_name, constant.constant.player_db_guid_collection); }
        }

        private string bind_db_proxy_name = null;
        public dbproxyproxy.Collection PlayerCollection
        {
            get
            {
                dbproxyproxy bind_db_proxy;
                do
                {
                    if (string.IsNullOrEmpty(bind_db_proxy_name))
                    {
                        bind_db_proxy = hub.hub.get_random_dbproxyproxy();
                        bind_db_proxy_name = bind_db_proxy.db_name;
                        break;
                    }

                    bind_db_proxy = hub.hub.get_dbproxy(bind_db_proxy_name);
                    if (bind_db_proxy == null)
                    {
                        bind_db_proxy = hub.hub.get_random_dbproxyproxy();
                        bind_db_proxy_name = bind_db_proxy.db_name;
                    }

                } while (false);

                return bind_db_proxy.getCollection(constant.constant.player_db_name, constant.constant.player_db_collection);
            }
        }

        private Task<long> get_guid()
        {
            var task = new TaskCompletionSource<long>();

            GuidCollection.getGuid(player.guid_key, (_ret, guid) =>
            {
                if (_ret != dbproxyproxy.EM_DB_RESULT.EM_DB_SUCESSED)
                {
                    var err = string.Format("getGuid error:{0}!", _ret);
                    log.log.err(err);
                    task.SetException(new GetGuidFromDBError(err));
                }
                else
                {
                    task.SetResult(guid);
                }
            });

            return task.Task;
        }

        public client_proxy(string sdk_uuid, player_info info = null)
        {
            _sdk_uuid = sdk_uuid;
            _info = info;
        }

        public async void create_player(string name)
        {
            _info = new player_info
            {
                sdk_uuid = _sdk_uuid,
                name = name,
                guid = await get_guid(),
                coin = 100,
                score = 0
            };

            PlayerCollection.createPersistedObject(_info.ToBsonDocument(), (ret) => {
                if (ret != dbproxyproxy.EM_DB_RESULT.EM_DB_SUCESSED)
                {
                    log.log.err($"createPersistedObject error, player sdk_uuid:{_sdk_uuid}, name:{name}, err:{ret}");
                }
            });
        }
    }

    public class client_mng
    {
        private readonly Dictionary<string, client_proxy> client_token_dict = new ();
        private readonly Dictionary<string, client_proxy> client_uuid_dict = new ();
        private readonly Dictionary<string, client_proxy> client_sdk_uuid_dict = new();
        private readonly Dictionary<long, client_proxy> client_guid_dict = new ();

        private dbproxyproxy.Collection GetPlayerCollection
        {
            get { return hub.hub.get_random_dbproxyproxy().getCollection(constant.constant.player_db_name, constant.constant.player_db_collection); }
        }

        private static readonly player_client_caller player_Client_Caller = new();
        public static player_client_caller PlayerClientCaller
        {
            get
            {
                return player_Client_Caller;
            }
        }

        private static readonly player_game_client_caller player_Game_Client_Caller = new ();
        public static player_game_client_caller PlayerGameClientCaller
        {
            get
            {
                return player_Game_Client_Caller;
            }
        }

        private static readonly player_room_client_caller player_Room_Client_Caller = new ();
        public static player_room_client_caller PlayerRoomClientCaller
        {
            get
            {
                return player_Room_Client_Caller;
            }
        }

        public Task<string> token_player_login(string sdk_uuid)
        {
            var ret = new TaskCompletionSource<string>();

            do
            {
                if (client_sdk_uuid_dict.TryGetValue(sdk_uuid, out client_proxy _proxy))
                {
                    var token = Guid.NewGuid().ToString();
                    PlayerClientCaller.get_client(_proxy.uuid).be_displacement();
                    ret.SetResult(token);
                    break;
                }

                DBQueryHelper query = new();
                query.condition("sdk_uuid", sdk_uuid);
                GetPlayerCollection.getObjectInfo(query.query(), (player_info_list) =>
                {
                    if (player_info_list.Count > 1)
                    {
                        log.log.err($"duplicate sdk_uuid:{sdk_uuid}");
                        ret.SetException(new LoginException($"duplicate sdk_uuid:{sdk_uuid}"));
                    }
                    else
                    {
                        client_proxy _proxy = null;
                        var token = Guid.NewGuid().ToString();

                        if (player_info_list.Count == 0)
                        {
                            _proxy = new client_proxy(sdk_uuid);
                        }
                        else if (player_info_list.Count == 1)
                        {
                            var info = player_info_list[0];
                            var _player_info_db = BsonSerializer.Deserialize<player_info>(info as BsonDocument);
                            _proxy = new client_proxy(sdk_uuid, _player_info_db);
                            client_guid_dict.Add(_proxy.PlayerInfo.guid, _proxy);
                        }
                        client_token_dict.Add(token, _proxy);
                        client_sdk_uuid_dict.Add(sdk_uuid, _proxy);

                        ret.SetResult(token);
                    }
                }, () => { });

            } while (false);
            
            return ret.Task;
        }

        public client_proxy token_get_client_proxy(string uuid, string token)
        {
            if (!client_token_dict.Remove(token, out client_proxy _proxy))
            {
                throw new LoginException($"invaild token:{token}");
            }
            _proxy.uuid = uuid;
            client_uuid_dict[uuid] = _proxy;
            return _proxy;
        }

        public client_proxy create_player(string uuid, string name)
        {
            if (!client_uuid_dict.TryGetValue(uuid, out client_proxy _proxy))
            {
                throw new LoginException($"invaild uuid:{uuid}");
            }

            _proxy.create_player(name);
            client_guid_dict.Add(_proxy.PlayerInfo.guid, _proxy);

            return _proxy;
        }

        public client_proxy uuid_get_client_proxy(string uuid)
        {
            if (!client_uuid_dict.TryGetValue(uuid, out client_proxy _proxy))
            {
                throw new GetPlayerException($"invaild uuid:{uuid}");
            }
            return _proxy;
        }

        public client_proxy sdk_uuid_get_client_proxy(string sdk_uuid)
        {
            if (!client_sdk_uuid_dict.TryGetValue(sdk_uuid, out client_proxy _proxy))
            {
                throw new GetPlayerException($"invaild sdk_uuid:{sdk_uuid}");
            }
            return _proxy;
        }

        public client_proxy guid_get_client_proxy(long guid)
        {
            if (!client_guid_dict.TryGetValue(guid, out client_proxy _proxy))
            {
                throw new GetPlayerException($"invaild guid:{guid}");
            }
            return _proxy;
        }
    }
}
