using abelkhan;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Security.Principal;

namespace game
{
    partial class game_impl
    {
        private List<props> props_define = new () {
            props.horn,
            props.bomb,
            props.help_vellus,
            props.thunder,
            props.clown_gift_box,
            props.excited_petals,
            props.clip,
            props.landmine,
            props.spring,
            props.turtle_shell,
            props.banana,
            props.watermelon_rind,
            props.red_mushroom,
            props.gacha,
            props.fake_dice
        };
        
        private List<effect> step_lotus_effect_define = new() {
            effect.clip,
            effect.landmine,
            effect.spring
        };

        public void check_randmon_step_lotus_props(short pos)
        {
            if (already_has_effect_grid(pos))
            {
                return;
            }

            var r = hub.hub.randmon_uint(3);
            if (r < 1)
            {
                var effect_id = step_lotus_effect_define[(int)hub.hub.randmon_uint((uint)step_lotus_effect_define.Count)];

                var _props_info = new effect_info();
                _props_info.effect_id = effect_id;
                _props_info.grids = new ();
                _props_info.grids.Add(pos);
                effect_list.Add(_props_info);

                _game_client_caller.get_multicast(ClientUUIDS).ntf_new_effect_info(_props_info);
            }
        }
        

    }
}
