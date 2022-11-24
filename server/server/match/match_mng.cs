using abelkhan;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace match
{
    public class match_mng
    {
        private readonly Queue<Tuple<string, player_inline_info> > one_player_match_list = new ();
        private readonly Queue<Tuple<string, room_info> > one_room_match_list = new();
        private readonly Queue<Tuple<string, room_info> > two_room_match_list = new ();
        private readonly Queue<Tuple<string, room_info> > three_room_match_list = new ();
        private readonly Queue<Tuple<string, room_info> > four_room_match_list = new ();

        public match_mng()
        {
            hub.hub._timer.addticktime(5000, tick_match);
        }

        public void player_join_match(string player_hub_name, player_inline_info _player_info)
        {
            one_player_match_list.Enqueue(Tuple.Create(player_hub_name, _player_info));
        }

        public void room_join_match(string room_hub_name, room_info _info)
        {
            switch (_info.room_player_list.Count)
            {
                case 1:
                    one_room_match_list.Enqueue(Tuple.Create(room_hub_name, _info));
                    break;

                case 2:
                    two_room_match_list.Enqueue(Tuple.Create(room_hub_name, _info));
                    break;

                case 3:
                    three_room_match_list.Enqueue(Tuple.Create(room_hub_name, _info));
                    break;

                case 4:
                    four_room_match_list.Enqueue(Tuple.Create(room_hub_name, _info));
                    break;

                default:
                    log.log.err($"wrong room info room hub name:{room_hub_name}, guid:{_info.room_uuid}");
                    break;
            }
        }

        private Task<bool> match_game(game_proxy _game, List<player_inline_info> player_List)
        {
            var ret = new TaskCompletionSource<bool>();

            _game.start_game(player_List).callBack(() => {
                ret.SetResult(true);

            }, (err) => {
                log.log.err($"match game err:{err}!");
                ret.SetResult(false);

            }).timeout(1000, () => {
                log.log.err($"match game timeout!");
                ret.SetResult(false);
            });

            return ret.Task;
        }

        private async Task match_four_room(List<game_proxy> idle_game_svr_list)
        {
            var room = four_room_match_list.Dequeue();
            while (true)
            {
                var idle_game_count = idle_game_svr_list.Count;
                if (idle_game_count <= 0)
                {
                    four_room_match_list.Enqueue(room);
                    break;
                }
                var _game = idle_game_svr_list[(int)hub.hub.randmon_uint((uint)idle_game_count)];

                if (await match_game(_game, room.Item2.room_player_list))
                {
                    var _room_svr = match._room_proxy_mng.get_room(room.Item1);
                    _room_svr.start_game(room.Item2.room_uuid, _game.name);
                }
                else
                {
                    idle_game_svr_list.Remove(_game);
                    continue;
                }

                if (four_room_match_list.Count <= 0)
                {
                    break;
                }

                room = four_room_match_list.Dequeue();
            }
        }

        private async Task match_three_room(List<game_proxy> idle_game_svr_list)
        {
            var room = three_room_match_list.Dequeue();
            Tuple<string, player_inline_info> _player = null;
            Tuple<string, room_info> _one_match = null;
            while (true)
            {
                var idle_game_count = idle_game_svr_list.Count;
                if (idle_game_count <= 0)
                {
                    three_room_match_list.Enqueue(room);

                    if (_player != null)
                    {
                        one_player_match_list.Enqueue(_player);
                    }
                    else if (_one_match != null)
                    {
                        one_room_match_list.Enqueue(_one_match);
                    }

                    break;
                }
                var _game = idle_game_svr_list[(int)hub.hub.randmon_uint((uint)idle_game_count)];

                List<player_inline_info> player_list = new(room.Item2.room_player_list);
                if (one_player_match_list.Count > 0)
                {
                    _player = one_player_match_list.Dequeue();
                    player_list.Add(_player.Item2);
                }
                else if (one_room_match_list.Count > 0)
                {
                    _one_match = one_room_match_list.Dequeue();
                    player_list.AddRange(_one_match.Item2.room_player_list);
                }

                if (await match_game(_game, player_list))
                {
                    var _room_svr = match._room_proxy_mng.get_room(room.Item1);
                    _room_svr.start_game(room.Item2.room_uuid, _game.name);

                    if (_player != null)
                    {
                        var _player_svr = match._player_proxy_mng.get_player(_player.Item1);
                        _player_svr.player_join_game(_player.Item2.guid, _game.name);
                        _player = null;
                    }
                    else if (_one_match != null)
                    {
                        var _one_match_room_svr = match._room_proxy_mng.get_room(_one_match.Item1);
                        _one_match_room_svr.start_game(_one_match.Item2.room_uuid, _game.name);
                        _one_match = null;
                    }
                }
                else
                {
                    idle_game_svr_list.Remove(_game);
                    continue;
                }

                if (three_room_match_list.Count <= 0)
                {
                    break;
                }

                room = three_room_match_list.Dequeue();
            }
        }

        private async Task match_two_room(List<game_proxy> idle_game_svr_list)
        {
            var room = two_room_match_list.Dequeue();
            Tuple<string, room_info> _two_match = null;
            Tuple<string, player_inline_info> _player1 = null;
            Tuple<string, player_inline_info> _player2 = null;
            Tuple<string, room_info> _one_match1 = null;
            Tuple<string, room_info> _one_match2 = null;
            while (true)
            {
                var idle_game_count = idle_game_svr_list.Count;
                if (idle_game_count <= 0)
                {
                    three_room_match_list.Enqueue(room);

                    if (_two_match != null)
                    {
                        two_room_match_list.Enqueue(_two_match);
                    }
                    if (_player1 != null)
                    {
                        one_player_match_list.Enqueue(_player1);
                    }
                    if (_player2 != null)
                    {
                        one_player_match_list.Enqueue(_player2);
                    }
                    if (_one_match1 != null)
                    {
                        one_room_match_list.Enqueue(_one_match1);
                    }
                    if (_one_match2 != null)
                    {
                        one_room_match_list.Enqueue(_one_match2);
                    }

                    break;
                }
                var _game = idle_game_svr_list[(int)hub.hub.randmon_uint((uint)idle_game_count)];

                List<player_inline_info> player_list = new(room.Item2.room_player_list);
                if (two_room_match_list.Count > 0)
                {
                    _two_match = two_room_match_list.Dequeue();
                    player_list.AddRange(_two_match.Item2.room_player_list);
                }
                else 
                {
                    if (one_player_match_list.Count > 0)
                    {
                        _player1 = one_player_match_list.Dequeue();
                        player_list.Add(_player1.Item2);
                    }
                    if (one_player_match_list.Count > 0)
                    {
                        _player2 = one_player_match_list.Dequeue();
                        player_list.Add(_player2.Item2);
                    }

                    if (player_list.Count < 4)
                    {
                        if (one_room_match_list.Count > 0)
                        {
                            _one_match1 = one_room_match_list.Dequeue();
                            player_list.AddRange(_one_match1.Item2.room_player_list);
                        }
                        if (player_list.Count < 4)
                        {
                            if (one_room_match_list.Count > 0)
                            {
                                _one_match2 = one_room_match_list.Dequeue();
                                player_list.AddRange(_one_match2.Item2.room_player_list);
                            }
                        }
                    }
                }

                if (await match_game(_game, player_list))
                {
                    var _room_svr = match._room_proxy_mng.get_room(room.Item1);
                    _room_svr.start_game(room.Item2.room_uuid, _game.name);

                    if (_two_match != null)
                    {
                        var _two_match_room_svr = match._room_proxy_mng.get_room(_two_match.Item1);
                        _two_match_room_svr.start_game(_two_match.Item2.room_uuid, _game.name);
                    }
                    else 
                    {
                        if (_player1 != null)
                        {
                            var _player_svr = match._player_proxy_mng.get_player(_player1.Item1);
                            _player_svr.player_join_game(_player1.Item2.guid, _game.name);
                        }
                        if (_player2 != null)
                        {
                            var _player_svr = match._player_proxy_mng.get_player(_player2.Item1);
                            _player_svr.player_join_game(_player2.Item2.guid, _game.name);
                        }
                        if (_one_match1 != null)
                        {
                            var _one_match_room_svr = match._room_proxy_mng.get_room(_one_match1.Item1);
                            _one_match_room_svr.start_game(_one_match1.Item2.room_uuid, _game.name);
                        }
                        if (_one_match2 != null)
                        {
                            var _one_match_room_svr = match._room_proxy_mng.get_room(_one_match2.Item1);
                            _one_match_room_svr.start_game(_one_match2.Item2.room_uuid, _game.name);
                        }
                    }
                    _two_match = null;
                    _player1 = null;
                    _player2 = null;
                    _one_match1 = null;
                    _one_match2 = null;
                }
                else
                {
                    idle_game_svr_list.Remove(_game);
                    continue;
                }

                if (two_room_match_list.Count <= 0)
                {
                    break;
                }

                room = two_room_match_list.Dequeue();
            }
        }

        private async Task match_one_room(List<game_proxy> idle_game_svr_list)
        {
            List<Tuple<string, room_info> > match_room_List = new ();
            List<Tuple<string, player_inline_info> > match_player_List = new();
            while (true)
            {
                var idle_game_count = idle_game_svr_list.Count;
                if (idle_game_count <= 0)
                {
                    foreach (var it in match_room_List)
                    {
                        one_room_match_list.Enqueue(it);
                    }
                    foreach (var it in match_player_List)
                    {
                        one_player_match_list.Enqueue(it);
                    }

                    break;
                }
                var _game = idle_game_svr_list[(int)hub.hub.randmon_uint((uint)idle_game_count)];

                List<player_inline_info> player_list = new();
                while (one_room_match_list.Count > 0)
                {
                    var _room = one_room_match_list.Dequeue();
                    player_list.AddRange(_room.Item2.room_player_list);
                    match_room_List.Add(_room);

                    if (player_list.Count >= 4)
                    {
                        break;
                    }
                }
                if (player_list.Count < 4)
                {
                    while (one_player_match_list.Count > 0)
                    {
                        var _player = one_player_match_list.Dequeue();
                        player_list.Add(_player.Item2);
                        match_player_List.Add(_player);

                        if (player_list.Count >= 4)
                        {
                            break;
                        }
                    }
                }

                if (await match_game(_game, player_list))
                {
                    foreach (var it in match_room_List)
                    {
                        var _match_room_svr = match._room_proxy_mng.get_room(it.Item1);
                        _match_room_svr.start_game(it.Item2.room_uuid, _game.name);
                    }
                    foreach (var it in match_player_List)
                    {
                        var _match_player_svr = match._player_proxy_mng.get_player(it.Item1);
                        _match_player_svr.player_join_game(it.Item2.guid, _game.name);
                    }

                    match_room_List.Clear();
                    match_player_List.Clear();
                }
                else
                {
                    idle_game_svr_list.Remove(_game);
                    continue;
                }

                if (one_room_match_list.Count <= 0 && one_player_match_list.Count <= 0)
                {
                    break;
                }
            }
        }

        private async void tick_match(long tick_time)
        {
            var idle_game_svr_list = await match._game_proxy_mng.get_idle_game();

            if (four_room_match_list.Count > 0 && idle_game_svr_list.Count > 0)
            {
                await match_four_room(idle_game_svr_list);
            }

            if (three_room_match_list.Count > 0 && idle_game_svr_list.Count > 0)
            {
                await match_three_room(idle_game_svr_list);
            }

            if (two_room_match_list.Count > 0 && idle_game_svr_list.Count > 0)
            {
                await match_two_room(idle_game_svr_list);
            }

            if (one_room_match_list.Count > 0 && one_player_match_list.Count > 0 && idle_game_svr_list.Count > 0)
            {
                await match_one_room(idle_game_svr_list);
            }
        }
    }
}
