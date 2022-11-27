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
    public class game_module : common.imodule {
        public game_module()
        {
            hub.hub._modules.add_mothed("game_into_game", into_game);
            hub.hub._modules.add_mothed("game_use_skill", use_skill);
            hub.hub._modules.add_mothed("game_throw_dice", throw_dice);
        }

        public event Action<Int64> on_into_game;
        public void into_game(IList<MsgPack.MessagePackObject> inArray){
            var _guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            if (on_into_game != null){
                on_into_game(_guid);
            }
        }

        public event Action on_use_skill;
        public void use_skill(IList<MsgPack.MessagePackObject> inArray){
            if (on_use_skill != null){
                on_use_skill();
            }
        }

        public event Action on_throw_dice;
        public void throw_dice(IList<MsgPack.MessagePackObject> inArray){
            if (on_throw_dice != null){
                on_throw_dice();
            }
        }

    }

}
