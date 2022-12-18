using abelkhan;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Security.Principal;

namespace game
{
    partial class game_impl
    {
        public List<props> props_define = new() {
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
        private client_proxy random_props_target()
        {
            var targetClientList = new List<client_proxy>();
            foreach (var _client in _impl.ClientProxys)
            {
                if (_client != this)
                {
                    targetClientList.Add(_client);
                }
            }

            return targetClientList[(int)hub.hub.randmon_uint((uint)targetClientList.Count)];
        }

        private client_proxy randmon_reverse_props_target(client_proxy target)
        {
            var targetClientList = new List<client_proxy>();
            foreach (var _client in _impl.ClientProxys)
            {
                if (_client != this && _client != target)
                {
                    targetClientList.Add(_client);
                }
            }

            return targetClientList[(int)hub.hub.randmon_uint((uint)targetClientList.Count)];
        }

        private void horn_props(long target_client_guid, short target_animal_index)
        {
            var target_client = _impl.get_client_proxy(target_client_guid);

            if (target_client.reverse_props())
            {
                target_client = randmon_reverse_props_target(target_client);
                _impl.ntf_reverse_props(_game_info.guid, target_client_guid, props.horn, target_client.PlayerGameInfo.guid, target_client.PlayerGameInfo.current_animal_index);
            }
            else if (target_client.immunity_props())
            {
                _impl.ntf_immunity_props(_game_info.guid, props.horn, target_client_guid, target_animal_index);
                return;
            }
            else
            {
                _impl.ntf_player_use_props(_game_info.guid, props.horn, target_client_guid, target_animal_index);
            }

            target_client.skill_Effects.Add(new()
            {
                 skill_state = enum_skill_state.em_move_halved,
                 continued_rounds = 2,
            });
        }

        private void bomb_props(long target_client_guid, short target_animal_index)
        {
            var target_client = _impl.get_client_proxy(target_client_guid);
            var target_animal = target_client.PlayerGameInfo.animal_info[target_animal_index];

            if (target_client.reverse_props())
            {
                target_client = randmon_reverse_props_target(target_client);
                target_animal = target_client.PlayerGameInfo.animal_info[target_client.PlayerGameInfo.current_animal_index];
                _impl.ntf_reverse_props(_game_info.guid, target_client_guid, props.horn, target_client.PlayerGameInfo.guid, target_client.PlayerGameInfo.current_animal_index);
            }
            else if (target_client.immunity_props())
            {
                _impl.ntf_immunity_props(_game_info.guid, props.bomb, target_client_guid, target_animal_index);
                return;
            }
            else
            {
                _impl.ntf_player_use_props(_game_info.guid, props.bomb, target_client_guid, target_animal_index);
            }

            target_animal.could_move = false;
            target_animal.unmovable_rounds = 2;
        }

        private void help_vellus_props(long target_client_guid, short target_animal_index)
        {
            skill_Effects.Add(new()
            {
                skill_state = enum_skill_state.em_immunity,
                continued_rounds = 3,
            });

            _impl.ntf_player_use_props(_game_info.guid, props.help_vellus, PlayerGameInfo.guid, PlayerGameInfo.current_animal_index);
        }

        private void thunder_props(long target_client_guid, short target_animal_index)
        {
            _impl.ntf_player_use_props(_game_info.guid, props.thunder, target_client_guid, target_animal_index);

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
                for (short i = 0; i < target.PlayerGameInfo.animal_info.Count; i++)
                {
                    var _target = target;
                    var _animal = target.PlayerGameInfo.animal_info[i];
                    var index = i;

                    if (_animal.current_pos > 0 && _animal.current_pos < _impl.PlayergroundLenght)
                    {
                        if (_target.reverse_props())
                        {
                            var _reverse = randmon_reverse_props_target(_target);
                            _animal = _reverse.PlayerGameInfo.animal_info[_reverse.PlayerGameInfo.current_animal_index];
                            _impl.ntf_reverse_props(_game_info.guid, _target.PlayerGameInfo.guid, props.clown_gift_box, _reverse.PlayerGameInfo.guid, _reverse.PlayerGameInfo.current_animal_index);
                            _target = _reverse;
                            index = _reverse.PlayerGameInfo.current_animal_index;
                        }
                        else if (_target.immunity_props())
                        {
                            _impl.ntf_immunity_props(_game_info.guid, props.clown_gift_box, _target.PlayerGameInfo.guid, _target.PlayerGameInfo.current_animal_index);
                            continue;
                        }

                        var from = _animal.current_pos;
                        _animal.current_pos -= 3;
                        if (_animal.current_pos < 0)
                        {
                            _animal.current_pos = 0;
                        }
                        var to = _animal.current_pos;
                        _impl.ntf_effect_move(effect.thunder, _target.PlayerGameInfo.guid, index, from, to);
                    }
                }
            }
        }

