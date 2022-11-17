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
/*this cb code is codegen by abelkhan for c#*/
    public class player_client_rsp_cb : common.imodule {
        public player_client_rsp_cb() 
        {
        }

    }

    public class player_client_clientproxy {
        public string client_uuid_1aaece60_7bb0_3cf7_bd66_aeb26a76183d;
        private Int64 uuid_1aaece60_7bb0_3cf7_bd66_aeb26a76183d = (Int64)RandomUUID.random();

        public player_client_rsp_cb rsp_cb_player_client_handle;

        public player_client_clientproxy(player_client_rsp_cb rsp_cb_player_client_handle_)
        {
            rsp_cb_player_client_handle = rsp_cb_player_client_handle_;
        }

        public void be_displacement(){
            var _argv_156d31bb_d697_3042_a3e8_88d0a5d0484c = new ArrayList();
            hub.hub._gates.call_client(client_uuid_1aaece60_7bb0_3cf7_bd66_aeb26a76183d, "player_client_be_displacement", _argv_156d31bb_d697_3042_a3e8_88d0a5d0484c);
        }

    }

    public class player_client_multicast {
        public List<string> client_uuids_1aaece60_7bb0_3cf7_bd66_aeb26a76183d;
        public player_client_rsp_cb rsp_cb_player_client_handle;

        public player_client_multicast(player_client_rsp_cb rsp_cb_player_client_handle_)
        {
            rsp_cb_player_client_handle = rsp_cb_player_client_handle_;
        }

    }

    public class player_client_broadcast {
        public player_client_rsp_cb rsp_cb_player_client_handle;

        public player_client_broadcast(player_client_rsp_cb rsp_cb_player_client_handle_)
        {
            rsp_cb_player_client_handle = rsp_cb_player_client_handle_;
        }

    }

    public class player_client_caller {
        public static player_client_rsp_cb rsp_cb_player_client_handle = null;
        private player_client_clientproxy _clientproxy;
        private player_client_multicast _multicast;
        private player_client_broadcast _broadcast;

        public player_client_caller() 
        {
            if (rsp_cb_player_client_handle == null)
            {
                rsp_cb_player_client_handle = new player_client_rsp_cb();
            }

            _clientproxy = new player_client_clientproxy(rsp_cb_player_client_handle);
            _multicast = new player_client_multicast(rsp_cb_player_client_handle);
            _broadcast = new player_client_broadcast(rsp_cb_player_client_handle);
        }

        public player_client_clientproxy get_client(string client_uuid) {
            _clientproxy.client_uuid_1aaece60_7bb0_3cf7_bd66_aeb26a76183d = client_uuid;
            return _clientproxy;
        }

        public player_client_multicast get_multicast(List<string> client_uuids) {
            _multicast.client_uuids_1aaece60_7bb0_3cf7_bd66_aeb26a76183d = client_uuids;
            return _multicast;
        }

        public player_client_broadcast get_broadcast() {
            return _broadcast;
        }
    }

