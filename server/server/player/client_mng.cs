using abelkhan;
using hub;
using MongoDB.Bson;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Security.Principal;
using System.Threading;
using System.Threading.Tasks;

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

        private player_info _info;
        public player_info PlayerInfo
        {
            get { return _info; }
        }

        private dbproxyproxy.Collection GuidCollection
        {
            get { return hub.hub.get_random_dbproxyproxy().getCollection(constant.constant.player_db_name, constant.constant.player_db_guid_collection); }
        }

        private string bind_db_proxy_name = null;
        public hub.dbproxyproxy.Collection PlayerCollection
        {
            get
            {
                hub.dbproxyproxy bind_db_proxy = null;
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
                if (_ret != hub.dbproxyproxy.EM_DB_RESULT.EM_DB_SUCESSED)
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

        public client_proxy(string sdk_uuid, player_info info)
        {
            _sdk_uuid = sdk_uuid;
            _info = info;
        }

        public async void create_player(string name)
        {
            _info = new player_info();
            _info.sdk_uuid = _sdk_uuid;
            _info.name = name;
            _info.guid = await get_guid();
            _info.coin = 100;
            _info.score = 0;

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

        public client_proxy token_get_client_proxy(string uuid, string token)
        {
            if (!client_token_dict.Remove(token, out client_proxy _proxy))
            {
                throw new LoginException($"invaild token:{token}");
            }
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

            return _proxy;
        }
    }
}
