using abelkhan;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Security.Principal;

namespace game
{
    partial class client_proxy
    {

        private void chicken_skill()
        {
            if (rounds < 3)
            {
                log.log.err($"skill rounds not achieve player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            if (skill_rounds < 6)
            {
                log.log.err($"skill in cd player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            skill_rounds = 0;

            var _effect = new skill_effect();
            _effect.move_coefficient = 1.5f;
            _effect.continued_rounds = 4;
            skill_Effects.Add(_effect);
        }

        private void monkey_skill()
        {
            if (rounds < 3)
            {
                log.log.err($"skill rounds not achieve player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            if (skill_rounds < 6)
            {
                log.log.err($"skill in cd player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            skill_rounds = 0;

            var _effect = new skill_effect();
            _effect.move_coefficient = 1.5f;
            _effect.is_immunity = true;
            _effect.continued_rounds = 3;
            skill_Effects.Add(_effect);
        }

        private void rabbit_skill()
        {
            if (rounds < 3)
            {
                log.log.err($"skill rounds not achieve player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            if (skill_rounds < 6)
            {
                log.log.err($"skill in cd player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            skill_rounds = 0;

            var _effect = new skill_effect();
            _effect.dice_num = 2;
            _effect.continued_rounds = 2;
            skill_Effects.Add(_effect);
        }

        private void duck_skill()
        {
            if (rounds < 10)
            {
                log.log.err($"skill rounds not achieve player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            var _effect = new skill_effect();
            _effect.move_coefficient = 2;
            _effect.continued_rounds = int.MaxValue;
            skill_Effects.Add(_effect);
        }

        private void mouse_skill()
        {
            if (rounds < 3)
            {
                log.log.err($"skill rounds not achieve player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            if (skill_rounds < 6)
            {
                log.log.err($"skill in cd player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            skill_rounds = 0;

            var _effect = new effect_info();
            _effect.effect_id = effect.mouse_trap;
            _effect.grids = new List<short> { _game_info.animal_info[_game_info.current_animal_index].current_pos };
            _impl.effect_list.Add(_effect);
        }

        private void do_bear_skill()
        {
            foreach (var animal_info in PlayerGameInfo.animal_info) 
            {
                animal_info.current_pos -= 4;
                if (animal_info.current_pos < 0)
                {
                    animal_info.current_pos = 0;
                }
            }
        }

        private void bear_skill()
        {
            if (rounds < 3)
            {
                log.log.err($"skill rounds not achieve player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            if (skill_rounds < 6)
            {
                log.log.err($"skill in cd player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            skill_rounds = 0;

            foreach (var _client in _impl.ClientProxys)
            {
                if (_client.PlayerGameInfo.guid != _game_info.guid)
                {
                    _client.do_bear_skill();
                }
            }
        }

        private void do_tiger_skill()
        {
            var _effect = new skill_effect();
            _effect.could_move = false;
            _effect.continued_rounds = 2;
            skill_Effects.Add(_effect);
        }

        private void tiger_skill()
        {
            if (rounds < 3)
            {
                log.log.err($"skill rounds not achieve player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            if (skill_rounds < 6)
            {
                log.log.err($"skill in cd player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            skill_rounds = 0;

            foreach (var _client in _impl.ClientProxys)
            {
                if (_client.PlayerGameInfo.guid != _game_info.guid)
                {
                    _client.do_tiger_skill();
                }
            }
        }

        private void do_lion_skill()
        {
            var _effect = new skill_effect();
            _effect.move_coefficient = 0.5f;
            _effect.continued_rounds = 3;
            skill_Effects.Add(_effect);
        }

        private void lion_skill()
        {
            if (rounds < 3)
            {
                log.log.err($"skill rounds not achieve player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            if (skill_rounds < 6)
            {
                log.log.err($"skill in cd player.name:{_info.name} player.guid:{_info.guid}");
                return;
            }

            skill_rounds = 0;

            foreach (var _client in _impl.ClientProxys)
            {
                if (_client.PlayerGameInfo.guid != _game_info.guid)
                {
                    _client.do_lion_skill();
                }
            }
        }

    }
}
