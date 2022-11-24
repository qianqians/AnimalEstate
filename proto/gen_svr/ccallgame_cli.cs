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

        public void into_game(){
            var _argv_90a69cb9_3a0a_3a86_9cad_499708905276 = new ArrayList();
            _client_handle.call_hub(hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47, "game_into_game", _argv_90a69cb9_3a0a_3a86_9cad_499708905276);
        }

        public void use_skill(){
            var _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe = new ArrayList();
            _client_handle.call_hub(hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47, "game_use_skill", _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe);
        }

        public void throw_dice(){
            var _argv_89caa8aa_910b_3726_9283_63467ea68426 = new ArrayList();
            _client_handle.call_hub(hub_name_b8b9723b_52d5_3bc2_8583_8bf5fd51de47, "game_throw_dice", _argv_89caa8aa_910b_3726_9283_63467ea68426);
        }

    }

}
