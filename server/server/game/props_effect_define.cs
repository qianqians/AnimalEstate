using abelkhan;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Security.Principal;

namespace game
{
    partial class game_impl
    {
        private List<props> props_define = new() {
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
                _props_info.grids = new();
                _props_info.grids.Add(pos);
                effect_list.Add(_props_info);

                _game_client_caller.get_multicast(ClientUUIDS).ntf_new_effect_info(_props_info);
            }
        }
    }

    partial class client_proxy
    {
        private void horn_props(long target_client_guid, short target_animal_index)
        {
            var target_client = _impl.get_client_proxy(target_client_guid);

            target_client.skill_Effects.Add(new()
            {
                 skill_state = enum_skill_state.em_move_halved,
                 continued_rounds = 2,
            });

            _impl.ntf_player_use_props(_game_info.guid, props.horn, target_client_guid, target_animal_index);
        }

        private void bomb_props(long target_client_guid, short target_animal_index)
        {
            var target_client = _impl.get_client_proxy(target_client_guid);
            var target_animal = target_client.PlayerGameInfo.animal_info[target_animal_index];

            target_animal.could_move = false;
            target_animal.unmovable_rounds = 2;

            _impl.ntf_player_use_props(_game_info.guid, props.bomb, target_client_guid, target_animal_index);
        }

        private void help_vellus_props(long target_client_guid, short target_animal_index)
        {
            skill_Effects.Add(new()
            {
                skill_state = enum_skill_state.em_immunity,
                continued_rounds = 3,
            });

            _impl.ntf_player_use_props(_game_info.guid, props.help_vellus, target_client_guid, target_animal_index);
        }

        private void thunder_props(long target_client_guid, short target_animal_index)
        {
            var targetClientList = new List<client_proxy>();
            foreach (var _client in _impl.ClientProxys)
            {
                if (_client != this)
                {
                    targetClientList.Add(_client);
                }
            }

            foreach (var target in targetClientList)
            {
                foreach(var _animal in target.PlayerGameInfo.animal_info)
                {
                    var from = _animal.current_pos;
                    _animal.current_pos -= 3;
                    if (_animal.current_pos < 0)
                    {
                        _animal.current_pos = 0;
                    }
                    var to = _animal.current_pos;
                    _impl.ntf_effect_move(effect.landmine, _client.PlayerGameInfo.guid, _client.PlayerGameInfo.current_animal_index, from, to);
                }
            }
        }
    }
}
