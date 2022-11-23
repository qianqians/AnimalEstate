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
    public class room_client_rsp_cb : common.imodule {
        public room_client_rsp_cb() 
        {
        }

    }

    public class room_client_clientproxy {
        public string client_uuid_59b7c252_c008_342a_8082_3977be609704;
        private Int64 uuid_59b7c252_c008_342a_8082_3977be609704 = (Int64)RandomUUID.random();

        public room_client_rsp_cb rsp_cb_room_client_handle;

        public room_client_clientproxy(room_client_rsp_cb rsp_cb_room_client_handle_)
        {
            rsp_cb_room_client_handle = rsp_cb_room_client_handle_;
        }

        public void player_leave_room_success(){
            var _argv_071b8841_4091_310f_9b36_42379d140d35 = new ArrayList();
            hub.hub._gates.call_client(client_uuid_59b7c252_c008_342a_8082_3977be609704, "room_client_player_leave_room_success", _argv_071b8841_4091_310f_9b36_42379d140d35);
        }

        public void be_kicked(){
            var _argv_2616b459_0117_393c_86a2_1eec5764c007 = new ArrayList();
            hub.hub._gates.call_client(client_uuid_59b7c252_c008_342a_8082_3977be609704, "room_client_be_kicked", _argv_2616b459_0117_393c_86a2_1eec5764c007);
        }

    }

    public class room_client_multicast {
        public List<string> client_uuids_59b7c252_c008_342a_8082_3977be609704;
        public room_client_rsp_cb rsp_cb_room_client_handle;

        public room_client_multicast(room_client_rsp_cb rsp_cb_room_client_handle_)
        {
            rsp_cb_room_client_handle = rsp_cb_room_client_handle_;
        }

        public void refresh_room_info(room_info info){
            var _argv_0cd0a647_e950_33ea_aaee_78e393454cf7 = new ArrayList();
            _argv_0cd0a647_e950_33ea_aaee_78e393454cf7.Add(room_info.room_info_to_protcol(info));
            hub.hub._gates.call_group_client(client_uuids_59b7c252_c008_342a_8082_3977be609704, "room_client_refresh_room_info", _argv_0cd0a647_e950_33ea_aaee_78e393454cf7);
        }

        public void transfer_refresh_room_info(string room_hub_name, room_info info){
            var _argv_ab6777d0_e79b_31c0_93a6_6626bdcf6426 = new ArrayList();
            _argv_ab6777d0_e79b_31c0_93a6_6626bdcf6426.Add(room_hub_name);
            _argv_ab6777d0_e79b_31c0_93a6_6626bdcf6426.Add(room_info.room_info_to_protcol(info));
            hub.hub._gates.call_group_client(client_uuids_59b7c252_c008_342a_8082_3977be609704, "room_client_transfer_refresh_room_info", _argv_ab6777d0_e79b_31c0_93a6_6626bdcf6426);
        }

        public void chat(Int64 chat_player_guid, string chat_str){
            var _argv_963291b4_683e_3905_b8fb_55e87bd3c071 = new ArrayList();
            _argv_963291b4_683e_3905_b8fb_55e87bd3c071.Add(chat_player_guid);
            _argv_963291b4_683e_3905_b8fb_55e87bd3c071.Add(chat_str);
            hub.hub._gates.call_group_client(client_uuids_59b7c252_c008_342a_8082_3977be609704, "room_client_chat", _argv_963291b4_683e_3905_b8fb_55e87bd3c071);
        }

        public void room_is_free(){
            var _argv_0c336ab9_922c_355b_ad95_eeb4e4b20ed0 = new ArrayList();
            hub.hub._gates.call_group_client(client_uuids_59b7c252_c008_342a_8082_3977be609704, "room_client_room_is_free", _argv_0c336ab9_922c_355b_ad95_eeb4e4b20ed0);
        }

        public void team_into_match(){
            var _argv_5b55326f_4ad9_3e5e_ac7a_53955a3768f7 = new ArrayList();
            hub.hub._gates.call_group_client(client_uuids_59b7c252_c008_342a_8082_3977be609704, "room_client_team_into_match", _argv_5b55326f_4ad9_3e5e_ac7a_53955a3768f7);
        }

    }

    public class room_client_broadcast {
        public room_client_rsp_cb rsp_cb_room_client_handle;

        public room_client_broadcast(room_client_rsp_cb rsp_cb_room_client_handle_)
        {
            rsp_cb_room_client_handle = rsp_cb_room_client_handle_;
        }

    }

    public class room_client_caller {
        public static room_client_rsp_cb rsp_cb_room_client_handle = null;
        private room_client_clientproxy _clientproxy;
        private room_client_multicast _multicast;
        private room_client_broadcast _broadcast;

        public room_client_caller() 
        {
            if (rsp_cb_room_client_handle == null)
            {
                rsp_cb_room_client_handle = new room_client_rsp_cb();
            }

            _clientproxy = new room_client_clientproxy(rsp_cb_room_client_handle);
            _multicast = new room_client_multicast(rsp_cb_room_client_handle);
            _broadcast = new room_client_broadcast(rsp_cb_room_client_handle);
        }

        public room_client_clientproxy get_client(string client_uuid) {
            _clientproxy.client_uuid_59b7c252_c008_342a_8082_3977be609704 = client_uuid;
            return _clientproxy;
        }

        public room_client_multicast get_multicast(List<string> client_uuids) {
            _multicast.client_uuids_59b7c252_c008_342a_8082_3977be609704 = client_uuids;
            return _multicast;
        }

        public room_client_broadcast get_broadcast() {
            return _broadcast;
        }
    }

