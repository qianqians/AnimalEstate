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
    public class match_game_start_game_cb
    {
        private UInt64 cb_uuid;
        private match_game_rsp_cb module_rsp_cb;

        public match_game_start_game_cb(UInt64 _cb_uuid, match_game_rsp_cb _module_rsp_cb)
        {
            cb_uuid = _cb_uuid;
            module_rsp_cb = _module_rsp_cb;
        }

        public event Action on_start_game_cb;
        public event Action<Int32> on_start_game_err;
        public event Action on_start_game_timeout;

        public match_game_start_game_cb callBack(Action cb, Action<Int32> err)
        {
            on_start_game_cb += cb;
            on_start_game_err += err;
            return this;
        }

        public void timeout(UInt64 tick, Action timeout_cb)
        {
            TinyTimer.add_timer(tick, ()=>{
                module_rsp_cb.start_game_timeout(cb_uuid);
            });
            on_start_game_timeout += timeout_cb;
        }

        public void call_cb()
        {
            if (on_start_game_cb != null)
            {
                on_start_game_cb();
            }
        }

        public void call_err(Int32 err)
        {
            if (on_start_game_err != null)
            {
                on_start_game_err(err);
            }
        }

        public void call_timeout()
        {
            if (on_start_game_timeout != null)
            {
                on_start_game_timeout();
            }
        }

    }

/*this cb code is codegen by abelkhan for c#*/
    public class match_game_rsp_cb : common.imodule {
        public Dictionary<UInt64, match_game_start_game_cb> map_start_game;
        public match_game_rsp_cb()
        {
            map_start_game = new Dictionary<UInt64, match_game_start_game_cb>();
            hub.hub._modules.add_mothed("match_game_rsp_cb_start_game_rsp", start_game_rsp);
            hub.hub._modules.add_mothed("match_game_rsp_cb_start_game_err", start_game_err);
        }

        public void start_game_rsp(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var rsp = try_get_and_del_start_game_cb(uuid);
            if (rsp != null)
            {
                rsp.call_cb();
            }
        }

        public void start_game_err(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _err = ((MsgPack.MessagePackObject)inArray[1]).AsInt32();
            var rsp = try_get_and_del_start_game_cb(uuid);
            if (rsp != null)
            {
                rsp.call_err(_err);
            }
        }

        public void start_game_timeout(UInt64 cb_uuid){
            var rsp = try_get_and_del_start_game_cb(cb_uuid);
            if (rsp != null){
                rsp.call_timeout();
            }
        }

        private match_game_start_game_cb try_get_and_del_start_game_cb(UInt64 uuid){
            lock(map_start_game)
            {
                if (map_start_game.TryGetValue(uuid, out match_game_start_game_cb rsp))
                {
                    map_start_game.Remove(uuid);
                }
                return rsp;
            }
        }

    }

    public class match_game_caller {
        public static match_game_rsp_cb rsp_cb_match_game_handle = null;
        private match_game_hubproxy _hubproxy;
        public match_game_caller()
        {
            if (rsp_cb_match_game_handle == null)
            {
                rsp_cb_match_game_handle = new match_game_rsp_cb();
            }
            _hubproxy = new match_game_hubproxy(rsp_cb_match_game_handle);
        }

        public match_game_hubproxy get_hub(string hub_name) {
            _hubproxy.hub_name_c4041984_8d90_3417_8e13_9d51947982cb = hub_name;
            return _hubproxy;
        }

    }

    public class match_game_hubproxy {
        public string hub_name_c4041984_8d90_3417_8e13_9d51947982cb;
        private Int64 uuid_c4041984_8d90_3417_8e13_9d51947982cb = (Int64)RandomUUID.random();

        private match_game_rsp_cb rsp_cb_match_game_handle;

        public match_game_hubproxy(match_game_rsp_cb rsp_cb_match_game_handle_)
        {
            rsp_cb_match_game_handle = rsp_cb_match_game_handle_;
        }

        public match_game_start_game_cb start_game(room_info _info){
            var uuid_f06e9503_61db_5f2e_8f88_644242d7103f = (UInt64)Interlocked.Increment(ref uuid_c4041984_8d90_3417_8e13_9d51947982cb);

            var _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747 = new ArrayList();
            _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747.Add(uuid_f06e9503_61db_5f2e_8f88_644242d7103f);
            _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747.Add(room_info.room_info_to_protcol(_info));
            hub.hub._hubs.call_hub(hub_name_c4041984_8d90_3417_8e13_9d51947982cb, "match_game_start_game", _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747);

            var cb_start_game_obj = new match_game_start_game_cb(uuid_f06e9503_61db_5f2e_8f88_644242d7103f, rsp_cb_match_game_handle);
            lock(rsp_cb_match_game_handle.map_start_game)
            {
                rsp_cb_match_game_handle.map_start_game.Add(uuid_f06e9503_61db_5f2e_8f88_644242d7103f, cb_start_game_obj);
            }
            return cb_start_game_obj;
        }

    }
/*this module code is codegen by abelkhan codegen for c#*/
    public class match_game_start_game_rsp : common.Response {
        private string _hub_name_3ad8ee08_b505_3abe_b70d_9c6b12861747;
        private UInt64 uuid_98c011c2_b548_3891_990d_a3554c01f8e8;
        public match_game_start_game_rsp(string hub_name, UInt64 _uuid) 
        {
            _hub_name_3ad8ee08_b505_3abe_b70d_9c6b12861747 = hub_name;
            uuid_98c011c2_b548_3891_990d_a3554c01f8e8 = _uuid;
        }

        public void rsp(){
            var _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747 = new ArrayList();
            _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747.Add(uuid_98c011c2_b548_3891_990d_a3554c01f8e8);
            hub.hub._hubs.call_hub(_hub_name_3ad8ee08_b505_3abe_b70d_9c6b12861747, "match_game_rsp_cb_start_game_rsp", _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747);
        }

        public void err(Int32 err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696){
            var _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747 = new ArrayList();
            _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747.Add(uuid_98c011c2_b548_3891_990d_a3554c01f8e8);
            _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747.Add(err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696);
            hub.hub._hubs.call_hub(_hub_name_3ad8ee08_b505_3abe_b70d_9c6b12861747, "match_game_rsp_cb_start_game_err", _argv_3ad8ee08_b505_3abe_b70d_9c6b12861747);
        }

    }

    public class match_game_module : common.imodule {
        public match_game_module() 
        {
            hub.hub._modules.add_mothed("match_game_start_game", start_game);
        }

        public event Action<room_info> on_start_game;
        public void start_game(IList<MsgPack.MessagePackObject> inArray){
            var _cb_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var __info = room_info.protcol_to_room_info(((MsgPack.MessagePackObject)inArray[1]).AsDictionary());
            rsp = new match_game_start_game_rsp(hub.hub._hubs.current_hubproxy.name, _cb_uuid);
            if (on_start_game != null){
                on_start_game(__info);
            }
            rsp = null;
        }

    }

}
