using abelkhan;
using service;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace game
{
    public class client_proxy
    {
        private readonly player_inline_info _info;
        private player_game_info _game_info;
        public player_game_info PlayerGameInfo
        {
            get
            {
                return _game_info;
            }
        }

        public string uuid
        {
            get
            {
                return _info.uuid;
            }
        }

        private long wait_active_time = timerservice.Tick;
        public long WaitActiveTime
        {
            set
            {
                wait_active_time = value;
            }
            get
            {
                return wait_active_time;
            }
        }

        private bool is_auto_active = false;
        public bool IsAutoActive
        {
            get
            {
                return is_auto_active;
            }
        }

        private readonly game_impl _impl;
        public game_impl GameImpl
        {
            get
            {
                return _impl;
            }
        }

        private int rounds = 0;
        private int skill_rounds = int.MaxValue;

        struct skill_effect
        {
            public bool could_move = true;
            public bool is_immunity = false;
            public int dice_num = 1;
            public float move_coefficient = 1.0f;

            public int continued_rounds = 0;

            public skill_effect()
            {
            }
        }
        private List<skill_effect> skill_Effects = new();

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
            _effect.move_coefficient = 2;
            _effect.continued_rounds = 3;
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
            _effect.continued_rounds = 4;
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

            var _special_grid = new game_impl.special_grid();
            _special_grid.stop_rounds = 3;
            _impl.special_grids.Add(_game_info.current_pos, _special_grid);
        }

        private void do_bear_skill()
        {
            PlayerGameInfo.current_pos -= 4;
            if (PlayerGameInfo.current_pos < 0)
            {
                PlayerGameInfo.current_pos = 0;
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

        public client_proxy(player_inline_info info, game_impl impl)
        {
            _info = info;
            _impl = impl;

            _game_info = new ();
            _game_info.uuid = _info.uuid;
            _game_info.guid = _info.guid;
            _game_info.name = _info.name;
            _game_info.current_pos = 0;
            _game_info.current_animal_index = 0;
        }

        public void set_auto_active(bool is_auto)
        {
            is_auto_active = is_auto;
        }

        public void auto_active()
        {

        }
    }

    public class game_impl
    {
        private readonly playground _playground;
        
        private readonly List<client_proxy> _client_proxys = new ();
        public List<client_proxy> ClientProxys
        {
            get
            {
                return _client_proxys;
            }
        }
        private int _current_client_index = 0;

        public struct special_grid
        {
            public float move_coefficient = 1.0f;
            public int random_move = 0;
            public int mutil_rounds = 0;

            public int continued_rounds = 0;
            public int stop_rounds = 0;

            public special_grid()
            {
            }
        }
        public Dictionary<int, special_grid> special_grids = new ();

        public game_impl(playground playground, List<player_inline_info> room_player_list)
        {
            _playground = playground;

            foreach (var _player in room_player_list)
            {
                var _client = new client_proxy(_player, this);
                _client_proxys.Add(_client);
            }

            _current_client_index = 0;
        }

        public void tick()
        {
            var _client = _client_proxys[_current_client_index];

            if (_client.IsAutoActive)
            {
                _client.auto_active();
                _current_client_index++;
            }
            if ((_client.WaitActiveTime + 20000) < timerservice.Tick)
            {
                _client.set_auto_active(true);
                _client.auto_active();
                _current_client_index++;
            }
        }
    }

    public class game_mng
    {
        private readonly Dictionary<string, client_proxy> uuid_clients = new ();
        private readonly List<game_impl> games = new ();

        public game_mng()
        {
            hub.hub._timer.addticktime(1000, tick_game);
        }

        public void create_game(playground _playground, List<player_inline_info> room_player_list)
        {
            var _game = new game_impl(_playground, room_player_list);
            games.Add(_game);

            foreach (var _client in _game.ClientProxys)
            {
                uuid_clients.Add(_client.uuid, _client);
            }
        }

        private void tick_game(long tick)
        {
            try
            {
                foreach (var _game in games)
                {
                    _game.tick();
                }
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
            finally
            {
                hub.hub._timer.addticktime(1000, tick_game);
            }
        }
    }
}
