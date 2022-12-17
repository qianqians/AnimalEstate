using abelkhan;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace game
{
    public class SetAnimalOrderError : System.Exception
    {
        public SetAnimalOrderError(string err) : base(err)
        {
        }
    }

    public partial class client_proxy
    {
        private readonly player_inline_info _info;
        public List<playground> PlayerPlaygrounds{
            get
            {
                return _info.playground_list;
            }
        }

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
            set
            {
                _info.uuid = value;
            }
            get
            {
                return _info.uuid;
            }
        }

        private bool is_ready = false;
        public bool IsReady
        {
            get
            {
                return is_ready;
            }
        }

        private long wait_active_time = service.timerservice.Tick;
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

        private bool is_offline = false;
        public bool IsOffline
        {
            set
            {
                is_offline = value;
            }
            get
            {
                return is_offline;
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

        private int ThrowDiceCount
        {
            get
            {
                if (PlayerGameInfo.animal_info[PlayerGameInfo.current_animal_index].animal_id == animal.rabbit)
                {
                    return 2;
                }
                else
                {
                    return 1;
                }
            }
        }

        public class special_grid_effect
        {
            public float move_coefficient = 1.0f;
            public int mutil_rounds = 0;

            public int continued_rounds = 0;
            public int stop_rounds = 0;
        }
        private List<special_grid_effect> special_grid_effects = new();

        class skill_effect
        {
            public enum_skill_state skill_state;
            public int continued_rounds = 0;
        }
        private List<skill_effect> skill_Effects = new ();
        
        class active_state
        {
            public bool is_step_lotus;
            public bool could_use_skill;
            public bool could_use_props;
            public int use_props_count;
            public bool could_throw_dice;
            public int throw_dice_count;
            public float move_coefficient;
            public int round_active_num;
        }
        private active_state active_State;
        private bool skill_is_used = false;
        
        private bool is_done_play = false;
        public bool IsDonePlay
        {
            get
            {
                return is_done_play;
            }
        }

        private int rank = 4;
        public int PlayRank
        {
            get
            {
                return rank;
            }
        }

        public List<props> props_list = new ();

        private readonly Dictionary<skill, Action<long, short> > skill_list = new ();

        private error_code_ntf_caller _error_code_ntf_caller = new ();

        public client_proxy(player_inline_info info, game_impl impl)
        {
            _info = info;
            _impl = impl;

            _game_info = new()
            {
                uuid = _info.uuid,
                guid = _info.guid,
                name = _info.name,
                current_animal_index = 0,
                animal_info = new ()
            };

            var animal_list = new List<animal>(_info.hero_list);
            for (var i = 0; i < 3; i++)
            {
                var _animal_id = animal_list[(int)hub.hub.randmon_uint((uint)animal_list.Count)];
                var _skin_id = (skin)((int)_animal_id * 100 + 1);
                _game_info.animal_info.Add(new animal_game_info() { animal_id = _animal_id, skin_id = _skin_id, current_pos = -1 });
                animal_list.Remove(_animal_id);
            }
        }

        public void ntf_error_code(error err_code)
        {
            _error_code_ntf_caller.get_client(uuid).error_code(err_code);
        }

        public void set_animal_order(List<animal_game_info> animal_info)
        {
            if (animal_info.Count != 3)
            {
                throw new SetAnimalOrderError($"animal_info count != 3, player.guid:{_game_info.guid}");
            }
            _game_info.animal_info = animal_info;
        }

        public void add_special_grid_effect(special_grid_effect _effect)
        {
            special_grid_effects.Add(_effect);
        }

        public void summary_skill_effect()
        {
        }

        public void iterater_skill_effect()
        {
            var _due_skill_effect = new List<skill_effect>();
            foreach (var _skill_effect in skill_Effects)
            {
                _skill_effect.continued_rounds--;
                if (_skill_effect.continued_rounds <= 0)
                {
                    _due_skill_effect.Add(_skill_effect);
                }
            }
            foreach (var _skill_effect in _due_skill_effect)
            {
                skill_Effects.Remove(_skill_effect);
            }

            var _due_special_grid_effect = new List<special_grid_effect>();
            foreach (var grid_effect in special_grid_effects)
            {
                if (grid_effect.continued_rounds > 0)
                {
                    grid_effect.continued_rounds--;
                }
                else if (grid_effect.stop_rounds > 0)
                {
                    grid_effect.stop_rounds--;
                    if (grid_effect.stop_rounds <= 0)
                    {
                        _due_special_grid_effect.Add(grid_effect);
                    }
                }
                else
                {
                    _due_special_grid_effect.Add(grid_effect);
                }
            }
            foreach (var _grid_effect in _due_special_grid_effect)
            {
                special_grid_effects.Remove(_grid_effect);
            }
        }

        public void use_skill(long target_client_guid, short target_animal_index)
        {
            if (active_State.could_use_skill)
            {
                if (skill_list.TryGetValue(PlayerGameInfo.skill_id, out Action<long, short> skill_func))
                {
                    check_set_active_state_unactive();
                    skill_func.Invoke(target_client_guid, target_animal_index);
                }
                else
                {
                    log.log.err($"invaild skill id:{PlayerGameInfo.skill_id}, player.name:{_game_info.name}, player.guid:{_game_info.guid}");
                }
            }
        }

        public void throw_dice()
        {
            if (active_State.could_throw_dice)
            {
                var dice_list = new List<int>();
                var n = (int)hub.hub.randmon_uint(6) + 1;
                dice_list.Add(n);
                var dice = n;
                _impl.GameClientCaller.get_multicast(_impl.ClientUUIDS).throw_dice(_game_info.guid, dice_list);

                var move = (short)(dice * active_State.move_coefficient);
                var from = _game_info.animal_info[_game_info.current_animal_index].current_pos;
                var to = _game_info.animal_info[_game_info.current_animal_index].current_pos + move;
                if (_impl.PlayergroundLenght <= to)
                {
                    to = _impl.PlayergroundLenght - 1;
                    _game_info.animal_info[_game_info.current_animal_index].current_pos = (short)_impl.PlayergroundLenght;
                    if (check_done_play())
                    {
                        is_done_play = true;
                        _impl.DonePlayClient.Add(this);
                        rank = _impl.DonePlayClient.Count;
                    }
                }
                _impl.GameClientCaller.get_multicast(_impl.ClientUUIDS).move(_game_info.guid, from, to);
                if (active_State.is_step_lotus)
                {
                    for (var i = from; i <= to; i++)
                    {
                        _impl.
                    }
                }

                _impl.check_grid_effect(this);
            }
        }

        private void check_set_active_state_unactive()
        {
            active_State.could_use_skill = false;
            active_State.could_use_props = false;
            active_State.could_throw_dice = false;
        }

        public bool check_end_round()
        {
            if (active_State.could_use_skill || active_State.could_use_props || active_State.could_throw_dice)
            {
                return false;
            }

            if (active_State.round_active_num > 0)
            {
                active_State.round_active_num--;

                active_State.could_use_skill = true;
                active_State.could_use_props = true;
                active_State.use_props_count = 1;
                active_State.could_throw_dice = true;
                active_State.throw_dice_count = ThrowDiceCount;

                return false;
            }

            rounds++;

            return true;
        }

        private bool check_done_play()
        {
            foreach (var animal_info in _game_info.animal_info)
            {
                if (animal_info.current_pos < _impl.PlayergroundLenght)
                {
                    return false;
                }
            }
            return true;
        }

        public void set_ready()
        {
            is_ready = true;
        }

        public void set_auto_active(bool is_auto)
        {
            is_auto_active = is_auto;
        }

        public void auto_active_and_check_end_round()
        {
            throw_dice();
        }
    }

    public partial class game_impl
    {
        private readonly Dictionary<playground, int> playground_lenght = new() {
            { playground.lakeside, 64 },
            { playground.grassland, 100 },
            { playground.hill, 100 },
            { playground.snow, 100 },
            { playground.desert, 100 },
        };
        private readonly playground _playground;
        public int PlayergroundLenght 
        {
            get
            {
                return playground_lenght[_playground];
            }
        }
        public playground Playground
        {
            get
            {
                return _playground;
            }
        }

        private readonly List<client_proxy> _client_proxys = new ();
        public List<client_proxy> ClientProxys
        {
            get
            {
                return _client_proxys;
            }
        }
        public List<string> ClientUUIDS
        {
            get
            {
                var uuids = new List<string>();
                foreach (var _client in _client_proxys)
                {
                    uuids.Add(_client.uuid);
                }
                return uuids;
            }
        }
        public List<player_game_info> PlayerGameInfo
        {
            get
            {
                var player_game_info_list = new List<player_game_info>();
                foreach (var _client in _client_proxys)
                {
                    player_game_info_list.Add(_client.PlayerGameInfo);
                }
                return player_game_info_list;
            }
        }
        public int _current_client_index = 0;

        private long wait_ready_time = service.timerservice.Tick + 25000;
        public long Countdown
        {
            get
            {
                return (wait_ready_time - service.timerservice.Tick) / 1000;
            }
        }

        private bool is_all_ready = false;
        public bool IsAllReady
        {
            get
            {
                return is_all_ready;
            }
        }

        private bool is_done_play = false;
        public List<client_proxy> DonePlayClient = new ();

        public List<effect_info> effect_list = new ();
        public List

        private long idle_time = service.timerservice.Tick;
        private bool turn_next_player = false;

        private readonly game_client_caller _game_client_caller;
        public game_client_caller GameClientCaller
        {
            get
            {
                return _game_client_caller;
            }
        }

        private playground random_playground()
        {
            var random_list = new List<playground>();
            foreach (var _client in _client_proxys)
            {
                foreach (var _playground in _client.PlayerPlaygrounds)
                {
                    if (!random_list.Contains(_playground))
                    {
                        random_list.Add(_playground);
                    }
                }
            }
            return random_list[(int)hub.hub.randmon_uint((uint)random_list.Count)];
        }

        public game_impl(game_client_caller _caller, playground playground, List<player_inline_info> room_player_list)
        {
            _game_client_caller = _caller;
            _playground = playground;
            
            foreach (var _player in room_player_list)
            {
                var _client = new client_proxy(_player, this);
                _client_proxys.Add(_client);
            }

            for (var i = room_player_list.Count; i < 4; i++)
            {
                var _player_robot = new player_inline_info();
                _player_robot.uuid = "robot";
                _player_robot.name = NameHelper.GetNameHelper.GetName();
                _player_robot.guid = -1;
                _player_robot.hero_list = new List<animal> { animal.chicken, animal.monkey, animal.rabbit, animal.duck, animal.mouse, animal.bear, animal.tiger, animal.lion };
                _player_robot.skin_list = new List<skin> { skin.chicken, skin.monkey, skin.rabbit, skin.duck, skin.mouse, skin.bear, skin.tiger, skin.lion };
                _player_robot.playground_list = new List<playground> { playground.lakeside/*, playground.grassland, playground.hill, playground.snow, playground.desert*/ };
                var _client = new client_proxy(_player_robot, this);
                _client_proxys.Add(_client);
                _client.set_ready();
                _client.set_auto_active(true);
                _client.IsOffline = true;
            }

            if (_playground == playground.random)
            {
                _playground = random_playground();
            }

            _current_client_index = 0;
        }

        public void ntf_game_wait_start_info()
        {
            _game_client_caller.get_multicast(ClientUUIDS).game_wait_start_info((int)Countdown, Playground, PlayerGameInfo);
        }

        private bool check_all_ready()
        {
            foreach (var _client_Proxy in _client_proxys)
            {
                if (!_client_Proxy.IsReady)
                {
                    return false;
                }
            }
            return true;
        }

        public async void check_done_play()
        {
            if (DonePlayClient.Count >= 3)
            {
                var info = new game_settle_info();
                info.settle_info = new List<game_player_settle_info>();

                var player_hub_list = new List<string>();
                foreach (var _client_Proxy in _client_proxys)
                {
                    var player_settle_info = new game_player_settle_info();
                    player_settle_info.guid = _client_Proxy.PlayerGameInfo.guid;
                    player_settle_info.name = _client_Proxy.PlayerGameInfo.name;
                    player_settle_info.rank = _client_Proxy.PlayRank;
                    player_settle_info.award_coin = 100 / _client_Proxy.PlayRank;
                    player_settle_info.award_score = 50 / _client_Proxy.PlayRank;
                    info.settle_info.Add(player_settle_info);

                    var player_svr_key = redis_help.BuildPlayerGuidCacheKey(_client_Proxy.PlayerGameInfo.guid);
                    string player_hub_name = await game._redis_handle.GetStrData(player_svr_key);
                    if (!player_hub_list.Contains(player_hub_name))
                    {
                        player_hub_list.Add(player_hub_name);
                    }

                    var token = $"lock_{_client_Proxy.PlayerGameInfo.guid}";
                    var lock_key = redis_help.BuildPlayerGameCacheLockKey(_client_Proxy.PlayerGameInfo.guid);
                    try
                    {
                        await game._redis_handle.Lock(lock_key, token, 1000);

                        var player_game_key = redis_help.BuildPlayerGameCacheKey(_client_Proxy.PlayerGameInfo.guid);
                        var game_hub_name = await game._redis_handle.GetStrData(player_game_key);
                        if (game_hub_name == hub.hub.name)
                        {
                            game._redis_handle.DelData(player_game_key);
                        }
                    }
                    finally
                    {
                        await game._redis_handle.UnLock(lock_key, token);
                    }
                }

                foreach (var palyer_hub_name in player_hub_list)
                {
                    game._player_proxy_mng.get_player(palyer_hub_name).settle(info);
                }

                is_done_play = true;
            }
        }

        private void ntf_game_info()
        {
            var _round_player = _client_proxys[_current_client_index];
            _game_client_caller.get_multicast(ClientUUIDS).game_info(_playground, PlayerGameInfo, _round_player.PlayerGameInfo.guid);
        }

        public void ntf_player_use_skill(long guid, long target_client_guid, short target_animal_index)
        {
            _game_client_caller.get_multicast(ClientUUIDS).use_skill(guid, target_client_guid, target_animal_index);
        }

        public void ntf_reset_position()
        {
            _game_client_caller.get_multicast(ClientUUIDS).reset_position(PlayerGameInfo);
        }

        public client_proxy get_client_proxy(long guid)
        {
            foreach (var client_proxy in _client_proxys)
            {
                if (client_proxy.PlayerGameInfo.guid == guid)
                {
                    return client_proxy;
                }
            }
            return null;
        }

        private void next_player()
        {
            for(var i = 0; i < 4; i++)
            {
                _current_client_index++;
                if (_current_client_index >= 4)
                {
                    _current_client_index = 0;
                }

                var _round_client = _client_proxys[_current_client_index];
                if (!_round_client.IsDonePlay)
                {
                    _round_client.summary_skill_effect();
                    _round_client.iterater_skill_effect();
                    if (_round_client.CouldMove)
                    {
                        _game_client_caller.get_multicast(ClientUUIDS).turn_player_round(_round_client.PlayerGameInfo.guid);
                        break;
                    }
                }
            }

            turn_next_player = false;
        }

        private void wait_next_player()
        {
            turn_next_player = true;
            idle_time = service.timerservice.Tick + 3000;
        }

        public void player_use_skill(client_proxy _client, long target_client_guid, short target_animal_index)
        {
            var _current_client = _client_proxys[_current_client_index];
            if (_client.PlayerGameInfo.guid == _current_client.PlayerGameInfo.guid)
            {
                _client.use_skill(target_client_guid, target_animal_index);
                wait_next_player();
            }
            else
            {
                log.log.warn($"use_skill not client:{_client.PlayerGameInfo.guid} round active!");
            }
        }

        public void player_throw_dice(client_proxy _client)
        {
            var _current_client = _client_proxys[_current_client_index];
            if (_client.PlayerGameInfo.guid == _current_client.PlayerGameInfo.guid)
            {
                if (_client.throw_dice_and_check_end_round())
                {
                    wait_next_player();
                }
            }
            else
            {
                log.log.warn($"throw_dice not client:{_client.PlayerGameInfo.guid} round active!");
            }
        }

        public bool tick()
        {
            do
            {
                if (!is_all_ready)
                {
                    if (check_all_ready())
                    {
                        is_all_ready = true;
                    }
                    if (wait_ready_time < service.timerservice.Tick)
                    {
                        foreach (var _client_Proxy in _client_proxys)
                        {
                            if (!_client_Proxy.IsReady)
                            {
                                _client_Proxy.set_ready();
                                _client_Proxy.set_auto_active(true);
                            }
                        }
                        is_all_ready = true;
                    }
                    else
                    {
                        break;
                    }

                    if (is_all_ready)
                    {
                        var _round_client = _client_proxys[_current_client_index];
                        _round_client.summary_skill_effect();
                        _round_client.iterater_skill_effect();
                        ntf_game_info();
                    }
                }

                if (idle_time > service.timerservice.Tick)
                {
                    break;
                }

                if (turn_next_player)
                {
                    next_player();
                    check_randmon_effect();
                }

                var _client = _client_proxys[_current_client_index];
                if (_client.IsAutoActive)
                {
                    if (!_client.auto_active_and_check_end_round())
                    {
                        break;
                    }
                }
                if ((_client.WaitActiveTime + 15000) < service.timerservice.Tick)
                {
                    _client.set_auto_active(true);
                    if (!_client.auto_active_and_check_end_round())
                    {
                        break;
                    }
                }

                wait_next_player();

            } while (false);

            return is_done_play;
        }
    }

    public class game_mng
    {
        private readonly Dictionary<string, client_proxy> uuid_clients = new ();
        private readonly Dictionary<long, client_proxy> guid_clients = new();
        private readonly List<game_impl> games = new ();
        public int Count
        {
            get
            {
                return guid_clients.Count;
            }
        }

        private readonly game_client_caller _game_client_caller = new ();

        public game_mng()
        {
            hub.hub._timer.addticktime(3000, tick_game);
        }

        public client_proxy get_player(string uuid)
        {
            uuid_clients.TryGetValue(uuid, out client_proxy _client);
            return _client;
        }

        public void create_game(playground _playground, List<player_inline_info> room_player_list)
        {
            var _game = new game_impl(_game_client_caller, _playground, room_player_list);
            games.Add(_game);

            foreach (var _client in _game.ClientProxys)
            {
                if (_client.uuid == "robot" && _client.PlayerGameInfo.guid == -1)
                {
                    continue;
                }

                uuid_clients[_client.uuid] = _client;
                guid_clients[_client.PlayerGameInfo.guid] = _client;
            }
        }

        public void player_into_game(long guid, string uuid)
        {
            if (guid_clients.TryGetValue(guid, out client_proxy _client))
            {
                uuid_clients.Remove(_client.uuid);
                _client.uuid = uuid;
                uuid_clients.Add(_client.uuid, _client);

                _client.IsOffline = false;

                if (_client.GameImpl.IsAllReady)
                {
                    var _round_player = _client.GameImpl.ClientProxys[_client.GameImpl._current_client_index];
                    _game_client_caller.get_multicast(new List<string> { _client.uuid }).game_info(_client.GameImpl.Playground, _client.GameImpl.PlayerGameInfo, _round_player.PlayerGameInfo.guid);
                    _game_client_caller.get_multicast(new List<string> { _client.uuid }).ntf_effect_info(_client.GameImpl.effect_list);
                }
                else
                {
                    _game_client_caller.get_multicast(new List<string> { _client.uuid }).game_wait_start_info((int)_client.GameImpl.Countdown, _client.GameImpl.Playground, _client.GameImpl.PlayerGameInfo);
                }
            }
            else
            {
                log.log.warn($"player_into_game error player not in game guid:{guid}");


            }
        }

        public client_proxy get_client_uuid(string uuid)
        {
            uuid_clients.TryGetValue(uuid, out client_proxy _client);
            return _client;
        }

        public void player_use_skill(string uuid)
        {
            if (uuid_clients.TryGetValue(uuid, out client_proxy _client))
            {
                _client.GameImpl.player_use_skill(_client);
            }
            else
            {
                log.log.warn($"client not inline uuid:{uuid}");
            }
        }

        public void player_throw_dice(string uuid)
        {
            if (uuid_clients.TryGetValue(uuid, out client_proxy _client))
            {
                _client.GameImpl.player_throw_dice(_client);
            }
            else
            {
                log.log.warn($"client not inline uuid:{uuid}");
            }
        }

        private void tick_game(long tick)
        {
            try
            {
                var done_game_list = new List<game_impl>();
                foreach (var _game in games)
                {
                    if (_game.tick())
                    {
                        done_game_list.Add(_game);
                    }
                }

                foreach (var _game in done_game_list)
                {
                    games.Remove(_game);

                    foreach (var _client in _game.ClientProxys)
                    {
                        uuid_clients.Remove(_client.uuid);
                        guid_clients.Remove(_client.PlayerGameInfo.guid);
                    }
                }
            }
            catch (System.Exception ex)
            {
                log.log.err($"{ex}");
            }
            finally
            {
                hub.hub._timer.addticktime(3000, tick_game);
            }
        }
    }
}
