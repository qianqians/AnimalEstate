using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using MsgPack.Serialization;

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for c#*/

/*this struct code is codegen by abelkhan codegen for c#*/
/*this caller code is codegen by abelkhan codegen for c#*/
    public class login_player_login_no_author_cb
    {
        private UInt64 cb_uuid;
        private login_rsp_cb module_rsp_cb;

        public login_player_login_no_author_cb(UInt64 _cb_uuid, login_rsp_cb _module_rsp_cb)
        {
            cb_uuid = _cb_uuid;
            module_rsp_cb = _module_rsp_cb;
        }

        public event Action<string, string> on_player_login_no_author_cb;
        public event Action<Int32> on_player_login_no_author_err;
        public event Action on_player_login_no_author_timeout;

        public login_player_login_no_author_cb callBack(Action<string, string> cb, Action<Int32> err)
        {
            on_player_login_no_author_cb += cb;
            on_player_login_no_author_err += err;
            return this;
        }

        public void timeout(UInt64 tick, Action timeout_cb)
        {
            TinyTimer.add_timer(tick, ()=>{
                module_rsp_cb.player_login_no_author_timeout(cb_uuid);
            });
            on_player_login_no_author_timeout += timeout_cb;
        }

        public void call_cb(string player_hub_name, string token)
        {
            if (on_player_login_no_author_cb != null)
            {
                on_player_login_no_author_cb(player_hub_name, token);
            }
        }

        public void call_err(Int32 err)
        {
            if (on_player_login_no_author_err != null)
            {
                on_player_login_no_author_err(err);
            }
        }

        public void call_timeout()
        {
            if (on_player_login_no_author_timeout != null)
            {
                on_player_login_no_author_timeout();
            }
        }

    }

/*this cb code is codegen by abelkhan for c#*/
    public class login_rsp_cb : common.imodule {
        public Dictionary<UInt64, login_player_login_no_author_cb> map_player_login_no_author;
        public login_rsp_cb(common.modulemanager modules)
        {
            map_player_login_no_author = new Dictionary<UInt64, login_player_login_no_author_cb>();
            modules.add_mothed("login_rsp_cb_player_login_no_author_rsp", player_login_no_author_rsp);
            modules.add_mothed("login_rsp_cb_player_login_no_author_err", player_login_no_author_err);
        }

        public void player_login_no_author_rsp(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _player_hub_name = ((MsgPack.MessagePackObject)inArray[1]).AsString();
            var _token = ((MsgPack.MessagePackObject)inArray[2]).AsString();
            var rsp = try_get_and_del_player_login_no_author_cb(uuid);
            if (rsp != null)
            {
                rsp.call_cb(_player_hub_name, _token);
            }
        }

        public void player_login_no_author_err(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _err = ((MsgPack.MessagePackObject)inArray[1]).AsInt32();
            var rsp = try_get_and_del_player_login_no_author_cb(uuid);
            if (rsp != null)
            {
                rsp.call_err(_err);
            }
        }

        public void player_login_no_author_timeout(UInt64 cb_uuid){
            var rsp = try_get_and_del_player_login_no_author_cb(cb_uuid);
            if (rsp != null){
                rsp.call_timeout();
            }
        }

        private login_player_login_no_author_cb try_get_and_del_player_login_no_author_cb(UInt64 uuid){
            lock(map_player_login_no_author)
            {
                if (map_player_login_no_author.TryGetValue(uuid, out login_player_login_no_author_cb rsp))
                {
                    map_player_login_no_author.Remove(uuid);
                }
                return rsp;
            }
        }

    }

    public class login_caller {
        public static login_rsp_cb rsp_cb_login_handle = null;
        private login_hubproxy _hubproxy;
        public login_caller(client.client _client_handle) 
        {
            if (rsp_cb_login_handle == null)
            {
                rsp_cb_login_handle = new login_rsp_cb(_client_handle.modulemanager);
            }

            _hubproxy = new login_hubproxy(_client_handle, rsp_cb_login_handle);
        }

        public login_hubproxy get_hub(string hub_name)
        {
            _hubproxy.hub_name_d3bb20a7_d0fc_3440_bb9e_b3cc0630e2d1 = hub_name;
            return _hubproxy;
        }

    }

    public class login_hubproxy {
        public string hub_name_d3bb20a7_d0fc_3440_bb9e_b3cc0630e2d1;
        private Int32 uuid_d3bb20a7_d0fc_3440_bb9e_b3cc0630e2d1 = (Int32)RandomUUID.random();

        public client.client _client_handle;
        public login_rsp_cb rsp_cb_login_handle;

        public login_hubproxy(client.client client_handle_, login_rsp_cb rsp_cb_login_handle_)
        {
            _client_handle = client_handle_;
            rsp_cb_login_handle = rsp_cb_login_handle_;
        }

        public login_player_login_no_author_cb player_login_no_author(string account){
            var uuid_bb47480f_4208_5766_8691_969c21d11b5d = (UInt64)Interlocked.Increment(ref uuid_d3bb20a7_d0fc_3440_bb9e_b3cc0630e2d1);

            var _argv_2c74a728_390c_3834_83d5_c8331456ea49 = new ArrayList();
            _argv_2c74a728_390c_3834_83d5_c8331456ea49.Add(uuid_bb47480f_4208_5766_8691_969c21d11b5d);
            _argv_2c74a728_390c_3834_83d5_c8331456ea49.Add(account);
            _client_handle.call_hub(hub_name_d3bb20a7_d0fc_3440_bb9e_b3cc0630e2d1, "login_player_login_no_author", _argv_2c74a728_390c_3834_83d5_c8331456ea49);

            var cb_player_login_no_author_obj = new login_player_login_no_author_cb(uuid_bb47480f_4208_5766_8691_969c21d11b5d, rsp_cb_login_handle);
            lock(rsp_cb_login_handle.map_player_login_no_author)
            {                rsp_cb_login_handle.map_player_login_no_author.Add(uuid_bb47480f_4208_5766_8691_969c21d11b5d, cb_player_login_no_author_obj);
            }            return cb_player_login_no_author_obj;
        }

    }

}
