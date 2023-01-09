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
    public class client_room_match_rsp_cb : common.imodule {
        public client_room_match_rsp_cb(common.modulemanager modules)
        {
        }

    }

    public class client_room_match_caller {
        public static client_room_match_rsp_cb rsp_cb_client_room_match_handle = null;
        private client_room_match_hubproxy _hubproxy;
        public client_room_match_caller(client.client _client_handle) 
        {
            if (rsp_cb_client_room_match_handle == null)
            {
                rsp_cb_client_room_match_handle = new client_room_match_rsp_cb(_client_handle.modulemanager);
            }

            _hubproxy = new client_room_match_hubproxy(_client_handle, rsp_cb_client_room_match_handle);
        }

        public client_room_match_hubproxy get_hub(string hub_name)
        {
            _hubproxy.hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f = hub_name;
            return _hubproxy;
        }

    }

    public class client_room_match_hubproxy {
        public string hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f;
        private Int32 uuid_b5f3fac6_a396_3fba_b454_dfa0635d459f = (Int32)RandomUUID.random();

        public client.client _client_handle;
        public client_room_match_rsp_cb rsp_cb_client_room_match_handle;

        public client_room_match_hubproxy(client.client client_handle_, client_room_match_rsp_cb rsp_cb_client_room_match_handle_)
        {
            _client_handle = client_handle_;
            rsp_cb_client_room_match_handle = rsp_cb_client_room_match_handle_;
        }

        public void into_room(){
            var _argv_98a2a5aa_24ec_3da8_9e3a_6f538c18f72e = new ArrayList();
            _client_handle.call_hub(hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f, "client_room_match_into_room", _argv_98a2a5aa_24ec_3da8_9e3a_6f538c18f72e);
        }

        public void chat(string chat_str){
            var _argv_963291b4_683e_3905_b8fb_55e87bd3c071 = new ArrayList();
            _argv_963291b4_683e_3905_b8fb_55e87bd3c071.Add(chat_str);
            _client_handle.call_hub(hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f, "client_room_match_chat", _argv_963291b4_683e_3905_b8fb_55e87bd3c071);
        }

        public void leave_room(){
            var _argv_382a8a22_f4e3_3394_8ae3_d355baaef1ac = new ArrayList();
            _client_handle.call_hub(hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f, "client_room_match_leave_room", _argv_382a8a22_f4e3_3394_8ae3_d355baaef1ac);
        }

        public void kick_out(Int64 player_guid){
            var _argv_316c421a_7e25_3ef2_86d6_1c294eb65792 = new ArrayList();
            _argv_316c421a_7e25_3ef2_86d6_1c294eb65792.Add(player_guid);
            _client_handle.call_hub(hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f, "client_room_match_kick_out", _argv_316c421a_7e25_3ef2_86d6_1c294eb65792);
        }

        public void disband(){
            var _argv_61e085ae_c852_39f0_82bf_61120861bcdd = new ArrayList();
            _client_handle.call_hub(hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f, "client_room_match_disband", _argv_61e085ae_c852_39f0_82bf_61120861bcdd);
        }

        public void start_match(){
            var _argv_5d1645a8_78f1_3219_bb7e_d14f420c9e1d = new ArrayList();
            _client_handle.call_hub(hub_name_b5f3fac6_a396_3fba_b454_dfa0635d459f, "client_room_match_start_match", _argv_5d1645a8_78f1_3219_bb7e_d14f420c9e1d);
        }

    }

}
