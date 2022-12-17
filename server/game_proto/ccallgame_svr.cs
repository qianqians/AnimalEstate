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
            hub.hub._modules.add_mothed("game_play_order", play_order);
            hub.hub._modules.add_mothed("game_use_skill", use_skill);
            hub.hub._modules.add_mothed("game_use_props", use_props);
            hub.hub._modules.add_mothed("game_throw_dice", throw_dice);
        }

        public event Action<Int64> on_into_game;
        public void into_game(IList<MsgPack.MessagePackObject> inArray){
            var _guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            if (on_into_game != null){
                on_into_game(_guid);
            }
        }

        public event Action<List<animal_game_info>> on_play_order;
        public void play_order(IList<MsgPack.MessagePackObject> inArray){
            var _animal_info = new List<animal_game_info>();
            var _protocol_arrayanimal_info = ((MsgPack.MessagePackObject)inArray[0]).AsList();
            foreach (var v_c00062dc_edff_54ff_a6ff_4b3c0f329e98 in _protocol_arrayanimal_info){
                _animal_info.Add(animal_game_info.protcol_to_animal_game_info(((MsgPack.MessagePackObject)v_c00062dc_edff_54ff_a6ff_4b3c0f329e98).AsDictionary()));
            }
            if (on_play_order != null){
                on_play_order(_animal_info);
            }
        }

        public event Action<Int64, Int16> on_use_skill;
        public void use_skill(IList<MsgPack.MessagePackObject> inArray){
            var _target_guid = ((MsgPack.MessagePackObject)inArray[0]).AsInt64();
            var _target_animal_index = ((MsgPack.MessagePackObject)inArray[1]).AsInt16();
            if (on_use_skill != null){
                on_use_skill(_target_guid, _target_animal_index);
            }
        }

        public event Action<props, Int64, Int16> on_use_props;
        public void use_props(IList<MsgPack.MessagePackObject> inArray){
            var _props_id = (props)((MsgPack.MessagePackObject)inArray[0]).AsInt32();
            var _target_guid = ((MsgPack.MessagePackObject)inArray[1]).AsInt64();
            var _target_animal_index = ((MsgPack.MessagePackObject)inArray[2]).AsInt16();
            if (on_use_props != null){
                on_use_props(_props_id, _target_guid, _target_animal_index);
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