/*this cb code is codegen by abelkhan for c#*/
    public class player_game_client_rsp_cb : common.imodule {
        public player_game_client_rsp_cb() 
        {
        }

    }

    public class player_game_client_clientproxy {
        public string client_uuid_e92da3e4_6925_302c_a40e_81b45d8d0d19;
        private Int64 uuid_e92da3e4_6925_302c_a40e_81b45d8d0d19 = (Int64)RandomUUID.random();

        public player_game_client_rsp_cb rsp_cb_player_game_client_handle;

        public player_game_client_clientproxy(player_game_client_rsp_cb rsp_cb_player_game_client_handle_)
        {
            rsp_cb_player_game_client_handle = rsp_cb_player_game_client_handle_;
        }

        public void game_svr(string game_hub_name){
            var _argv_629529e7_d91e_30fb_927a_8f65b81cf2da = new ArrayList();
            _argv_629529e7_d91e_30fb_927a_8f65b81cf2da.Add(game_hub_name);
            hub.hub._gates.call_client(client_uuid_e92da3e4_6925_302c_a40e_81b45d8d0d19, "player_game_client_game_svr", _argv_629529e7_d91e_30fb_927a_8f65b81cf2da);
        }

        public void room_svr(string room_hub_name){
            var _argv_3bb5e4e6_73b3_3767_a171_b2654cd89993 = new ArrayList();
            _argv_3bb5e4e6_73b3_3767_a171_b2654cd89993.Add(room_hub_name);
            hub.hub._gates.call_client(client_uuid_e92da3e4_6925_302c_a40e_81b45d8d0d19, "player_game_client_room_svr", _argv_3bb5e4e6_73b3_3767_a171_b2654cd89993);
        }

        public void settle(game_settle_info settle_info){
            var _argv_b28d056f_3d2a_3ca4_91e6_47b841274e0b = new ArrayList();
            _argv_b28d056f_3d2a_3ca4_91e6_47b841274e0b.Add(game_settle_info.game_settle_info_to_protcol(settle_info));
            hub.hub._gates.call_client(client_uuid_e92da3e4_6925_302c_a40e_81b45d8d0d19, "player_game_client_settle", _argv_b28d056f_3d2a_3ca4_91e6_47b841274e0b);
        }

    }

    public class player_game_client_multicast {
        public List<string> client_uuids_e92da3e4_6925_302c_a40e_81b45d8d0d19;
        public player_game_client_rsp_cb rsp_cb_player_game_client_handle;

        public player_game_client_multicast(player_game_client_rsp_cb rsp_cb_player_game_client_handle_)
        {
            rsp_cb_player_game_client_handle = rsp_cb_player_game_client_handle_;
        }

    }

    public class player_game_client_broadcast {
        public player_game_client_rsp_cb rsp_cb_player_game_client_handle;

        public player_game_client_broadcast(player_game_client_rsp_cb rsp_cb_player_game_client_handle_)
        {
            rsp_cb_player_game_client_handle = rsp_cb_player_game_client_handle_;
        }

    }

    public class player_game_client_caller {
        public static player_game_client_rsp_cb rsp_cb_player_game_client_handle = null;
        private player_game_client_clientproxy _clientproxy;
        private player_game_client_multicast _multicast;
        private player_game_client_broadcast _broadcast;

        public player_game_client_caller() 
        {
            if (rsp_cb_player_game_client_handle == null)
            {
                rsp_cb_player_game_client_handle = new player_game_client_rsp_cb();
            }

            _clientproxy = new player_game_client_clientproxy(rsp_cb_player_game_client_handle);
            _multicast = new player_game_client_multicast(rsp_cb_player_game_client_handle);
            _broadcast = new player_game_client_broadcast(rsp_cb_player_game_client_handle);
        }

        public player_game_client_clientproxy get_client(string client_uuid) {
            _clientproxy.client_uuid_e92da3e4_6925_302c_a40e_81b45d8d0d19 = client_uuid;
            return _clientproxy;
        }

        public player_game_client_multicast get_multicast(List<string> client_uuids) {
            _multicast.client_uuids_e92da3e4_6925_302c_a40e_81b45d8d0d19 = client_uuids;
            return _multicast;
        }

        public player_game_client_broadcast get_broadcast() {
            return _broadcast;
        }
    }

