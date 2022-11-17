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
    public class client_room_match_module : common.imodule {
        public client_room_match_module()
        {
            hub.hub._modules.add_mothed("client_room_match_into_room", into_room);
            hub.hub._modules.add_mothed("client_room_match_chat", chat);
            hub.hub._modules.add_mothed("client_room_match_leave_room", leave_room);
            hub.hub._modules.add_mothed("client_room_match_kick_out", kick_out);
            hub.hub._modules.add_mothed("client_room_match_disband", disband);
            hub.hub._modules.add_mothed("client_room_match_start_match", start_match);
        }

        public event Action on_into_room;
        public void into_room(IList<MsgPack.MessagePackObject> inArray){
            if (on_into_room != null){
                on_into_room();
            }
        }

        public event Action<string> on_chat;
        public void chat(IList<MsgPack.MessagePackObject> inArray){
            var _chat_str = ((MsgPack.MessagePackObject)inArray[0]).AsString();
            if (on_chat != null){
                on_chat(_chat_str);
            }
        }

        public event Action on_leave_room;
        public void leave_room(IList<MsgPack.MessagePackObject> inArray){
            if (on_leave_room != null){
                on_leave_room();
            }
        }

        public event Action<Int64> on_kick_out;
        public void kick_out(IList<MsgPack.MessagePackObject> inArray){
            var _player_guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            if (on_kick_out != null){
                on_kick_out(_player_guid);
            }
        }

        public event Action on_disband;
        public void disband(IList<MsgPack.MessagePackObject> inArray){
            if (on_disband != null){
                on_disband();
            }
        }

        public event Action on_start_match;
        public void start_match(IList<MsgPack.MessagePackObject> inArray){
            if (on_start_match != null){
                on_start_match();
            }
        }

    }

}
