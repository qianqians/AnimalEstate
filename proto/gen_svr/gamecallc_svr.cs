using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using MsgPack.Serialization;

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for c#*/

    public enum enum_add_props_type{
        pick_up = 1,
        gacha_add = 2
    }
/*this struct code is codegen by abelkhan codegen for c#*/
    public class effect_info
    {
        public List<Int16> grids;
        public effect effect_id;
        public Int32 continued_rounds;
        public static MsgPack.MessagePackObjectDictionary effect_info_to_protcol(effect_info _struct){
            var _protocol = new MsgPack.MessagePackObjectDictionary();
            if (_struct.grids != null) {
                var _array_grids = new List<MsgPack.MessagePackObject>();
                foreach(var v_ in _struct.grids){
                    _array_grids.Add(v_);
                }
                _protocol.Add("grids", new MsgPack.MessagePackObject(_array_grids));
            }
            _protocol.Add("effect_id", (Int32)_struct.effect_id);
            _protocol.Add("continued_rounds", _struct.continued_rounds);
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
                else if (((MsgPack.MessagePackObject)i.Key).AsString() == "continued_rounds"){
                    _struct3934263e_8a7e_3773_9a47_c85f982b70f5.continued_rounds = ((MsgPack.MessagePackObject)i.Value).AsInt32();
                }
            }
            return _struct3934263e_8a7e_3773_9a47_c85f982b70f5;
        }
    }

/*this caller code is codegen by abelkhan codegen for c#*/
    public class game_client_choose_dice_cb
    {
        private UInt64 cb_uuid;
        private game_client_rsp_cb module_rsp_cb;

        public game_client_choose_dice_cb(UInt64 _cb_uuid, game_client_rsp_cb _module_rsp_cb)
        {
            cb_uuid = _cb_uuid;
            module_rsp_cb = _module_rsp_cb;
        }

        public event Action<Int16> on_choose_dice_cb;
        public event Action on_choose_dice_err;
        public event Action on_choose_dice_timeout;

        public game_client_choose_dice_cb callBack(Action<Int16> cb, Action err)
        {
            on_choose_dice_cb += cb;
            on_choose_dice_err += err;
            return this;
        }

        public void timeout(UInt64 tick, Action timeout_cb)
        {
            TinyTimer.add_timer(tick, ()=>{
                module_rsp_cb.choose_dice_timeout(cb_uuid);
            });
            on_choose_dice_timeout += timeout_cb;
        }

        public void call_cb(Int16 dice_index)
        {
            if (on_choose_dice_cb != null)
            {
                on_choose_dice_cb(dice_index);
            }
        }

        public void call_err()
        {
            if (on_choose_dice_err != null)
            {
                on_choose_dice_err();
            }
        }

        public void call_timeout()
        {
            if (on_choose_dice_timeout != null)
            {
                on_choose_dice_timeout();
            }
        }

    }

