using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using MsgPack.Serialization;

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for c#*/

/*this struct code is codegen by abelkhan codegen for c#*/
/*this module code is codegen by abelkhan codegen for c#*/
    public class player_client_module : common.imodule {
        public client.client _client_handle;
        public player_client_module(client.client client_handle_) 
        {
            _client_handle = client_handle_;
            _client_handle.modulemanager.add_mothed("player_client_be_displacement", be_displacement);
        }

        public event Action on_be_displacement;
        public void be_displacement(IList<MsgPack.MessagePackObject> inArray){
            if (on_be_displacement != null){
                on_be_displacement();
            }
        }

    }
    public class player_game_client_module : common.imodule {
        public client.client _client_handle;
        public player_game_client_module(client.client client_handle_) 
        {
            _client_handle = client_handle_;
            _client_handle.modulemanager.add_mothed("player_game_client_game_svr", game_svr);
            _client_handle.modulemanager.add_mothed("player_game_client_room_svr", room_svr);
            _client_handle.modulemanager.add_mothed("player_game_client_settle", settle);
        }

        public event Action<string> on_game_svr;
        public void game_svr(IList<MsgPack.MessagePackObject> inArray){
            var _game_hub_name = ((MsgPack.MessagePackObject)inArray[0]).AsString();
            if (on_game_svr != null){
                on_game_svr(_game_hub_name);
            }
        }

        public event Action<string> on_room_svr;
        public void room_svr(IList<MsgPack.MessagePackObject> inArray){
            var _room_hub_name = ((MsgPack.MessagePackObject)inArray[0]).AsString();
            if (on_room_svr != null){
                on_room_svr(_room_hub_name);
            }
        }

        public event Action<game_settle_info> on_settle;
        public void settle(IList<MsgPack.MessagePackObject> inArray){
            var _settle_info = game_settle_info.protcol_to_game_settle_info(((MsgPack.MessagePackObject)inArray[0]).AsDictionary());
            if (on_settle != null){
                on_settle(_settle_info);
            }
        }

    }
    public class player_room_client_module : common.imodule {
        public client.client _client_handle;
        public player_room_client_module(client.client client_handle_) 
        {
            _client_handle = client_handle_;
            _client_handle.modulemanager.add_mothed("player_room_client_invite_role_join_room", invite_role_join_room);
        }

        public event Action<string, string> on_invite_role_join_room;
        public void invite_role_join_room(IList<MsgPack.MessagePackObject> inArray){
            var _room_id = ((MsgPack.MessagePackObject)inArray[0]).AsString();
            var _invite_role_name = ((MsgPack.MessagePackObject)inArray[1]).AsString();
            if (on_invite_role_join_room != null){
                on_invite_role_join_room(_room_id, _invite_role_name);
            }
        }

    }
    public class player_friend_client_invite_role_friend_rsp : common.Response {
        private UInt64 uuid_f4abe68d_823d_33d5_a6f6_9ebff8eb6e18;
        private string hub_name_7b2d0e53_b589_37f7_a9bc_31fcce44d278;
        private client.client _client_handle;
        public player_friend_client_invite_role_friend_rsp(client.client client_handle_, string current_hub, UInt64 _uuid) 
        {
            _client_handle = client_handle_;
            hub_name_7b2d0e53_b589_37f7_a9bc_31fcce44d278 = current_hub;
            uuid_f4abe68d_823d_33d5_a6f6_9ebff8eb6e18 = _uuid;
        }

        public void rsp(){
            var _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278 = new ArrayList();
            _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278.Add(uuid_f4abe68d_823d_33d5_a6f6_9ebff8eb6e18);
            _client_handle.call_hub(hub_name_7b2d0e53_b589_37f7_a9bc_31fcce44d278, "player_friend_client_rsp_cb_invite_role_friend_rsp", _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278);
        }

        public void err(){
            var _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278 = new ArrayList();
            _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278.Add(uuid_f4abe68d_823d_33d5_a6f6_9ebff8eb6e18);
            _client_handle.call_hub(hub_name_7b2d0e53_b589_37f7_a9bc_31fcce44d278, "player_friend_client_rsp_cb_invite_role_friend_err", _argv_7b2d0e53_b589_37f7_a9bc_31fcce44d278);
        }

    }

    public class player_friend_client_agree_role_friend_rsp : common.Response {
        private UInt64 uuid_8d09e4bc_e374_3918_b734_2a4508dc1ab9;
        private string hub_name_1f120946_a2d8_34bf_a794_941de0d70f98;
        private client.client _client_handle;
        public player_friend_client_agree_role_friend_rsp(client.client client_handle_, string current_hub, UInt64 _uuid) 
        {
            _client_handle = client_handle_;
            hub_name_1f120946_a2d8_34bf_a794_941de0d70f98 = current_hub;
            uuid_8d09e4bc_e374_3918_b734_2a4508dc1ab9 = _uuid;
        }

        public void rsp(){
            var _argv_1f120946_a2d8_34bf_a794_941de0d70f98 = new ArrayList();
            _argv_1f120946_a2d8_34bf_a794_941de0d70f98.Add(uuid_8d09e4bc_e374_3918_b734_2a4508dc1ab9);
            _client_handle.call_hub(hub_name_1f120946_a2d8_34bf_a794_941de0d70f98, "player_friend_client_rsp_cb_agree_role_friend_rsp", _argv_1f120946_a2d8_34bf_a794_941de0d70f98);
        }

        public void err(){
            var _argv_1f120946_a2d8_34bf_a794_941de0d70f98 = new ArrayList();
            _argv_1f120946_a2d8_34bf_a794_941de0d70f98.Add(uuid_8d09e4bc_e374_3918_b734_2a4508dc1ab9);
            _client_handle.call_hub(hub_name_1f120946_a2d8_34bf_a794_941de0d70f98, "player_friend_client_rsp_cb_agree_role_friend_err", _argv_1f120946_a2d8_34bf_a794_941de0d70f98);
        }

    }

    public class player_friend_client_module : common.imodule {
        public client.client _client_handle;
        public player_friend_client_module(client.client client_handle_) 
        {
            _client_handle = client_handle_;
            _client_handle.modulemanager.add_mothed("player_friend_client_invite_role_friend", invite_role_friend);
            _client_handle.modulemanager.add_mothed("player_friend_client_agree_role_friend", agree_role_friend);
        }

        public event Action<player_friend_info> on_invite_role_friend;
        public void invite_role_friend(IList<MsgPack.MessagePackObject> inArray){
            var _cb_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _invite_player = player_friend_info.protcol_to_player_friend_info(((MsgPack.MessagePackObject)inArray[1]).AsDictionary());
            rsp = new player_friend_client_invite_role_friend_rsp(_client_handle, _client_handle.current_hub, _cb_uuid);
            if (on_invite_role_friend != null){
                on_invite_role_friend(_invite_player);
            }
            rsp = null;
        }

        public event Action<player_friend_info> on_agree_role_friend;
        public void agree_role_friend(IList<MsgPack.MessagePackObject> inArray){
            var _cb_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _target_player = player_friend_info.protcol_to_player_friend_info(((MsgPack.MessagePackObject)inArray[1]).AsDictionary());
            rsp = new player_friend_client_agree_role_friend_rsp(_client_handle, _client_handle.current_hub, _cb_uuid);
            if (on_agree_role_friend != null){
                on_agree_role_friend(_target_player);
            }
            rsp = null;
        }

    }

}
