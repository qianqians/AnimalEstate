using abelkhan;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Security.Principal;

namespace game
{
    partial class game_impl
    {
        private List<effect> effects_define = new () { effect.muddy, effect.golden_apple, effect.rice_ear, effect.golden_apple, effect.rice_ear, effect.golden_apple, effect.rice_ear, effect.monkey_wine };

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
            if (game_rounds < 6)
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
                    _effect_info.continued_rounds = int.MaxValue;
                }
                effect_list.Add(_effect_info);

                _game_client_caller.get_multicast(ClientUUIDS).ntf_new_effect_info(_effect_info);
            }
        }

        public bool check_grid_effect(client_proxy _client, int _from, int _to)
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

                        case effect.golden_apple:
                            {
                                var _effect = new client_proxy.special_grid_effect();
                                _effect.mutil_rounds = 2;
                                _effect.continued_rounds = 3;
                                _effect.stop_rounds = 1;
                                _client.add_special_grid_effect(_effect);

                                effect_list.Remove(_effect_info);
                            }
                            break;

                        case effect.rice_ear:
                            {
                                var _effect = new client_proxy.special_grid_effect();
                                _effect.move_coefficient = 2;
                                _effect.continued_rounds = 3;
                                _client.add_special_grid_effect(_effect);

                                effect_list.Remove(_effect_info);
                            }
                            break;

                        case effect.monkey_wine:
                            {
                                var _effect = new client_proxy.special_grid_effect();
                                _effect.stop_rounds = 1;
                                _client.add_special_grid_effect(_effect);

                                effect_list.Remove(_effect_info);
                            }
                            break;

                        case effect.clip:
                            {
                                var _animal = _client.PlayerGameInfo.animal_info[_client.PlayerGameInfo.current_animal_index];
                                _animal.could_move = false;
                                _animal.unmovable_rounds = 1;

                                effect_list.Remove(_effect_info);
                            }
                            break;

                        case effect.landmine:
                            {
                                var _animal = _client.PlayerGameInfo.animal_info[_client.PlayerGameInfo.current_animal_index];
                                int from = _animal.current_pos;
                                int to = from - 4;
                                if (to < 0)
                                {
                                    to = 0;
                                }
                                _animal.current_pos = (short)to;
                                ntf_effect_move(effect.landmine, _client.PlayerGameInfo.guid, _client.PlayerGameInfo.current_animal_index, from, to);

                                effect_list.Remove(_effect_info);
                            }
                            break;

                        case effect.spring:
                            {
                                int from = _to;
                                int to = _from;
                                var _animal = _client.PlayerGameInfo.animal_info[_client.PlayerGameInfo.current_animal_index];
                                _animal.current_pos = (short)to;
                                ntf_effect_move(effect.spring, _client.PlayerGameInfo.guid, _client.PlayerGameInfo.current_animal_index, from, to);

                                effect_list.Remove(_effect_info);
                            }
                            break;

                        case effect.watermelon_rind:
                            {
                                var _animal = _client.PlayerGameInfo.animal_info[_client.PlayerGameInfo.current_animal_index];
                                int from = _animal.current_pos;
                                int to;
                                if (hub.hub.randmon_uint(2) < 1)
                                {
                                    to = from + 3;
                                }
                                else
                                {
                                    to = from - 3;
                                    if (to < 0)
                                    {
                                        to = 0;
                                    }
                                }
                                _animal.current_pos = (short)to;
                                ntf_effect_move(effect.watermelon_rind, _client.PlayerGameInfo.guid, _client.PlayerGameInfo.current_animal_index, from, to);

                                effect_list.Remove(_effect_info);
                            }
                            break;

                        default:
                            break;
                    }

                    return true;
                }
            }

            return false;
        }
    }
}
