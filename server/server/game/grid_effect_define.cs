using abelkhan;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Security.Principal;

namespace game
{
    partial class game_impl
    {
        private List<effect> effects_define = new () { effect.muddy, effect.banana_peel, effect.golden_apple, effect.rice_ear, effect.monkey_wine };

        private int wait_game_rounds = 0;

        private bool already_has_effect_grid(short pos)
        {
            foreach (var _effect_info in effect_list)
            {
                if (_effect_info.grids.Contains(pos))
                {
                    return true;
                }
            }
            return false;
        }

        public void check_randmon_effect()
        {
            if (wait_game_rounds < 6)
            {
                return;
            }

            var r = hub.hub.randmon_uint(2);
            if (r < 1)
            {
                var _effect = effects_define[(int)hub.hub.randmon_uint((uint)effects_define.Count)];

                var _effect_info = new effect_info();
                _effect_info.effect_id = _effect;
                _effect_info.grids = new List<short>();

                var pos = hub.hub.randmon_uint((uint)PlayergroundLenght);
                while (already_has_effect_grid((short)pos))
                {
                    pos = hub.hub.randmon_uint((uint)PlayergroundLenght);
                }

                if (_effect == effect.muddy)
                {
                    var len = hub.hub.randmon_uint(3) + 3;
                    for (int i = 0; i < len; i++)
                    {
                        var grid_pos = pos + i;
                        if (grid_pos > PlayergroundLenght)
                        {
                            grid_pos -= PlayergroundLenght;
                        }
                        _effect_info.grids.Add((short)grid_pos);
                    }
                    _effect_info.continued_rounds = 3;
                }
                else
                {
                    _effect_info.grids.Add((short)pos);
                }
                effect_list.Add(_effect_info);

                _game_client_caller.get_multicast(ClientUUIDS).ntf_new_effect_info(_effect_info);
            }
        }

        public void check_grid_effect(client_proxy _client)
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

                        case effect.mouse_trap:
                            {
                                var _effect = new client_proxy.special_grid_effect();
                                _effect.stop_rounds = 3;
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
