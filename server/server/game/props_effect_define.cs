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
        
        private List<props> step_lotus_props_define = new() {
            props.clip,
            props.landmine,
            props.spring
        };

        private bool already_has_props_grid(short pos)
        {
            foreach (var _props_info in props_list)
            {
                if (_props_info.grid_pos == pos)
                {
                    return true;
                }
            }
            return false;
        }

        public void check_randmon_step_lotus_props(short pos)
        {
            if (already_has_props_grid(pos))
            {
                return;
            }

            var r = hub.hub.randmon_uint(3);
            if (r < 1)
            {
                var props_id = step_lotus_props_define[(int)hub.hub.randmon_uint((uint)step_lotus_props_define.Count)];

                var _props_info = new props_info();
                _props_info.props_id = props_id;
                _props_info.grid_pos = pos;
                props_list.Add(_props_info);

                _game_client_caller.get_multicast(ClientUUIDS).ntf_new_props_info(_props_info);
            }
        }

        public void check_props_effect(client_proxy _client)
        {
            foreach (var _effect_info in effect_list)
            {
                if (_effect_info.grids.Contains(_client.PlayerGameInfo.animal_info[_client.PlayerGameInfo.current_animal_index].current_pos))
                {
                    switch (_effect_info.effect_id)
                    {
                        case effect.muddy:
                            {
                                var _effect = new client_proxy.special_grid_effect();
                                _effect.move_coefficient = 0.67f;
                                _effect.continued_rounds = 1;
                                _client.add_special_grid_effect(_effect);
                            }
                            break;

                        case effect.banana_peel:
                            {
                                var from = _client.PlayerGameInfo.animal_info[_client.PlayerGameInfo.current_animal_index].current_pos;
                                var to = 0;
                                if (hub.hub.randmon_uint(2) < 1)
                                {
                                    to = from + 3;
                                }
                                else
                                {
                                    to = from - 3;
                                }
                                _game_client_caller.get_multicast(ClientUUIDS).effect_move(_client.PlayerGameInfo.guid, effect.banana_peel, from, to);
                            }
                            break;

                        case effect.golden_apple:
                            {
                                var _effect = new client_proxy.special_grid_effect();
                                _effect.mutil_rounds = 2;
                                _effect.continued_rounds = 3;
                                _effect.stop_rounds = 1;
                                _client.add_special_grid_effect(_effect);
                            }
                            break;

                        case effect.rice_ear:
                            {
                                var _effect = new client_proxy.special_grid_effect();
                                _effect.move_coefficient = 2;
                                _effect.continued_rounds = 3;
                                _client.add_special_grid_effect(_effect);
                            }
                            break;

                        case effect.monkey_wine:
                            {
                                var _effect = new client_proxy.special_grid_effect();
                                _effect.stop_rounds = 1;
                                _client.add_special_grid_effect(_effect);
                            }
                            break;

                        default:
                            break;
                    }

                    effect_list.Remove(_effect_info);
                    break;
                }
            }
        }
    }
}