        private void clown_gift_box_props(long target_client_guid, short target_animal_index)
        {
            var _target = random_props_target();

            if (_target.reverse_props())
            {
                var _reverse = randmon_reverse_props_target(_target);
                _impl.ntf_reverse_props(_game_info.guid, _target.PlayerGameInfo.guid, props.clown_gift_box, _reverse.PlayerGameInfo.guid, _reverse.PlayerGameInfo.current_animal_index);
                _target = _reverse;
            }
            else if (_target.immunity_props())
            {
                _impl.ntf_immunity_props(_game_info.guid, props.clown_gift_box, _target.PlayerGameInfo.guid, _target.PlayerGameInfo.current_animal_index);
                return;
            }
            else
            {
                _impl.ntf_player_use_props(_game_info.guid, props.clown_gift_box, _target.PlayerGameInfo.guid, _target.PlayerGameInfo.current_animal_index);
            }

            _target.skill_Effects.Add(new () 
            {
                skill_state = enum_skill_state.em_unable_use_props,
                continued_rounds = 3,
            });
        }

        private void excited_petals_props(long target_client_guid, short target_animal_index)
        {
            skill_Effects.Add(new()
            {
                skill_state = enum_skill_state.em_action_three,
                continued_rounds = 1,
            });

            _impl.ntf_player_use_props(_game_info.guid, props.excited_petals, PlayerGameInfo.guid, PlayerGameInfo.current_animal_index);
        }

        private void clip_props(long target_client_guid, short target_animal_index)
        {
            var _animal = PlayerGameInfo.animal_info[PlayerGameInfo.current_animal_index];

            var _effect_info = new effect_info();
            _effect_info.effect_id = effect.clip;
            _effect_info.grids = new List<short>();
            _effect_info.grids.Add(_animal.current_pos);

            _impl.effect_list.Add(_effect_info);

            _impl.ntf_player_use_props(_game_info.guid, props.clip, PlayerGameInfo.guid, PlayerGameInfo.current_animal_index);
        }

        private void landmine_props(long target_client_guid, short target_animal_index)
        {
            var _animal = PlayerGameInfo.animal_info[PlayerGameInfo.current_animal_index];

            var _effect_info = new effect_info();
            _effect_info.effect_id = effect.landmine;
            _effect_info.grids = new List<short>();
            _effect_info.grids.Add(_animal.current_pos);

            _impl.effect_list.Add(_effect_info);

            _impl.ntf_player_use_props(_game_info.guid, props.landmine, PlayerGameInfo.guid, PlayerGameInfo.current_animal_index);
        }

        private void spring_props(long target_client_guid, short target_animal_index)
        {
            var _animal = PlayerGameInfo.animal_info[PlayerGameInfo.current_animal_index];

            var _effect_info = new effect_info();
            _effect_info.effect_id = effect.spring;
            _effect_info.grids = new List<short>();
            _effect_info.grids.Add(_animal.current_pos);

            _impl.effect_list.Add(_effect_info);

            _impl.ntf_player_use_props(_game_info.guid, props.landmine, PlayerGameInfo.guid, PlayerGameInfo.current_animal_index);
        }

