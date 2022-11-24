using abelkhan;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace match
{
    public class match_mng
    {
        private readonly List<Tuple<string, player_inline_info> > one_player_match_list = new ();
        private readonly List<Tuple<string, room_info> > one_room_match_list = new();
        private readonly List<Tuple<string, room_info> > two_room_match_list = new ();
        private readonly List<Tuple<string, room_info> > three_room_match_list = new ();
        private readonly List<Tuple<string, room_info> > four_room_match_list = new ();

        public void player_join_match(string player_hub_name, player_inline_info _player_info)
        {
            one_player_match_list.Add(Tuple.Create(player_hub_name, _player_info));
        }

        public void room_join_match(string room_hub_name, room_info _info)
        {
            switch (_info.room_player_list.Count)
            {
                case 1:
                    one_room_match_list.Add(Tuple.Create(room_hub_name, _info));
                    break;

                case 2:
                    two_room_match_list.Add(Tuple.Create(room_hub_name, _info));
                    break;

                case 3:
                    three_room_match_list.Add(Tuple.Create(room_hub_name, _info));
                    break;

                case 4:
                    four_room_match_list.Add(Tuple.Create(room_hub_name, _info));
                    break;

                default:
                    log.log.err($"wrong room info room hub name:{room_hub_name}, guid:{_info.room_uuid}");
                    break;
            }
        }
    }
}
