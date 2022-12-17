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
    public class game_rsp_cb : common.imodule {
        public game_rsp_cb(common.modulemanager modules)
        {
        }

    }

    public class game_caller {
        public static game_rsp_cb rsp_cb_game_handle = null;
        private game_hubproxy _hubproxy;
        public game_caller(client.client _client_handle) 
        {
            if (rsp_cb_game_handle == null)
            {
                rsp_cb_game_handle = new game_rsp_cb(_client_handle.modulemanager);
            }

            _hubproxy = new game_hubproxy(_client_handle, rsp_cb_game_handle);
        }

        public game_hubproxy get_hub(string hub_name)
        {
            _hubproxy.hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47 = hub_name;
            return _hubproxy;
        }

    }

    public class game_hubproxy {
        public string hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47;
        private Int64 uuid_b8b9723b_52d5_3bc2_8583_8bf5fd51de47 = (Int64)RandomUUID.random();

        public client.client _client_handle;
        public game_rsp_cb rsp_cb_game_handle;

        public game_hubproxy(client.client client_handle_, game_rsp_cb rsp_cb_game_handle_)
        {
            _client_handle = client_handle_;
            rsp_cb_game_handle = rsp_cb_game_handle_;
        }

        public void into_game(Int64 guid){
            var _argv_90a69cb9_3a0a_3a86_9cad_499708905276 = new ArrayList();
            _argv_90a69cb9_3a0a_3a86_9cad_499708905276.Add(guid);
            _client_handle.call_hub(hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47, "game_into_game", _argv_90a69cb9_3a0a_3a86_9cad_499708905276);
        }

        public void play_order(List<animal_game_info> animal_info){
            var _argv_72cd38c4_f976_3ca7_aeef_12b6fc619413 = new ArrayList();
            var _array_7044f738_3b40_35d1_a737_b6b236adbdd2 = new ArrayList();
            foreach(var v_6dc408dd_fea4_5767_a896_5cfbe6a4974f in animal_info){
                _array_7044f738_3b40_35d1_a737_b6b236adbdd2.Add(animal_game_info.animal_game_info_to_protcol(v_6dc408dd_fea4_5767_a896_5cfbe6a4974f));
            }
            _argv_72cd38c4_f976_3ca7_aeef_12b6fc619413.Add(_array_7044f738_3b40_35d1_a737_b6b236adbdd2);
            _client_handle.call_hub(hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47, "game_play_order", _argv_72cd38c4_f976_3ca7_aeef_12b6fc619413);
        }

        public void use_skill(Int64 target_guid, Int16 target_animal_index){
            var _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe = new ArrayList();
            _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe.Add(target_guid);
            _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe.Add(target_animal_index);
            _client_handle.call_hub(hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47, "game_use_skill", _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe);
        }

        public void use_props(props props_id, Int64 target_guid, Int16 target_animal_index){
            var _argv_20fdd6aa_1127_36f5_b101_2ce394d2e1c9 = new ArrayList();
            _argv_20fdd6aa_1127_36f5_b101_2ce394d2e1c9.Add((int)props_id);
            _argv_20fdd6aa_1127_36f5_b101_2ce394d2e1c9.Add(target_guid);
            _argv_20fdd6aa_1127_36f5_b101_2ce394d2e1c9.Add(target_animal_index);
            _client_handle.call_hub(hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47, "game_use_props", _argv_20fdd6aa_1127_36f5_b101_2ce394d2e1c9);
        }

        public void throw_dice(){
            var _argv_89caa8aa_910b_3726_9283_63467ea68426 = new ArrayList();
            _client_handle.call_hub(hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47, "game_throw_dice", _argv_89caa8aa_910b_3726_9283_63467ea68426);
        }

    }

}
