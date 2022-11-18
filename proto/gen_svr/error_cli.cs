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
        server_busy = 1,
        unregistered_palyer = 2
    }
/*this struct code is codegen by abelkhan codegen for c#*/
/*this module code is codegen by abelkhan codegen for c#*/
    public class error_code_ntf_module : common.imodule {
        public client.client _client_handle;
        public error_code_ntf_module(client.client client_handle_) 
        {
            _client_handle = client_handle_;
            _client_handle.modulemanager.add_mothed("error_code_ntf_error_code", error_code);
        }

        public event Action<error> on_error_code;
        public void error_code(IList<MsgPack.MessagePackObject> inArray){
            var _err_code = (error)((MsgPack.MessagePackObject)inArray[0]).AsInt32();
            if (on_error_code != null){
                on_error_code(_err_code);
            }
        }

    }

}
