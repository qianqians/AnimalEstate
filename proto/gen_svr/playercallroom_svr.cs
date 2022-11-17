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
    public class player_room_create_room_cb
    {
        private UInt64 cb_uuid;
        private player_room_rsp_cb module_rsp_cb;

        public player_room_create_room_cb(UInt64 _cb_uuid, player_room_rsp_cb _module_rsp_cb)
        {
            cb_uuid = _cb_uuid;
            module_rsp_cb = _module_rsp_cb;
        }

        public event Action<room_info> on_create_room_cb;
        public event Action<Int32> on_create_room_err;
        public event Action on_create_room_timeout;

        public player_room_create_room_cb callBack(Action<room_info> cb, Action<Int32> err)
        {
            on_create_room_cb += cb;
            on_create_room_err += err;
            return this;
        }

        public void timeout(UInt64 tick, Action timeout_cb)
        {
            TinyTimer.add_timer(tick, ()=>{
                module_rsp_cb.create_room_timeout(cb_uuid);
            });
            on_create_room_timeout += timeout_cb;
        }

        public void call_cb(room_info info)
        {
            if (on_create_room_cb != null)
            {
                on_create_room_cb(info);
            }
        }

        public void call_err(Int32 err)
        {
            if (on_create_room_err != null)
            {
                on_create_room_err(err);
            }
        }

        public void call_timeout()
        {
            if (on_create_room_timeout != null)
            {
                on_create_room_timeout();
            }
        }

    }

    public class player_room_agree_join_room_cb
    {
        private UInt64 cb_uuid;
        private player_room_rsp_cb module_rsp_cb;

        public player_room_agree_join_room_cb(UInt64 _cb_uuid, player_room_rsp_cb _module_rsp_cb)
        {
            cb_uuid = _cb_uuid;
            module_rsp_cb = _module_rsp_cb;
        }

        public event Action<room_info> on_agree_join_room_cb;
        public event Action<Int32> on_agree_join_room_err;
        public event Action on_agree_join_room_timeout;

        public player_room_agree_join_room_cb callBack(Action<room_info> cb, Action<Int32> err)
        {
            on_agree_join_room_cb += cb;
            on_agree_join_room_err += err;
            return this;
        }

        public void timeout(UInt64 tick, Action timeout_cb)
        {
            TinyTimer.add_timer(tick, ()=>{
                module_rsp_cb.agree_join_room_timeout(cb_uuid);
            });
            on_agree_join_room_timeout += timeout_cb;
        }

        public void call_cb(room_info info)
        {
            if (on_agree_join_room_cb != null)
            {
                on_agree_join_room_cb(info);
            }
        }

        public void call_err(Int32 err)
        {
            if (on_agree_join_room_err != null)
            {
                on_agree_join_room_err(err);
            }
        }

        public void call_timeout()
        {
            if (on_agree_join_room_timeout != null)
            {
                on_agree_join_room_timeout();
            }
        }

    }

