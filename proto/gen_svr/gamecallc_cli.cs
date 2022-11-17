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
    public class game_client_module : common.imodule {
        public client.client _client_handle;
        public game_client_module(client.client client_handle_) 
        {
            _client_handle = client_handle_;
            _client_handle.modulemanager.add_mothed("game_client_move", move);
        }

        public event Action<Int32, Int32> on_move;
        public void move(IList<MsgPack.MessagePackObject> inArray){
            var _from = ((MsgPack.MessagePackObject)inArray[0]).AsInt32();
            var _to = ((MsgPack.MessagePackObject)inArray[1]).AsInt32();
            if (on_move != null){
                on_move(_from, _to);
            }
        }

    }

}
