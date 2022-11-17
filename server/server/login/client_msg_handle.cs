using abelkhan;
using System;
using System.Threading;

namespace login
{
    class client_msg_handle
    {
        private abelkhan.login_module login_Module = new abelkhan.login_module();

        public client_msg_handle()
        {
            login_Module.on_player_login_no_author += Login_Module_on_player_login_no_author;
        }

        private async void Login_Module_on_player_login_no_author(string account)
        {
            log.log.trace("on_player_login_no_author begin! player account:{0}", account);

            var rsp = login_Module.rsp as abelkhan.login_player_login_no_author_rsp;

            var _proxy = await login._player_proxy_mng.random_idle_player();
            if (_proxy != null)
            {
                _proxy.player_login(account).callBack((token) => {
                    rsp.rsp(_proxy.name, token);
                }, (err) => {
                    rsp.err(err);
                }).timeout(1000, () => {
                    rsp.err((int)error.timeout);
                });
            }
            else
            {
                rsp.err((int)error.server_busy);
            }
        }
    }
}
