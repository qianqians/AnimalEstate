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
        invalid_team = 2,
        not_leader = 3,
        more_team_members = 4,
        in_game = 5,
        not_in_match = 6,
        wait_into_game = 7,
        is_in_match = 8,
        is_ready = 9,
        not_all_ready = 10,
        drop_box_too_far = 11,
        invalid_drop_box = 12,
        box_is_occupied = 13,
        not_open_drop_box = 14,
        drop_box_not_have_this_item = 15,
        invalid_drop_team = 16,
        not_at_door = 17,
        battle_is_end = 18,
        team_is_full = 19,
        invalid_role = 20
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

        public event Action<Int32> on_error_code;
        public void error_code(IList<MsgPack.MessagePackObject> inArray){
            var _error = ((MsgPack.MessagePackObject)inArray[0]).AsInt32();
            if (on_error_code != null){
                on_error_code(_error);
            }
        }

    }

}