/*this cb code is codegen by abelkhan for c#*/
    public class player_room_rsp_cb : common.imodule {
        public Dictionary<UInt64, player_room_create_room_cb> map_create_room;
        public Dictionary<UInt64, player_room_agree_join_room_cb> map_agree_join_room;
        public player_room_rsp_cb()
        {
            map_create_room = new Dictionary<UInt64, player_room_create_room_cb>();
            hub.hub._modules.add_mothed("player_room_rsp_cb_create_room_rsp", create_room_rsp);
            hub.hub._modules.add_mothed("player_room_rsp_cb_create_room_err", create_room_err);
            map_agree_join_room = new Dictionary<UInt64, player_room_agree_join_room_cb>();
            hub.hub._modules.add_mothed("player_room_rsp_cb_agree_join_room_rsp", agree_join_room_rsp);
            hub.hub._modules.add_mothed("player_room_rsp_cb_agree_join_room_err", agree_join_room_err);
        }

        public void create_room_rsp(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _info = room_info.protcol_to_room_info(((MsgPack.MessagePackObject)inArray[1]).AsDictionary());
            var rsp = try_get_and_del_create_room_cb(uuid);
            if (rsp != null)
            {
                rsp.call_cb(_info);
            }
        }

        public void create_room_err(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _err = ((MsgPack.MessagePackObject)inArray[1]).AsInt32();
            var rsp = try_get_and_del_create_room_cb(uuid);
            if (rsp != null)
            {
                rsp.call_err(_err);
            }
        }

        public void create_room_timeout(UInt64 cb_uuid){
            var rsp = try_get_and_del_create_room_cb(cb_uuid);
            if (rsp != null){
                rsp.call_timeout();
            }
        }

        private player_room_create_room_cb try_get_and_del_create_room_cb(UInt64 uuid){
            lock(map_create_room)
            {
                if (map_create_room.TryGetValue(uuid, out player_room_create_room_cb rsp))
                {
                    map_create_room.Remove(uuid);
                }
                return rsp;
            }
        }

        public void agree_join_room_rsp(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _info = room_info.protcol_to_room_info(((MsgPack.MessagePackObject)inArray[1]).AsDictionary());
            var rsp = try_get_and_del_agree_join_room_cb(uuid);
            if (rsp != null)
            {
                rsp.call_cb(_info);
            }
        }

        public void agree_join_room_err(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _err = ((MsgPack.MessagePackObject)inArray[1]).AsInt32();
            var rsp = try_get_and_del_agree_join_room_cb(uuid);
            if (rsp != null)
            {
                rsp.call_err(_err);
            }
        }

        public void agree_join_room_timeout(UInt64 cb_uuid){
            var rsp = try_get_and_del_agree_join_room_cb(cb_uuid);
            if (rsp != null){
                rsp.call_timeout();
            }
        }

        private player_room_agree_join_room_cb try_get_and_del_agree_join_room_cb(UInt64 uuid){
            lock(map_agree_join_room)
            {
                if (map_agree_join_room.TryGetValue(uuid, out player_room_agree_join_room_cb rsp))
                {
                    map_agree_join_room.Remove(uuid);
                }
                return rsp;
            }
        }

    }

    public class player_room_caller {
        public static player_room_rsp_cb rsp_cb_player_room_handle = null;
        private player_room_hubproxy _hubproxy;
        public player_room_caller()
        {
            if (rsp_cb_player_room_handle == null)
            {
                rsp_cb_player_room_handle = new player_room_rsp_cb();
            }
            _hubproxy = new player_room_hubproxy(rsp_cb_player_room_handle);
        }

        public player_room_hubproxy get_hub(string hub_name) {
            _hubproxy.hub_name_0cbb8ec7_5c42_333d_86fd_100c0951d27f = hub_name;
            return _hubproxy;
        }

    }

    public class player_room_hubproxy {
        public string hub_name_0cbb8ec7_5c42_333d_86fd_100c0951d27f;
        private Int64 uuid_0cbb8ec7_5c42_333d_86fd_100c0951d27f = (Int64)RandomUUID.random();

        private player_room_rsp_cb rsp_cb_player_room_handle;

        public player_room_hubproxy(player_room_rsp_cb rsp_cb_player_room_handle_)
        {
            rsp_cb_player_room_handle = rsp_cb_player_room_handle_;
        }

        public player_room_create_room_cb create_room(player_inline_info room_owner){
            var uuid_596b5288_d0f2_52ea_802a_a61621d93808 = (UInt64)Interlocked.Increment(ref uuid_0cbb8ec7_5c42_333d_86fd_100c0951d27f);

            var _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee = new ArrayList();
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.Add(uuid_596b5288_d0f2_52ea_802a_a61621d93808);
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.Add(player_inline_info.player_inline_info_to_protcol(room_owner));
            hub.hub._hubs.call_hub(hub_name_0cbb8ec7_5c42_333d_86fd_100c0951d27f, "player_room_create_room", _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee);

            var cb_create_room_obj = new player_room_create_room_cb(uuid_596b5288_d0f2_52ea_802a_a61621d93808, rsp_cb_player_room_handle);
            lock(rsp_cb_player_room_handle.map_create_room)
            {
                rsp_cb_player_room_handle.map_create_room.Add(uuid_596b5288_d0f2_52ea_802a_a61621d93808, cb_create_room_obj);
            }
            return cb_create_room_obj;
        }

        public player_room_agree_join_room_cb agree_join_room(string room_id, player_inline_info member){
            var uuid_2b5aaead_9c5d_5e1b_b2f5_62a6bfb42fe9 = (UInt64)Interlocked.Increment(ref uuid_0cbb8ec7_5c42_333d_86fd_100c0951d27f);

            var _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b = new ArrayList();
            _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.Add(uuid_2b5aaead_9c5d_5e1b_b2f5_62a6bfb42fe9);
            _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.Add(room_id);
            _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.Add(player_inline_info.player_inline_info_to_protcol(member));
            hub.hub._hubs.call_hub(hub_name_0cbb8ec7_5c42_333d_86fd_100c0951d27f, "player_room_agree_join_room", _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b);

            var cb_agree_join_room_obj = new player_room_agree_join_room_cb(uuid_2b5aaead_9c5d_5e1b_b2f5_62a6bfb42fe9, rsp_cb_player_room_handle);
            lock(rsp_cb_player_room_handle.map_agree_join_room)
            {
                rsp_cb_player_room_handle.map_agree_join_room.Add(uuid_2b5aaead_9c5d_5e1b_b2f5_62a6bfb42fe9, cb_agree_join_room_obj);
            }
            return cb_agree_join_room_obj;
        }

    }
