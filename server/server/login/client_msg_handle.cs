using abelkhan;
using System.Security.Cryptography;
using System.Security.Principal;

namespace login
{
    class client_msg_handle
    {
        private login_module login_Module = new login_module();

        public client_msg_handle()
        {
            login_Module.on_player_login_no_author += Login_Module_on_player_login_no_author;
        }

        private void try_player_login(player_proxy _proxy, string account, login_player_login_no_author_rsp rsp)
        {
            var key = redis_help.BuildPlayerSvrCacheKey(account);
            login._redis_handle.SetStrData(key, _proxy.name);

            _proxy.player_login(account).callBack((token) => {
                rsp.rsp(_proxy.name, token);
            }, (err) => {
                rsp.err(err);
            }).timeout(1000, () => {
                rsp.err((int)error.timeout);
            });
        }

        private async void random_player_svr_rsp(string account, login_player_login_no_author_rsp rsp)
        {
            var _proxy = await login._player_proxy_mng.random_idle_player();
            if (_proxy != null)
            {
                try_player_login(_proxy, account, rsp);
            }
            else
            {
                rsp.err((int)error.server_busy);
            }
        }

        private async void Login_Module_on_player_login_no_author(string account)
        {
            log.log.trace("on_player_login_no_author begin! player account:{0}", account);

            var rsp = login_Module.rsp as login_player_login_no_author_rsp;
            var uuid = hub.hub._gates.current_client_uuid;

            var lock_key = redis_help.BuildPlayerSvrCacheLockKey(account);
            var token = $"lock_{account}";
            try
            {
                await login._redis_handle.Lock(lock_key, token, 1000);

                var key = redis_help.BuildPlayerSvrCacheKey(account);
                var _player_proxy_name = await login._redis_handle.GetStrData(key);
                if (string.IsNullOrEmpty(_player_proxy_name))
                {
                    random_player_svr_rsp(account, rsp);
                }
                else
                {
                    var _proxy = login._player_proxy_mng.get_player(_player_proxy_name);
                    if (_proxy != null)
                    {
                        try_player_login(_proxy, account, rsp);
                    }
                    else
                    {
                        random_player_svr_rsp(account, rsp);
                    }
                }

                var gate_key = redis_help.BuildPlayerGateCacheKey(account);
                await login._redis_handle.SetStrData(key, hub.hub._gates.get_client_gate_name(uuid));
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
                rsp.err((int)error.db_error);
            }
            finally
            {
                await login._redis_handle.UnLock(lock_key, token);
            }
        }
    }
}
