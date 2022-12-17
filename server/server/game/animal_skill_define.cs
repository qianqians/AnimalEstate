using abelkhan;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Security.Principal;

namespace game
{
    partial class client_proxy
    {
        private bool check_could_use_skill()
        {
            if (rounds < 5)
            {
                return false;
            }

            if (skill_is_used)
            {
                return false;
            }

            return true;
        }

        enum enum_skill_state
        {
            em_phantom_dice = 1,
            em_thief = 2,
            em_step_lotus = 3,
            em_preemptive_strike = 4,
            em_move_halved = 5,
            em_can_not_move = 6,
            em_immunity = 7,
            em_unable_use_props = 8,
            em_action_three = 9,
            em_turtle_shell = 10,
            em_fake_dice = 11,
        }

        private void phantom_dice_skill(long target_client_guid, short target_animal_index)
        {
            skill_Effects.Add(new()
            {
                skill_state = enum_skill_state.em_phantom_dice,
                continued_rounds = 5,
            });
            _impl.ntf_player_use_skill(_game_info.guid, target_client_guid, target_animal_index);
        }

        private void soul_moving_method(long target_client_guid, short target_animal_index)
        {
            var target_client = _impl.get_client_proxy(target_client_guid);
            var src = target_client.PlayerGameInfo.animal_info[target_animal_index];
            var dest = PlayerGameInfo.animal_info[PlayerGameInfo.current_animal_index];

            target_client.PlayerGameInfo.animal_info[target_animal_index] = dest;
            PlayerGameInfo.animal_info[PlayerGameInfo.current_animal_index] = src;

            _impl.ntf_player_use_skill(_game_info.guid, target_client_guid, target_animal_index);
        }

        private void thief_reborn(long target_client_guid, short target_animal_index)
        {
            var target_client = _impl.get_client_proxy(target_client_guid);
            props_list.AddRange(target_client.props_list);
            target_client.props_list.Clear();

            active_State.could_use_props = true;
            active_State.use_props_count = 3;

            _impl.ntf_player_use_skill(_game_info.guid, target_client_guid, target_animal_index);
        }

        private void step_lotus(long target_client_guid, short target_animal_index)
        {
            skill_Effects.Add(new()
            {
                skill_state = enum_skill_state.em_step_lotus,
                continued_rounds = 5,

                active_animal = PlayerGameInfo.animal_info[target_animal_index].animal_id
            });

            _impl.ntf_player_use_skill(_game_info.guid, target_client_guid, target_animal_index);
        }

        private void preemptive_strike(long target_client_guid, short target_animal_index)
        {
            _impl.ClientProxys.Remove(this);
            _impl.ClientProxys.Insert(0, this);

            skill_Effects.Add(new()
            {
                skill_state = enum_skill_state.em_preemptive_strike,
                continued_rounds = int.MaxValue,
            });

            _impl.ntf_player_use_skill(_game_info.guid, target_client_guid, target_animal_index);
        }

        private void swap_places(long target_client_guid, short target_animal_index)
        {
            var target_client = _impl.get_client_proxy(target_client_guid);
            var src = target_client.PlayerGameInfo.animal_info[target_animal_index];
            var dest = PlayerGameInfo.animal_info[PlayerGameInfo.current_animal_index];

            var tmp_pos = src.current_pos;
            src.current_pos = dest.current_pos;
            dest.current_pos = tmp_pos;

            _impl.ntf_player_use_skill(_game_info.guid, target_client_guid, target_animal_index);
        }

        private void altec_lightwave(long target_client_guid, short target_animal_index)
        {
            var target_client = _impl.get_client_proxy(target_client_guid);
            var target_animal = target_client.PlayerGameInfo.animal_info[target_animal_index];
            target_animal.could_move = false;

            _impl.ntf_player_use_skill(_game_info.guid, target_client_guid, target_animal_index);
        }

        private void reset_position(long target_client_guid, short target_animal_index)
        {
            var src = PlayerGameInfo.animal_info[PlayerGameInfo.current_animal_index];
            var other_animal = new List<animal_game_info>();

            foreach (var _client in _impl.ClientProxys)
            {
                foreach (var _animal in _client.PlayerGameInfo.animal_info)
                {
                    if (_animal == src)
                    {
                        continue;
                    }

                    int index = 0;
                    for (int i = 0; i < other_animal.Count; i++)
                    {
                        if (other_animal[i].current_pos > src.current_pos)
                        {
                            index = i;
                        }
                        else
                        {
                            break;
                        }
                    }
                    other_animal.Insert(index, _animal);
                }
            }

            var pos = src.current_pos;
            foreach (var _target in other_animal)
            {
                _target.current_pos = --pos;
                if (_target.current_pos < 0)
                {
                    _target.current_pos = 0;
                }
            }

            _impl.ntf_player_use_skill(_game_info.guid, target_client_guid, target_animal_index);
            _impl.ntf_reset_position();
        }
    }
}