/*this cb code is codegen by abelkhan for c#*/
    public class player_room_client_rsp_cb : common.imodule {
        public player_room_client_rsp_cb() 
        {
        }

    }

    public class player_room_client_clientproxy {
        public string client_uuid_319c79d2_c8d6_35a4_884f_d7c2a7a23134;
        private Int64 uuid_319c79d2_c8d6_35a4_884f_d7c2a7a23134 = (Int64)RandomUUID.random();

        public player_room_client_rsp_cb rsp_cb_player_room_client_handle;

        public player_room_client_clientproxy(player_room_client_rsp_cb rsp_cb_player_room_client_handle_)
        {
            rsp_cb_player_room_client_handle = rsp_cb_player_room_client_handle_;
        }

        public void invite_role_join_room(string room_id, string invite_role_name){
            var _argv_4afdf6f4_2ff9_314b_9be9_c6d0fa96e4f8 = new ArrayList();
            _argv_4afdf6f4_2ff9_314b_9be9_c6d0fa96e4f8.Add(room_id);
            _argv_4afdf6f4_2ff9_314b_9be9_c6d0fa96e4f8.Add(invite_role_name);
            hub.hub._gates.call_client(client_uuid_319c79d2_c8d6_35a4_884f_d7c2a7a23134, "player_room_client_invite_role_join_room", _argv_4afdf6f4_2ff9_314b_9be9_c6d0fa96e4f8);
        }

    }

    public class player_room_client_multicast {
        public List<string> client_uuids_319c79d2_c8d6_35a4_884f_d7c2a7a23134;
        public player_room_client_rsp_cb rsp_cb_player_room_client_handle;

        public player_room_client_multicast(player_room_client_rsp_cb rsp_cb_player_room_client_handle_)
        {
            rsp_cb_player_room_client_handle = rsp_cb_player_room_client_handle_;
        }

    }

    public class player_room_client_broadcast {
        public player_room_client_rsp_cb rsp_cb_player_room_client_handle;

        public player_room_client_broadcast(player_room_client_rsp_cb rsp_cb_player_room_client_handle_)
        {
            rsp_cb_player_room_client_handle = rsp_cb_player_room_client_handle_;
        }

    }

    public class player_room_client_caller {
        public static player_room_client_rsp_cb rsp_cb_player_room_client_handle = null;
        private player_room_client_clientproxy _clientproxy;
        private player_room_client_multicast _multicast;
        private player_room_client_broadcast _broadcast;

        public player_room_client_caller() 
        {
            if (rsp_cb_player_room_client_handle == null)
            {
                rsp_cb_player_room_client_handle = new player_room_client_rsp_cb();
            }

            _clientproxy = new player_room_client_clientproxy(rsp_cb_player_room_client_handle);
            _multicast = new player_room_client_multicast(rsp_cb_player_room_client_handle);
            _broadcast = new player_room_client_broadcast(rsp_cb_player_room_client_handle);
        }

        public player_room_client_clientproxy get_client(string client_uuid) {
            _clientproxy.client_uuid_319c79d2_c8d6_35a4_884f_d7c2a7a23134 = client_uuid;
            return _clientproxy;
        }

        public player_room_client_multicast get_multicast(List<string> client_uuids) {
            _multicast.client_uuids_319c79d2_c8d6_35a4_884f_d7c2a7a23134 = client_uuids;
            return _multicast;
        }

        public player_room_client_broadcast get_broadcast() {
            return _broadcast;
        }
    }

    public class player_friend_client_invite_role_friend_cb
    {
        private UInt64 cb_uuid;
        private player_friend_client_rsp_cb module_rsp_cb;

        public player_friend_client_invite_role_friend_cb(UInt64 _cb_uuid, player_friend_client_rsp_cb _module_rsp_cb)
        {
            cb_uuid = _cb_uuid;
            module_rsp_cb = _module_rsp_cb;
        }

        public event Action on_invite_role_friend_cb;
        public event Action on_invite_role_friend_err;
        public event Action on_invite_role_friend_timeout;

        public player_friend_client_invite_role_friend_cb callBack(Action cb, Action err)
        {
            on_invite_role_friend_cb += cb;
            on_invite_role_friend_err += err;
            return this;
        }

        public void timeout(UInt64 tick, Action timeout_cb)
        {
            TinyTimer.add_timer(tick, ()=>{
                module_rsp_cb.invite_role_friend_timeout(cb_uuid);
            });
            on_invite_role_friend_timeout += timeout_cb;
        }

        public void call_cb()
        {
            if (on_invite_role_friend_cb != null)
            {
                on_invite_role_friend_cb();
            }
        }

        public void call_err()
        {
            if (on_invite_role_friend_err != null)
            {
                on_invite_role_friend_err();
            }
        }

        public void call_timeout()
        {
            if (on_invite_role_friend_timeout != null)
            {
                on_invite_role_friend_timeout();
            }
        }

    }

    public class player_friend_client_agree_role_friend_cb
    {
        private UInt64 cb_uuid;
        private player_friend_client_rsp_cb module_rsp_cb;

        public player_friend_client_agree_role_friend_cb(UInt64 _cb_uuid, player_friend_client_rsp_cb _module_rsp_cb)
        {
            cb_uuid = _cb_uuid;
            module_rsp_cb = _module_rsp_cb;
        }

        public event Action on_agree_role_friend_cb;
        public event Action on_agree_role_friend_err;
        public event Action on_agree_role_friend_timeout;

        public player_friend_client_agree_role_friend_cb callBack(Action cb, Action err)
        {
            on_agree_role_friend_cb += cb;
            on_agree_role_friend_err += err;
            return this;
        }

        public void timeout(UInt64 tick, Action timeout_cb)
        {
            TinyTimer.add_timer(tick, ()=>{
                module_rsp_cb.agree_role_friend_timeout(cb_uuid);
            });
            on_agree_role_friend_timeout += timeout_cb;
        }

        public void call_cb()
        {
            if (on_agree_role_friend_cb != null)
            {
                on_agree_role_friend_cb();
            }
        }

        public void call_err()
        {
            if (on_agree_role_friend_err != null)
            {
                on_agree_role_friend_err();
            }
        }

        public void call_timeout()
        {
            if (on_agree_role_friend_timeout != null)
            {
                on_agree_role_friend_timeout();
            }
        }

    }

