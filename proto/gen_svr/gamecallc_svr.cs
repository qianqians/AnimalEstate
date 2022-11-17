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
    public class game_client_rsp_cb : common.imodule {
        public game_client_rsp_cb() 
        {
        }

    }

    public class game_client_clientproxy {
        public string client_uuid_b99eae25_99b5_3006_b19c_ccf531aff983;
        private Int64 uuid_b99eae25_99b5_3006_b19c_ccf531aff983 = (Int64)RandomUUID.random();

        public game_client_rsp_cb rsp_cb_game_client_handle;

        public game_client_clientproxy(game_client_rsp_cb rsp_cb_game_client_handle_)
        {
            rsp_cb_game_client_handle = rsp_cb_game_client_handle_;
        }

        public void move(Int32 from, Int32 to){
            var _argv_33efb72e_9227_32af_a058_169be114a277 = new ArrayList();
            _argv_33efb72e_9227_32af_a058_169be114a277.Add(from);
            _argv_33efb72e_9227_32af_a058_169be114a277.Add(to);
            hub.hub._gates.call_client(client_uuid_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_move", _argv_33efb72e_9227_32af_a058_169be114a277);
        }

    }

    public class game_client_multicast {
        public List<string> client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983;
        public game_client_rsp_cb rsp_cb_game_client_handle;

        public game_client_multicast(game_client_rsp_cb rsp_cb_game_client_handle_)
        {
            rsp_cb_game_client_handle = rsp_cb_game_client_handle_;
        }

    }

    public class game_client_broadcast {
        public game_client_rsp_cb rsp_cb_game_client_handle;

        public game_client_broadcast(game_client_rsp_cb rsp_cb_game_client_handle_)
        {
            rsp_cb_game_client_handle = rsp_cb_game_client_handle_;
        }

    }

    public class game_client_caller {
        public static game_client_rsp_cb rsp_cb_game_client_handle = null;
        private game_client_clientproxy _clientproxy;
        private game_client_multicast _multicast;
        private game_client_broadcast _broadcast;

        public game_client_caller() 
        {
            if (rsp_cb_game_client_handle == null)
            {
                rsp_cb_game_client_handle = new game_client_rsp_cb();
            }

            _clientproxy = new game_client_clientproxy(rsp_cb_game_client_handle);
            _multicast = new game_client_multicast(rsp_cb_game_client_handle);
            _broadcast = new game_client_broadcast(rsp_cb_game_client_handle);
        }

        public game_client_clientproxy get_client(string client_uuid) {
            _clientproxy.client_uuid_b99eae25_99b5_3006_b19c_ccf531aff983 = client_uuid;
            return _clientproxy;
        }

        public game_client_multicast get_multicast(List<string> client_uuids) {
            _multicast.client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983 = client_uuids;
            return _multicast;
        }

        public game_client_broadcast get_broadcast() {
            return _broadcast;
        }
    }


}
