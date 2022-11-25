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
    public class player_login_player_login_rsp : common.Response {
        private string _client_uuid_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b;
        private UInt64 uuid_ade41c97_e005_3aac_9b68_925d09412afe;
        public player_login_player_login_rsp(string client_uuid, UInt64 _uuid)
        {
            _client_uuid_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b = client_uuid;
            uuid_ade41c97_e005_3aac_9b68_925d09412afe = _uuid;
        }

        public void rsp(player_info info_391fd3d4_2d55_3f5e_9223_7f450a814a15){
            var _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b = new ArrayList();
            _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b.Add(uuid_ade41c97_e005_3aac_9b68_925d09412afe);
            _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b.Add(player_info.player_info_to_protcol(info_391fd3d4_2d55_3f5e_9223_7f450a814a15));
            hub.hub._gates.call_client(_client_uuid_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b, "player_login_rsp_cb_player_login_rsp", _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b);
        }

        public void err(Int32 err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696){
            var _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b = new ArrayList();
            _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b.Add(uuid_ade41c97_e005_3aac_9b68_925d09412afe);
            _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b.Add(err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696);
            hub.hub._gates.call_client(_client_uuid_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b, "player_login_rsp_cb_player_login_err", _argv_803b03c3_eef6_3b5c_a790_4cd13c6c4e4b);
        }

    }

    public class player_login_create_role_rsp : common.Response {
        private string _client_uuid_30293c4a_8f5b_307e_a08a_ff76e003f95d;
        private UInt64 uuid_9b570d40_93db_3172_b2b2_238a3ebca94b;
        public player_login_create_role_rsp(string client_uuid, UInt64 _uuid)
        {
            _client_uuid_30293c4a_8f5b_307e_a08a_ff76e003f95d = client_uuid;
            uuid_9b570d40_93db_3172_b2b2_238a3ebca94b = _uuid;
        }

        public void rsp(player_info info_391fd3d4_2d55_3f5e_9223_7f450a814a15){
            var _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d = new ArrayList();
            _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d.Add(uuid_9b570d40_93db_3172_b2b2_238a3ebca94b);
            _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d.Add(player_info.player_info_to_protcol(info_391fd3d4_2d55_3f5e_9223_7f450a814a15));
            hub.hub._gates.call_client(_client_uuid_30293c4a_8f5b_307e_a08a_ff76e003f95d, "player_login_rsp_cb_create_role_rsp", _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d);
        }

        public void err(Int32 err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696){
            var _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d = new ArrayList();
            _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d.Add(uuid_9b570d40_93db_3172_b2b2_238a3ebca94b);
            _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d.Add(err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696);
            hub.hub._gates.call_client(_client_uuid_30293c4a_8f5b_307e_a08a_ff76e003f95d, "player_login_rsp_cb_create_role_err", _argv_30293c4a_8f5b_307e_a08a_ff76e003f95d);
        }

    }

    public class player_login_module : common.imodule {
        public player_login_module()
        {
            hub.hub._modules.add_mothed("player_login_player_login", player_login);
            hub.hub._modules.add_mothed("player_login_create_role", create_role);
        }

        public event Action<string> on_player_login;
        public void player_login(IList<MsgPack.MessagePackObject> inArray){
            var _cb_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _token = ((MsgPack.MessagePackObject)inArray[1]).AsString();
            rsp = new player_login_player_login_rsp(hub.hub._gates.current_client_uuid, _cb_uuid);
            if (on_player_login != null){
                on_player_login(_token);
            }
            rsp = null;
        }

        public event Action<string> on_create_role;
        public void create_role(IList<MsgPack.MessagePackObject> inArray){
            var _cb_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _name = ((MsgPack.MessagePackObject)inArray[1]).AsString();
            rsp = new player_login_create_role_rsp(hub.hub._gates.current_client_uuid, _cb_uuid);
            if (on_create_role != null){
                on_create_role(_name);
            }
            rsp = null;
        }

    }
    public class client_match_module : common.imodule {
        public client_match_module()
        {
            hub.hub._modules.add_mothed("client_match_start_match", start_match);
        }

        public event Action<playground> on_start_match;
        public void start_match(IList<MsgPack.MessagePackObject> inArray){
            var __playground = (playground)((MsgPack.MessagePackObject)inArray[0]).AsInt32();
            if (on_start_match != null){
                on_start_match(__playground);
            }
        }

    }
    public class client_room_player_create_room_rsp : common.Response {
        private string _client_uuid_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee;
        private UInt64 uuid_23854e65_5189_3f0a_a35a_e9ce5a5cd896;
        public client_room_player_create_room_rsp(string client_uuid, UInt64 _uuid)
        {
            _client_uuid_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee = client_uuid;
            uuid_23854e65_5189_3f0a_a35a_e9ce5a5cd896 = _uuid;
        }

        public void rsp(string room_hub_name_8b821011_725a_3f62_82ea_fb325d2729fa, room_info _room_info_c9f81e0b_8592_38f3_ac0b_f5dd151063b1){
            var _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee = new ArrayList();
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.Add(uuid_23854e65_5189_3f0a_a35a_e9ce5a5cd896);
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.Add(room_hub_name_8b821011_725a_3f62_82ea_fb325d2729fa);
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.Add(room_info.room_info_to_protcol(_room_info_c9f81e0b_8592_38f3_ac0b_f5dd151063b1));
            hub.hub._gates.call_client(_client_uuid_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee, "client_room_player_rsp_cb_create_room_rsp", _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee);
        }

        public void err(Int32 err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696){
            var _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee = new ArrayList();
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.Add(uuid_23854e65_5189_3f0a_a35a_e9ce5a5cd896);
            _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee.Add(err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696);
            hub.hub._gates.call_client(_client_uuid_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee, "client_room_player_rsp_cb_create_room_err", _argv_0f87a215_0b4f_3a78_9d92_9bd3f4aa6dee);
        }

    }

    public class client_room_player_agree_join_room_rsp : common.Response {
        private string _client_uuid_dd5a04d0_146c_30d4_bf08_5551c02a714b;
        private UInt64 uuid_8b9e7ae0_59b9_315d_8b03_8c1b2c614dec;
        public client_room_player_agree_join_room_rsp(string client_uuid, UInt64 _uuid)
        {
            _client_uuid_dd5a04d0_146c_30d4_bf08_5551c02a714b = client_uuid;
            uuid_8b9e7ae0_59b9_315d_8b03_8c1b2c614dec = _uuid;
        }

        public void rsp(string room_hub_name_8b821011_725a_3f62_82ea_fb325d2729fa, room_info _room_info_c9f81e0b_8592_38f3_ac0b_f5dd151063b1){
            var _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b = new ArrayList();
            _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.Add(uuid_8b9e7ae0_59b9_315d_8b03_8c1b2c614dec);
            _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.Add(room_hub_name_8b821011_725a_3f62_82ea_fb325d2729fa);
            _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.Add(room_info.room_info_to_protcol(_room_info_c9f81e0b_8592_38f3_ac0b_f5dd151063b1));
            hub.hub._gates.call_client(_client_uuid_dd5a04d0_146c_30d4_bf08_5551c02a714b, "client_room_player_rsp_cb_agree_join_room_rsp", _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b);
        }

        public void err(Int32 err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696){
            var _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b = new ArrayList();
            _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.Add(uuid_8b9e7ae0_59b9_315d_8b03_8c1b2c614dec);
            _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b.Add(err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696);
            hub.hub._gates.call_client(_client_uuid_dd5a04d0_146c_30d4_bf08_5551c02a714b, "client_room_player_rsp_cb_agree_join_room_err", _argv_dd5a04d0_146c_30d4_bf08_5551c02a714b);
        }

    }

    public class client_room_player_module : common.imodule {
        public client_room_player_module()
        {
            hub.hub._modules.add_mothed("client_room_player_create_room", create_room);
            hub.hub._modules.add_mothed("client_room_player_invite_role_join_room", invite_role_join_room);
            hub.hub._modules.add_mothed("client_room_player_agree_join_room", agree_join_room);
        }

        public event Action<playground> on_create_room;
        public void create_room(IList<MsgPack.MessagePackObject> inArray){
            var _cb_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var __playground = (playground)((MsgPack.MessagePackObject)inArray[1]).AsInt32();
            rsp = new client_room_player_create_room_rsp(hub.hub._gates.current_client_uuid, _cb_uuid);
            if (on_create_room != null){
                on_create_room(__playground);
            }
            rsp = null;
        }

        public event Action<string> on_invite_role_join_room;
        public void invite_role_join_room(IList<MsgPack.MessagePackObject> inArray){
            var _sdk_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsString();
            if (on_invite_role_join_room != null){
                on_invite_role_join_room(_sdk_uuid);
            }
        }

        public event Action<string> on_agree_join_room;
        public void agree_join_room(IList<MsgPack.MessagePackObject> inArray){
            var _cb_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _room_id = ((MsgPack.MessagePackObject)inArray[1]).AsString();
            rsp = new client_room_player_agree_join_room_rsp(hub.hub._gates.current_client_uuid, _cb_uuid);
            if (on_agree_join_room != null){
                on_agree_join_room(_room_id);
            }
            rsp = null;
        }

    }
    public class client_friend_lobby_find_role_rsp : common.Response {
        private string _client_uuid_ba126e3b_fd75_3aa1_a5be_1d096547ca8f;
        private UInt64 uuid_7cf098ce_38ef_30c0_b061_6a65be582555;
        public client_friend_lobby_find_role_rsp(string client_uuid, UInt64 _uuid)
        {
            _client_uuid_ba126e3b_fd75_3aa1_a5be_1d096547ca8f = client_uuid;
            uuid_7cf098ce_38ef_30c0_b061_6a65be582555 = _uuid;
        }

        public void rsp(player_friend_info find_info_90a9a99b_488a_39c4_8bbb_b8c5aed11cb2){
            var _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f = new ArrayList();
            _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f.Add(uuid_7cf098ce_38ef_30c0_b061_6a65be582555);
            _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f.Add(player_friend_info.player_friend_info_to_protcol(find_info_90a9a99b_488a_39c4_8bbb_b8c5aed11cb2));
            hub.hub._gates.call_client(_client_uuid_ba126e3b_fd75_3aa1_a5be_1d096547ca8f, "client_friend_lobby_rsp_cb_find_role_rsp", _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f);
        }

        public void err(Int32 err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696){
            var _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f = new ArrayList();
            _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f.Add(uuid_7cf098ce_38ef_30c0_b061_6a65be582555);
            _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f.Add(err_ad2710a2_3dd2_3a8f_a4c8_a7ebbe1df696);
            hub.hub._gates.call_client(_client_uuid_ba126e3b_fd75_3aa1_a5be_1d096547ca8f, "client_friend_lobby_rsp_cb_find_role_err", _argv_ba126e3b_fd75_3aa1_a5be_1d096547ca8f);
        }

    }

    public class client_friend_lobby_module : common.imodule {
        public client_friend_lobby_module()
        {
            hub.hub._modules.add_mothed("client_friend_lobby_find_role", find_role);
            hub.hub._modules.add_mothed("client_friend_lobby_invite_role_friend", invite_role_friend);
            hub.hub._modules.add_mothed("client_friend_lobby_agree_role_friend", agree_role_friend);
        }

        public event Action<Int64> on_find_role;
        public void find_role(IList<MsgPack.MessagePackObject> inArray){
            var _cb_uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _guid = ((MsgPack.MessagePackObject)inArray[1]).AsInt64();
            rsp = new client_friend_lobby_find_role_rsp(hub.hub._gates.current_client_uuid, _cb_uuid);
            if (on_find_role != null){
                on_find_role(_guid);
            }
            rsp = null;
        }

        public event Action<player_friend_info, player_friend_info> on_invite_role_friend;
        public void invite_role_friend(IList<MsgPack.MessagePackObject> inArray){
            var _self_info = player_friend_info.protcol_to_player_friend_info(((MsgPack.MessagePackObject)inArray[0]).AsDictionary());
            var _target_info = player_friend_info.protcol_to_player_friend_info(((MsgPack.MessagePackObject)inArray[1]).AsDictionary());
            if (on_invite_role_friend != null){
                on_invite_role_friend(_self_info, _target_info);
            }
        }

        public event Action<Int64, bool> on_agree_role_friend;
        public void agree_role_friend(IList<MsgPack.MessagePackObject> inArray){
            var _invite_guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            var _be_agree = ((MsgPack.MessagePackObject)inArray[1]).AsBoolean();
            if (on_agree_role_friend != null){
                on_agree_role_friend(_invite_guid, _be_agree);
            }
        }

    }

}