/*this cb code is codegen by abelkhan for c#*/
    public class player_friend_client_rsp_cb : common.imodule {
        public Dictionary<UInt64, player_friend_client_invite_role_friend_cb> map_invite_role_friend;
        public Dictionary<UInt64, player_friend_client_agree_role_friend_cb> map_agree_role_friend;
        public player_friend_client_rsp_cb() 
        {
            map_invite_role_friend = new Dictionary<UInt64, player_friend_client_invite_role_friend_cb>();
            hub.hub._modules.add_mothed("player_friend_client_rsp_cb_invite_role_friend_rsp", invite_role_friend_rsp);
            hub.hub._modules.add_mothed("player_friend_client_rsp_cb_invite_role_friend_err", invite_role_friend_err);
            map_agree_role_friend = new Dictionary<UInt64, player_friend_client_agree_role_friend_cb>();
            hub.hub._modules.add_mothed("player_friend_client_rsp_cb_agree_role_friend_rsp", agree_role_friend_rsp);
            hub.hub._modules.add_mothed("player_friend_client_rsp_cb_agree_role_friend_err", agree_role_friend_err);
        }

        public void invite_role_friend_rsp(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var rsp = try_get_and_del_invite_role_friend_cb(uuid);
            if (rsp != null)
            {
                rsp.call_cb();
            }
        }

        public void invite_role_friend_err(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var rsp = try_get_and_del_invite_role_friend_cb(uuid);
            if (rsp != null)
            {
                rsp.call_err();
            }
        }

        public void invite_role_friend_timeout(UInt64 cb_uuid){
            var rsp = try_get_and_del_invite_role_friend_cb(cb_uuid);
            if (rsp != null){
                rsp.call_timeout();
            }
        }

        private player_friend_client_invite_role_friend_cb try_get_and_del_invite_role_friend_cb(UInt64 uuid){
            lock(map_invite_role_friend)
            {
                if (map_invite_role_friend.TryGetValue(uuid, out player_friend_client_invite_role_friend_cb rsp))
                {
                    map_invite_role_friend.Remove(uuid);
                }
                return rsp;
            }
        }

        public void agree_role_friend_rsp(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var rsp = try_get_and_del_agree_role_friend_cb(uuid);
            if (rsp != null)
            {
                rsp.call_cb();
            }
        }

        public void agree_role_friend_err(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var rsp = try_get_and_del_agree_role_friend_cb(uuid);
            if (rsp != null)
            {
                rsp.call_err();
            }
        }

        public void agree_role_friend_timeout(UInt64 cb_uuid){
            var rsp = try_get_and_del_agree_role_friend_cb(cb_uuid);
            if (rsp != null){
                rsp.call_timeout();
            }
        }

        private player_friend_client_agree_role_friend_cb try_get_and_del_agree_role_friend_cb(UInt64 uuid){
            lock(map_agree_role_friend)
            {
                if (map_agree_role_friend.TryGetValue(uuid, out player_friend_client_agree_role_friend_cb rsp))
                {
                    map_agree_role_friend.Remove(uuid);
                }
                return rsp;
            }
        }

    }

    public class player_friend_client_clientproxy {
        public string client_uuid_ab0f8392_038f_32c5_83c3_84897ee30323;
        private Int64 uuid_ab0f8392_038f_32c5_83c3_84897ee30323 = (Int64)RandomUUID.random();

        public player_friend_client_rsp_cb rsp_cb_player_friend_client_handle;

        public player_friend_client_clientproxy(player_friend_client_rsp_cb rsp_cb_player_friend_client_handle_)
        {
            rsp_cb_player_friend_client_handle = rsp_cb_player_friend_client_handle_;
        }

        public player_friend_client_invite_role_friend_cb invite_role_friend(player_friend_info invite_account){
            var uuid_27e53be7_470d_5b98_b037_74e3de0f1203 = (UInt64)Interlocked.Increment(ref uuid_ab0f8392_038f_32c5_83c3_84897ee30323);

            var _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278 = new ArrayList();
            _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278.Add(uuid_27e53be7_470d_5b98_b037_74e3de0f1203);
            _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278.Add(player_friend_info.player_friend_info_to_protcol(invite_account));
            hub.hub._gates.call_client(client_uuid_ab0f8392_038f_32c5_83c3_84897ee30323, "player_friend_client_invite_role_friend", _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278);

            var cb_invite_role_friend_obj = new player_friend_client_invite_role_friend_cb(uuid_27e53be7_470d_5b98_b037_74e3de0f1203, rsp_cb_player_friend_client_handle);
            lock(rsp_cb_player_friend_client_handle.map_invite_role_friend)
            {                rsp_cb_player_friend_client_handle.map_invite_role_friend.Add(uuid_27e53be7_470d_5b98_b037_74e3de0f1203, cb_invite_role_friend_obj);
            }            return cb_invite_role_friend_obj;
        }

        public player_friend_client_agree_role_friend_cb agree_role_friend(player_friend_info target_account){
            var uuid_67bfbc9a_7c4d_5698_93a0_364d7aa95a7e = (UInt64)Interlocked.Increment(ref uuid_ab0f8392_038f_32c5_83c3_84897ee30323);

            var _argv_1f120946_a2d8_34bf_a794_941de0d70f98 = new ArrayList();
            _argv_1f120946_a2d8_34bf_a794_941de0d70f98.Add(uuid_67bfbc9a_7c4d_5698_93a0_364d7aa95a7e);
            _argv_1f120946_a2d8_34bf_a794_941de0d70f98.Add(player_friend_info.player_friend_info_to_protcol(target_account));
            hub.hub._gates.call_client(client_uuid_ab0f8392_038f_32c5_83c3_84897ee30323, "player_friend_client_agree_role_friend", _argv_1f120946_a2d8_34bf_a794_941de0d70f98);

            var cb_agree_role_friend_obj = new player_friend_client_agree_role_friend_cb(uuid_67bfbc9a_7c4d_5698_93a0_364d7aa95a7e, rsp_cb_player_friend_client_handle);
            lock(rsp_cb_player_friend_client_handle.map_agree_role_friend)
            {                rsp_cb_player_friend_client_handle.map_agree_role_friend.Add(uuid_67bfbc9a_7c4d_5698_93a0_364d7aa95a7e, cb_agree_role_friend_obj);
            }            return cb_agree_role_friend_obj;
        }

    }

    public class player_friend_client_multicast {
        public List<string> client_uuids_ab0f8392_038f_32c5_83c3_84897ee30323;
        public player_friend_client_rsp_cb rsp_cb_player_friend_client_handle;

        public player_friend_client_multicast(player_friend_client_rsp_cb rsp_cb_player_friend_client_handle_)
        {
            rsp_cb_player_friend_client_handle = rsp_cb_player_friend_client_handle_;
        }

    }

    public class player_friend_client_broadcast {
        public player_friend_client_rsp_cb rsp_cb_player_friend_client_handle;

        public player_friend_client_broadcast(player_friend_client_rsp_cb rsp_cb_player_friend_client_handle_)
        {
            rsp_cb_player_friend_client_handle = rsp_cb_player_friend_client_handle_;
        }

    }

    public class player_friend_client_caller {
        public static player_friend_client_rsp_cb rsp_cb_player_friend_client_handle = null;
        private player_friend_client_clientproxy _clientproxy;
        private player_friend_client_multicast _multicast;
        private player_friend_client_broadcast _broadcast;

        public player_friend_client_caller() 
        {
            if (rsp_cb_player_friend_client_handle == null)
            {
                rsp_cb_player_friend_client_handle = new player_friend_client_rsp_cb();
            }

            _clientproxy = new player_friend_client_clientproxy(rsp_cb_player_friend_client_handle);
            _multicast = new player_friend_client_multicast(rsp_cb_player_friend_client_handle);
            _broadcast = new player_friend_client_broadcast(rsp_cb_player_friend_client_handle);
        }

        public player_friend_client_clientproxy get_client(string client_uuid) {
            _clientproxy.client_uuid_ab0f8392_038f_32c5_83c3_84897ee30323 = client_uuid;
            return _clientproxy;
        }

        public player_friend_client_multicast get_multicast(List<string> client_uuids) {
            _multicast.client_uuids_ab0f8392_038f_32c5_83c3_84897ee30323 = client_uuids;
            return _multicast;
        }

        public player_friend_client_broadcast get_broadcast() {
            return _broadcast;
        }
    }


}
