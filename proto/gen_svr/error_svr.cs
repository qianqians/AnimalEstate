using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using MsgPack.Serialization;

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for c#*/

    public enum error{
        timeout = -2,
        db_error = -1,
        success = 0,
        server_busy = 1
    }
/*this struct code is codegen by abelkhan codegen for c#*/
/*this caller code is codegen by abelkhan codegen for c#*/
/*this cb code is codegen by abelkhan for c#*/
    public class error_code_ntf_rsp_cb : common.imodule {
        public error_code_ntf_rsp_cb() 
        {
        }

    }

    public class error_code_ntf_clientproxy {
        public string client_uuid_f657c200_2a33_308f_b478_82cef68fbca2;
        private Int64 uuid_f657c200_2a33_308f_b478_82cef68fbca2 = (Int64)RandomUUID.random();

        public error_code_ntf_rsp_cb rsp_cb_error_code_ntf_handle;

        public error_code_ntf_clientproxy(error_code_ntf_rsp_cb rsp_cb_error_code_ntf_handle_)
        {
            rsp_cb_error_code_ntf_handle = rsp_cb_error_code_ntf_handle_;
        }

        public void error_code(error err_code){
            var _argv_b2890040_4e10_3967_a5ca_fac1ca306870 = new ArrayList();
            _argv_b2890040_4e10_3967_a5ca_fac1ca306870.Add(err_code);
            hub.hub._gates.call_client(client_uuid_f657c200_2a33_308f_b478_82cef68fbca2, "error_code_ntf_error_code", _argv_b2890040_4e10_3967_a5ca_fac1ca306870);
        }

    }

    public class error_code_ntf_multicast {
        public List<string> client_uuids_f657c200_2a33_308f_b478_82cef68fbca2;
        public error_code_ntf_rsp_cb rsp_cb_error_code_ntf_handle;

        public error_code_ntf_multicast(error_code_ntf_rsp_cb rsp_cb_error_code_ntf_handle_)
        {
            rsp_cb_error_code_ntf_handle = rsp_cb_error_code_ntf_handle_;
        }

    }

    public class error_code_ntf_broadcast {
        public error_code_ntf_rsp_cb rsp_cb_error_code_ntf_handle;

        public error_code_ntf_broadcast(error_code_ntf_rsp_cb rsp_cb_error_code_ntf_handle_)
        {
            rsp_cb_error_code_ntf_handle = rsp_cb_error_code_ntf_handle_;
        }

    }

    public class error_code_ntf_caller {
        public static error_code_ntf_rsp_cb rsp_cb_error_code_ntf_handle = null;
        private error_code_ntf_clientproxy _clientproxy;
        private error_code_ntf_multicast _multicast;
        private error_code_ntf_broadcast _broadcast;

        public error_code_ntf_caller() 
        {
            if (rsp_cb_error_code_ntf_handle == null)
            {
                rsp_cb_error_code_ntf_handle = new error_code_ntf_rsp_cb();
            }

            _clientproxy = new error_code_ntf_clientproxy(rsp_cb_error_code_ntf_handle);
            _multicast = new error_code_ntf_multicast(rsp_cb_error_code_ntf_handle);
            _broadcast = new error_code_ntf_broadcast(rsp_cb_error_code_ntf_handle);
        }

        public error_code_ntf_clientproxy get_client(string client_uuid) {
            _clientproxy.client_uuid_f657c200_2a33_308f_b478_82cef68fbca2 = client_uuid;
            return _clientproxy;
        }

        public error_code_ntf_multicast get_multicast(List<string> client_uuids) {
            _multicast.client_uuids_f657c200_2a33_308f_b478_82cef68fbca2 = client_uuids;
            return _multicast;
        }

        public error_code_ntf_broadcast get_broadcast() {
            return _broadcast;
        }
    }


}