/*this cb code is codegen by abelkhan for c#*/
    public class game_client_rsp_cb : common.imodule {
        public Dictionary<UInt64, game_client_choose_dice_cb> map_choose_dice;
        public game_client_rsp_cb() 
        {
            map_choose_dice = new Dictionary<UInt64, game_client_choose_dice_cb>();
            hub.hub._modules.add_mothed("game_client_rsp_cb_choose_dice_rsp", choose_dice_rsp);
            hub.hub._modules.add_mothed("game_client_rsp_cb_choose_dice_err", choose_dice_err);
        }

        public void choose_dice_rsp(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var _dice_index = ((MsgPack.MessagePackObject)inArray[1]).AsInt16();
            var rsp = try_get_and_del_choose_dice_cb(uuid);
            if (rsp != null)
            {
                rsp.call_cb(_dice_index);
            }
        }

        public void choose_dice_err(IList<MsgPack.MessagePackObject> inArray){
            var uuid = ((MsgPack.MessagePackObject)inArray[0]).AsUInt64();
            var rsp = try_get_and_del_choose_dice_cb(uuid);
            if (rsp != null)
            {
                rsp.call_err();
            }
        }

        public void choose_dice_timeout(UInt64 cb_uuid){
            var rsp = try_get_and_del_choose_dice_cb(cb_uuid);
            if (rsp != null){
                rsp.call_timeout();
            }
        }

        private game_client_choose_dice_cb try_get_and_del_choose_dice_cb(UInt64 uuid){
            lock(map_choose_dice)
            {
                if (map_choose_dice.TryGetValue(uuid, out game_client_choose_dice_cb rsp))
                {
                    map_choose_dice.Remove(uuid);
                }
                return rsp;
            }
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

        public game_client_choose_dice_cb choose_dice(){
            var uuid_3ce28ca0_8b60_5302_9362_48ea595b7a44 = (UInt64)Interlocked.Increment(ref uuid_b99eae25_99b5_3006_b19c_ccf531aff983);

            var _argv_ffefe8e1_59c2_3292_8600_93dfa9b71e7f = new ArrayList();
            _argv_ffefe8e1_59c2_3292_8600_93dfa9b71e7f.Add(uuid_3ce28ca0_8b60_5302_9362_48ea595b7a44);
            hub.hub._gates.call_client(client_uuid_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_choose_dice", _argv_ffefe8e1_59c2_3292_8600_93dfa9b71e7f);

            var cb_choose_dice_obj = new game_client_choose_dice_cb(uuid_3ce28ca0_8b60_5302_9362_48ea595b7a44, rsp_cb_game_client_handle);
            lock(rsp_cb_game_client_handle.map_choose_dice)
            {                rsp_cb_game_client_handle.map_choose_dice.Add(uuid_3ce28ca0_8b60_5302_9362_48ea595b7a44, cb_choose_dice_obj);
            }            return cb_choose_dice_obj;
        }

    }

    public class game_client_multicast {
        public List<string> client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983;
        public game_client_rsp_cb rsp_cb_game_client_handle;

        public game_client_multicast(game_client_rsp_cb rsp_cb_game_client_handle_)
        {
            rsp_cb_game_client_handle = rsp_cb_game_client_handle_;
        }

        public void game_wait_start_info(Int32 countdown, playground _playground, List<player_game_info> info){
            var _argv_1de11b0e_6af1_350d_ad38_245a9e2a0a43 = new ArrayList();
            _argv_1de11b0e_6af1_350d_ad38_245a9e2a0a43.Add(countdown);
            _argv_1de11b0e_6af1_350d_ad38_245a9e2a0a43.Add((int)_playground);
            var _array_391fd3d4_2d55_3f5e_9223_7f450a814a15 = new ArrayList();
            foreach(var v_0c15545d_d42a_5fe0_bed7_a9496851e88b in info){
                _array_391fd3d4_2d55_3f5e_9223_7f450a814a15.Add(player_game_info.player_game_info_to_protcol(v_0c15545d_d42a_5fe0_bed7_a9496851e88b));
            }
            _argv_1de11b0e_6af1_350d_ad38_245a9e2a0a43.Add(_array_391fd3d4_2d55_3f5e_9223_7f450a814a15);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_game_wait_start_info", _argv_1de11b0e_6af1_350d_ad38_245a9e2a0a43);
        }

        public void game_info(playground _playground, List<player_game_info> info, Int64 round_player_guid){
            var _argv_a8150bab_ab88_3ac0_b633_425c25e81223 = new ArrayList();
            _argv_a8150bab_ab88_3ac0_b633_425c25e81223.Add((int)_playground);
            var _array_391fd3d4_2d55_3f5e_9223_7f450a814a15 = new ArrayList();
            foreach(var v_0c15545d_d42a_5fe0_bed7_a9496851e88b in info){
                _array_391fd3d4_2d55_3f5e_9223_7f450a814a15.Add(player_game_info.player_game_info_to_protcol(v_0c15545d_d42a_5fe0_bed7_a9496851e88b));
            }
            _argv_a8150bab_ab88_3ac0_b633_425c25e81223.Add(_array_391fd3d4_2d55_3f5e_9223_7f450a814a15);
            _argv_a8150bab_ab88_3ac0_b633_425c25e81223.Add(round_player_guid);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_game_info", _argv_a8150bab_ab88_3ac0_b633_425c25e81223);
        }

        public void ntf_effect_info(List<effect_info> info){
            var _argv_e8275721_ff0f_38f6_97f2_e503533bc36e = new ArrayList();
            var _array_391fd3d4_2d55_3f5e_9223_7f450a814a15 = new ArrayList();
            foreach(var v_0c15545d_d42a_5fe0_bed7_a9496851e88b in info){
                _array_391fd3d4_2d55_3f5e_9223_7f450a814a15.Add(effect_info.effect_info_to_protcol(v_0c15545d_d42a_5fe0_bed7_a9496851e88b));
            }
            _argv_e8275721_ff0f_38f6_97f2_e503533bc36e.Add(_array_391fd3d4_2d55_3f5e_9223_7f450a814a15);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_ntf_effect_info", _argv_e8275721_ff0f_38f6_97f2_e503533bc36e);
        }

        public void ntf_new_effect_info(effect_info info){
            var _argv_fba818df_3af0_36da_a270_f40974bad0a2 = new ArrayList();
            _argv_fba818df_3af0_36da_a270_f40974bad0a2.Add(effect_info.effect_info_to_protcol(info));
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_ntf_new_effect_info", _argv_fba818df_3af0_36da_a270_f40974bad0a2);
        }

        public void turn_player_round(Int64 guid){
            var _argv_ecab320c_0c7a_39d6_86e9_96ecfccda4c1 = new ArrayList();
            _argv_ecab320c_0c7a_39d6_86e9_96ecfccda4c1.Add(guid);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_turn_player_round", _argv_ecab320c_0c7a_39d6_86e9_96ecfccda4c1);
        }

        public void throw_dice(Int64 guid, List<Int32> dice){
            var _argv_89caa8aa_910b_3726_9283_63467ea68426 = new ArrayList();
            _argv_89caa8aa_910b_3726_9283_63467ea68426.Add(guid);
            var _array_50efb5f9_e76d_39f6_a8f5_087df183aa5b = new ArrayList();
            foreach(var v_6f8b15a1_8afa_550d_9b21_68c8187be9d8 in dice){
                _array_50efb5f9_e76d_39f6_a8f5_087df183aa5b.Add(v_6f8b15a1_8afa_550d_9b21_68c8187be9d8);
            }
            _argv_89caa8aa_910b_3726_9283_63467ea68426.Add(_array_50efb5f9_e76d_39f6_a8f5_087df183aa5b);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_throw_dice", _argv_89caa8aa_910b_3726_9283_63467ea68426);
        }

        public void rabbit_choose_dice(Int32 dice){
            var _argv_61d85040_12b5_380a_9077_58950d26e18b = new ArrayList();
            _argv_61d85040_12b5_380a_9077_58950d26e18b.Add(dice);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_rabbit_choose_dice", _argv_61d85040_12b5_380a_9077_58950d26e18b);
        }

        public void move(Int64 guid, Int16 animal_index, Int32 from, Int32 to){
            var _argv_33efb72e_9227_32af_a058_169be114a277 = new ArrayList();
            _argv_33efb72e_9227_32af_a058_169be114a277.Add(guid);
            _argv_33efb72e_9227_32af_a058_169be114a277.Add(animal_index);
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

        public void use_skill(Int64 guid, Int64 target_guid, Int16 target_animal_index){
            var _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe = new ArrayList();
            _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe.Add(guid);
            _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe.Add(target_guid);
            _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe.Add(target_animal_index);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_use_skill", _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe);
        }

        public void reset_position(List<player_game_info> info){
            var _argv_8e6fd7da_b0c0_3084_a608_af3c644d3fcd = new ArrayList();
            var _array_391fd3d4_2d55_3f5e_9223_7f450a814a15 = new ArrayList();
            foreach(var v_0c15545d_d42a_5fe0_bed7_a9496851e88b in info){
                _array_391fd3d4_2d55_3f5e_9223_7f450a814a15.Add(player_game_info.player_game_info_to_protcol(v_0c15545d_d42a_5fe0_bed7_a9496851e88b));
            }
            _argv_8e6fd7da_b0c0_3084_a608_af3c644d3fcd.Add(_array_391fd3d4_2d55_3f5e_9223_7f450a814a15);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_reset_position", _argv_8e6fd7da_b0c0_3084_a608_af3c644d3fcd);
        }

        public void effect_move(effect effect_id, Int64 guid, Int16 target_animal_index, Int32 from, Int32 to){
            var _argv_275504eb_206b_39cf_a228_7410dadf83b7 = new ArrayList();
            _argv_275504eb_206b_39cf_a228_7410dadf83b7.Add((int)effect_id);
            _argv_275504eb_206b_39cf_a228_7410dadf83b7.Add(guid);
            _argv_275504eb_206b_39cf_a228_7410dadf83b7.Add(target_animal_index);
            _argv_275504eb_206b_39cf_a228_7410dadf83b7.Add(from);
            _argv_275504eb_206b_39cf_a228_7410dadf83b7.Add(to);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_effect_move", _argv_275504eb_206b_39cf_a228_7410dadf83b7);
        }

        public void use_props(Int64 guid, props props_id, Int64 target_guid, Int16 target_animal_index){
            var _argv_20fdd6aa_1127_36f5_b101_2ce394d2e1c9 = new ArrayList();
            _argv_20fdd6aa_1127_36f5_b101_2ce394d2e1c9.Add(guid);
            _argv_20fdd6aa_1127_36f5_b101_2ce394d2e1c9.Add((int)props_id);
            _argv_20fdd6aa_1127_36f5_b101_2ce394d2e1c9.Add(target_guid);
            _argv_20fdd6aa_1127_36f5_b101_2ce394d2e1c9.Add(target_animal_index);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_use_props", _argv_20fdd6aa_1127_36f5_b101_2ce394d2e1c9);
        }

        public void add_props(enum_add_props_type add_type, Int64 guid, props props_id){
            var _argv_14a91df5_0d98_382a_9dfd_5ad28895e731 = new ArrayList();
            _argv_14a91df5_0d98_382a_9dfd_5ad28895e731.Add((int)add_type);
            _argv_14a91df5_0d98_382a_9dfd_5ad28895e731.Add(guid);
            _argv_14a91df5_0d98_382a_9dfd_5ad28895e731.Add((int)props_id);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_add_props", _argv_14a91df5_0d98_382a_9dfd_5ad28895e731);
        }

        public void reverse_props(Int64 src_guid, Int64 target_guid, props props_id, Int64 reverse_target_guid, Int16 reverse_target_animal_index){
            var _argv_729da852_62b2_37ba_b119_feec1b0d80bb = new ArrayList();
            _argv_729da852_62b2_37ba_b119_feec1b0d80bb.Add(src_guid);
            _argv_729da852_62b2_37ba_b119_feec1b0d80bb.Add(target_guid);
            _argv_729da852_62b2_37ba_b119_feec1b0d80bb.Add((int)props_id);
            _argv_729da852_62b2_37ba_b119_feec1b0d80bb.Add(reverse_target_guid);
            _argv_729da852_62b2_37ba_b119_feec1b0d80bb.Add(reverse_target_animal_index);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_reverse_props", _argv_729da852_62b2_37ba_b119_feec1b0d80bb);
        }

        public void immunity_props(Int64 guid, props props_id, Int64 target_guid, Int16 target_animal_index){
            var _argv_2888feac_1d9b_3c9f_9a00_e626b2c72788 = new ArrayList();
            _argv_2888feac_1d9b_3c9f_9a00_e626b2c72788.Add(guid);
            _argv_2888feac_1d9b_3c9f_9a00_e626b2c72788.Add((int)props_id);
            _argv_2888feac_1d9b_3c9f_9a00_e626b2c72788.Add(target_guid);
            _argv_2888feac_1d9b_3c9f_9a00_e626b2c72788.Add(target_animal_index);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_immunity_props", _argv_2888feac_1d9b_3c9f_9a00_e626b2c72788);
        }

        public void can_not_active_this_round(Int64 guid){
            var _argv_8809815d_02f3_3d59_8267_5fa68554d68a = new ArrayList();
            _argv_8809815d_02f3_3d59_8267_5fa68554d68a.Add(guid);
            hub.hub._gates.call_group_client(client_uuids_b99eae25_99b5_3006_b19c_ccf531aff983, "game_client_can_not_active_this_round", _argv_8809815d_02f3_3d59_8267_5fa68554d68a);
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