        private void banana_props(long target_client_guid, short target_animal_index)
        {
            var _target = random_props_target();

            if (_target.reverse_props())
            {
                var _reverse = randmon_reverse_props_target(_target);
                _impl.ntf_reverse_props(_game_info.guid, _target.PlayerGameInfo.guid, props.clown_gift_box, _reverse.PlayerGameInfo.guid, _reverse.PlayerGameInfo.current_animal_index);
                _target = _reverse;
            }
            else if (_target.immunity_props())
            {
                _impl.ntf_immunity_props(_game_info.guid, props.clown_gift_box, _target.PlayerGameInfo.guid, _target.PlayerGameInfo.current_animal_index);
                return;
            }
            else
            {
                _impl.ntf_player_use_props(_game_info.guid, props.clown_gift_box, _target.PlayerGameInfo.guid, _target.PlayerGameInfo.current_animal_index);
            }

            _target.skill_Effects.Add(new ()
            {
                skill_state = enum_skill_state.em_banana,
                continued_rounds = 1,
            });
        }

        private void watermelon_rind_props(long target_client_guid, short target_animal_index)
        {
            var _animal = PlayerGameInfo.animal_info[PlayerGameInfo.current_animal_index];

            var _effect_info = new effect_info();
            _effect_info.effect_id = effect.watermelon_rind;
            _effect_info.grids = new List<short>();
            _effect_info.grids.Add(_animal.current_pos);

            _impl.effect_list.Add(_effect_info);

            _impl.ntf_player_use_props(_game_info.guid, props.watermelon_rind, PlayerGameInfo.guid, PlayerGameInfo.current_animal_index);
        }

        private void red_mushroom_props(long target_client_guid, short target_animal_index)
        {
            var _animal = PlayerGameInfo.animal_info[PlayerGameInfo.current_animal_index];
            if (_animal.current_pos < _impl.PlayergroundLenght)
            {
                var from = _animal.current_pos;
                _animal.current_pos += 4;
                if (_animal.current_pos >= _impl.PlayergroundLenght)
                {
                    _animal.current_pos = (short)_impl.PlayergroundLenght;
                    if (check_done_play())
                    {
                        is_done_play = true;
                        _impl.DonePlayClient.Add(this);
                        rank = _impl.DonePlayClient.Count;
                    }
                }
                _impl.ntf_player_use_props(_game_info.guid, props.red_mushroom, PlayerGameInfo.guid, PlayerGameInfo.current_animal_index);
                _impl.ntf_effect_move(effect.red_mushroom, PlayerGameInfo.guid, PlayerGameInfo.current_animal_index, from, _animal.current_pos);
            }
        }

        private void gacha_props(long target_client_guid, short target_animal_index)
        {
            var add = _impl.props_define[(int)hub.hub.randmon_uint((uint)_impl.props_define.Count)];
            props_list.Add(add);

            _impl.ntf_player_use_props(_game_info.guid, props.gacha, PlayerGameInfo.guid, PlayerGameInfo.current_animal_index);
            _impl.ntf_add_props(enum_add_props_type.gacha_add, _game_info.guid, add);
        }

        private void fake_dice_props(long target_client_guid, short target_animal_index)
        {
            var _target = _impl.get_client_proxy(target_client_guid);

            if (_target.reverse_props())
            {
                var _reverse = randmon_reverse_props_target(_target);
                _impl.ntf_reverse_props(_game_info.guid, _target.PlayerGameInfo.guid, props.clown_gift_box, _reverse.PlayerGameInfo.guid, _reverse.PlayerGameInfo.current_animal_index);
                _target = _reverse;
            }
            else if (_target.immunity_props())
            {
                _impl.ntf_immunity_props(_game_info.guid, props.clown_gift_box, _target.PlayerGameInfo.guid, _target.PlayerGameInfo.current_animal_index);
                return;
            }
            else
            {
                _impl.ntf_player_use_props(_game_info.guid, props.clown_gift_box, _target.PlayerGameInfo.guid, _target.PlayerGameInfo.current_animal_index);
            }

            _target.skill_Effects.Add(new()
            {
                skill_state = enum_skill_state.em_fake_dice,
                continued_rounds = 1,
            });
        }
    }
}