/*this module code is codegen by abelkhan codegen for c#*/
    public class player_room_create_room_rsp : common.Response {
        private string _hub_name_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee;
        private UInt64 uuid_23854e65_5189_3f0a_a35a_e9ce5a5cd896;
        public player_room_create_room_rsp(string hub_name, UInt64 _uuid) 
        {
            _hub_name_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee = hub_name;
            uuid_23854e65_5189_3f0a_a35a_e9ce5a5cd896 = _uuid;
        }

        public void rsp(room_info info_391fd3d4_2d55_3f5e_9223_7f450a814a15){
            var _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee = new ArrayList();
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.Add(uuid_23854e65_5189_3f0a_a35a_e9ce5a5cd896);
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.Add(room_info.room_info_to_protcol(info_391fd3d4_2d55_3f5e_9223_7f450a814a15));
            hub.hub._hubs.call_hub(_hub_name_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee, "player_room_rsp_cb_create_room_rsp", _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee);
        }

        public void err(Int32 err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696){
            var _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee = new ArrayList();
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.Add(uuid_23854e65_5189_3f0a_a35a_e9ce5a5cd896);
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.Add(err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696);
            hub.hub._hubs.call_hub(_hub_name_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee, "player_room_rsp_cb_create_room_err", _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee);
        }

    }

    public class player_room_agree_join_room_rsp : common.Response {
        private string _hub_name_dd5a04d0_146c_30d4_bf08_5551c02a714b;
        private UInt64 uuid_8b9e7ae0_59b9_315d_8b03_8c1b2c614dec;
        public player_room_agree_join_room_rsp(string hub_name, UInt64 _uuid) 
        {
            _hub_name_dd5a04d0_146c_30d4_bf08_5551c02a714b = hub_name;
            uuid_8b9e7ae0_59b9_315d_8b03_8c1b2c614dec = _uuid;
        }

        public void rsp(room_info info_391fd3d4_2d55_3f5e_9223_7f450a814a15){
            var _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b = new ArrayList();
            _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.Add(uuid_8b9e7ae0_59b9_315d_8b03_8c1b2c614dec);
            _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.Add(room_info.room_info_to_protcol(info_391fd3d4_2d55_3f5e_9223_7f450a814a15));
            hub.hub._hubs.call_hub(_hub_name_dd5a04d0_146c_30d4_bf08_5551c02a714b, "player_room_rsp_cb_agree_join_room_rsp", _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b);
        }

        public void err(Int32 err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696){
            var _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b = new ArrayList();
            _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.Add(uuid_8b9e7ae0_59b9_315d_8b03_8c1b2c614dec);
            _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.Add(err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696);
            hub.hub._hubs.call_hub(_hub_name_dd5a04d0_146c_30d4_bf08_5551c02a714b, "player_room_rsp_cb_agree_join_room_err", _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b);
        }

    }

    public class player_room_module : common.imodule {
        public player_room_module() 
        {
            hub.hub._modules.add_mothed("player_room_create_room", create_room);
            hub.hub._modules.add_mothed("player_room_agree_join_room", agree_join_room);
        }

        public event Action<player_inline_info> on_create_room;
        public void create_room(IList<MsgPack.MessagePackObject> inArray){
            var _cb_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _room_owner = player_inline_info.protcol_to_player_inline_info(((MsgPack.MessagePackObject)inArray[1]).AsDictionary());
            rsp = new player_room_create_room_rsp(hub.hub._hubs.current_hubproxy.name, _cb_uuid);
            if (on_create_room != null){
                on_create_room(_room_owner);
            }
            rsp = null;
        }

        public event Action<string, player_inline_info> on_agree_join_room;
        public void agree_join_room(IList<MsgPack.MessagePackObject> inArray){
            var _cb_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _room_id = ((MsgPack.MessagePackObject)inArray[1]).AsString();
            var _member = player_inline_info.protcol_to_player_inline_info(((MsgPack.MessagePackObject)inArray[2]).AsDictionary());
            rsp = new player_room_agree_join_room_rsp(hub.hub._hubs.current_hubproxy.name, _cb_uuid);
            if (on_agree_join_room != null){
                on_agree_join_room(_room_id, _member);
            }
            rsp = null;
        }

    }

}
