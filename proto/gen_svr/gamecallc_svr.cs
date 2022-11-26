using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using MsgPack.Serialization;

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for c#*/

/*this struct code is codegen by abelkhan codegen for c#*/
    public class effect_info
    {
        public List<Int16> grids;
        public effect effect_id;
        public static MsgPack.MessagePackObjectDictionary effect_info_to_protcol(effect_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            var _array_grids = new List<MsgPack.MessagePackObject>();
            foreach(var v_ in _struct.grids){
                _array_grids.Add(v_);
            }
            _protocol.Add("grids", new MsgPack.MessagePackObject(_array_grids));
            _protocol.Add("effect_id", (Int32)_struct.effect_id);
            return _protocol;
        }
        public static effect_info protcol_to_effect_info(MsgPack.MessagePackObjectDictionary _protocol){
            var _struct3934263e_8a7e_3773_9a47_c85f982b70f5 = new effect_info();
            foreach (var i in _protocol){
                if (((MsgPack.MessagePackObject)i.Key).AsString() == "grids"){
                    _struct3934263e_8a7e_3773_9a47_c85f982b70f5.grids = new();
                    var _protocol_array = ((MsgPack.MessagePackObject)i.Value).AsList();
                    foreach (var v_ in _protocol_array){
                        _struct3934263e_8a7e_3773_9a47_c85f982b70f5.grids.Add(((MsgPack.MessagePackObject)v_).AsInt16());
                    }
                }
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "effect_id"){
                    _struct3934263e_8a7e_3773_9a47_c85f982b70f5.effect_id = (effect)((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
            }
            return _struct3934263e_8a7e_3773_9a47_c85f982b70f5;
        }
    }

/*this caller code is codegen by abelkhan codegen for c#*/
/*this cb code is codegen by abelkhan for c#*/
    public class game_client_rsp_cb : common.imodule {
        public game_client_rsp_cb() 
        {
        }

    }

    public class game_client_clientproxy {
        public string client_uuid_b99eae25_99b5_3006_b19c_ccf531aff983;
        private Int64 uuid_b99eae25_99b5_3006_b19c_ccf531aff983 = (Int64)RandomUUID.random();

        public game_client_rsp_cb rsp_cb_game_client_handle;

        public game_client_clientproxy(game_client_rsp_cb rsp_cb_game_client_handle_)
        {
            rsp_cb_game_client_handle = rsp_cb_game_client_handle_;
        }

    }

    public class game_client_multicast {
        public List<string> client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983;
        public game_client_rsp_cb rsp_cb_game_client_handle;

        public game_client_multicast(game_client_rsp_cb rsp_cb_game_client_handle_)
        {
            rsp_cb_game_client_handle = rsp_cb_game_client_handle_;
        }

        public void game_info(List<player_game_info> info){
            var _argv_a8150bab_ab88_3ac0_b633_425c25e81223 = new ArrayList();
            var _array_391fd3d4_2d55_3f5e_9223_7f450a814a15 = new ArrayList();
            foreach(var v_0c15545d_d42a_5fe0_bed7_a9496851e88b in info){
                _array_391fd3d4_2d55_3f5e_9223_7f450a814a15.Add(player_game_info.player_game_info_to_protcol(v_0c15545d_d42a_5fe0_bed7_a9496851e88b));
            }
            _argv_a8150bab_ab88_3ac0_b633_425c25e81223.Add(_array_391fd3d4_2d55_3f5e_9223_7f450a814a15);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_game_info", _argv_a8150bab_ab88_3ac0_b633_425c25e81223);
        }

        public void move(Int64 guid, Int32 from, Int32 to){
            var _argv_33efb72e_9227_32af_a058_169be114a277 = new ArrayList();
            _argv_33efb72e_9227_32af_a058_169be114a277.Add(guid);
            _argv_33efb72e_9227_32af_a058_169be114a277.Add(from);
            _argv_33efb72e_9227_32af_a058_169be114a277.Add(to);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_move", _argv_33efb72e_9227_32af_a058_169be114a277);
        }

        public void relay(Int64 guid, Int16 new_animal_index){
            var _argv_24e2d4a2_c288_30c5_b96e_6dd1d36278a9 = new ArrayList();
            _argv_24e2d4a2_c288_30c5_b96e_6dd1d36278a9.Add(guid);
            _argv_24e2d4a2_c288_30c5_b96e_6dd1d36278a9.Add(new_animal_index);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_relay", _argv_24e2d4a2_c288_30c5_b96e_6dd1d36278a9);
        }

        public void effect(effect_info info){
            var _argv_002c03ba_b18e_3cab_b587_5b1d8156975b = new ArrayList();
            _argv_002c03ba_b18e_3cab_b587_5b1d8156975b.Add(effect_info.effect_info_to_protcol(info));
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_effect", _argv_002c03ba_b18e_3cab_b587_5b1d8156975b);
        }

        public void use_skill(Int64 guid){
            var _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe = new ArrayList();
            _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe.Add(guid);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_use_skill", _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe);
        }

        public void effect_move(Int64 guid, effect effect_id, Int32 from, Int32 to){
            var _argv_275504eb_206b_39cf_a228_7410dadf83b7 = new ArrayList();
            _argv_275504eb_206b_39cf_a228_7410dadf83b7.Add(guid);
            _argv_275504eb_206b_39cf_a228_7410dadf83b7.Add(effect_id);
            _argv_275504eb_206b_39cf_a228_7410dadf83b7.Add(from);
            _argv_275504eb_206b_39cf_a228_7410dadf83b7.Add(to);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_effect_move", _argv_275504eb_206b_39cf_a228_7410dadf83b7);
        }

    }

    public class game_client_broadcast {
        public game_client_rsp_cb rsp_cb_game_client_handle;

        public game_client_broadcast(game_client_rsp_cb rsp_cb_game_client_handle_)
        {
            rsp_cb_game_client_handle = rsp_cb_game_client_handle_;
        }

    }

    public class game_client_caller {
        public static game_client_rsp_cb rsp_cb_game_client_handle = null;
        private game_client_clientproxy _clientproxy;
        private game_client_multicast _multicast;
        private game_client_broadcast _broadcast;

        public game_client_caller() 
        {
            if (rsp_cb_game_client_handle == null)
            {
                rsp_cb_game_client_handle = new game_client_rsp_cb();
            }

            _clientproxy = new game_client_clientproxy(rsp_cb_game_client_handle);
            _multicast = new game_client_multicast(rsp_cb_game_client_handle);
            _broadcast = new game_client_broadcast(rsp_cb_game_client_handle);
        }

        public game_client_clientproxy get_client(string client_uuid) {
            _clientproxy.client_uuid_b99eae25_99b5_3006_b19c_ccf531aff983 = client_uuid;
            return _clientproxy;
        }

        public game_client_multicast get_multicast(List<string> client_uuids) {
            _multicast.client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983 = client_uuids;
            return _multicast;
        }

        public game_client_broadcast get_broadcast() {
            return _broadcast;
        }
    }


}