/*this cb code is codegen by abelkhan for c#*/
    public class room_match_client_rsp_cb : common.imodule {
        public room_match_client_rsp_cb() 
        {
        }

    }

    public class room_match_client_clientproxy {
        public string client_uuid_28b7d582_d434_32f8_bd83_6eff7f90caa7;
        private Int64 uuid_28b7d582_d434_32f8_bd83_6eff7f90caa7 = (Int64)RandomUUID.random();

        public room_match_client_rsp_cb rsp_cb_room_match_client_handle;

        public room_match_client_clientproxy(room_match_client_rsp_cb rsp_cb_room_match_client_handle_)
        {
            rsp_cb_room_match_client_handle = rsp_cb_room_match_client_handle_;
        }

        public void role_into_game(string game_hub_name){
            var _argv_59c21bb2_715b_3560_87c4_55cca030071b = new ArrayList();
            _argv_59c21bb2_715b_3560_87c4_55cca030071b.Add(game_hub_name);
            hub.hub._gates.call_client(client_uuid_28b7d582_d434_32f8_bd83_6eff7f90caa7, "room_match_client_role_into_game", _argv_59c21bb2_715b_3560_87c4_55cca030071b);
        }

    }

    public class room_match_client_multicast {
        public List<string> client_uuids_28b7d582_d434_32f8_bd83_6eff7f90caa7;
        public room_match_client_rsp_cb rsp_cb_room_match_client_handle;

        public room_match_client_multicast(room_match_client_rsp_cb rsp_cb_room_match_client_handle_)
        {
            rsp_cb_room_match_client_handle = rsp_cb_room_match_client_handle_;
        }

    }

    public class room_match_client_broadcast {
        public room_match_client_rsp_cb rsp_cb_room_match_client_handle;

        public room_match_client_broadcast(room_match_client_rsp_cb rsp_cb_room_match_client_handle_)
        {
            rsp_cb_room_match_client_handle = rsp_cb_room_match_client_handle_;
        }

    }

    public class room_match_client_caller {
        public static room_match_client_rsp_cb rsp_cb_room_match_client_handle = null;
        private room_match_client_clientproxy _clientproxy;
        private room_match_client_multicast _multicast;
        private room_match_client_broadcast _broadcast;

        public room_match_client_caller() 
        {
            if (rsp_cb_room_match_client_handle == null)
            {
                rsp_cb_room_match_client_handle = new room_match_client_rsp_cb();
            }

            _clientproxy = new room_match_client_clientproxy(rsp_cb_room_match_client_handle);
            _multicast = new room_match_client_multicast(rsp_cb_room_match_client_handle);
            _broadcast = new room_match_client_broadcast(rsp_cb_room_match_client_handle);
        }

        public room_match_client_clientproxy get_client(string client_uuid) {
            _clientproxy.client_uuid_28b7d582_d434_32f8_bd83_6eff7f90caa7 = client_uuid;
            return _clientproxy;
        }

        public room_match_client_multicast get_multicast(List<string> client_uuids) {
            _multicast.client_uuids_28b7d582_d434_32f8_bd83_6eff7f90caa7 = client_uuids;
            return _multicast;
        }

        public room_match_client_broadcast get_broadcast() {
            return _broadcast;
        }
    }


}
