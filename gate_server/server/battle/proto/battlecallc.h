#ifndef _h_battlecallc_b5be201a_71af_3e96_ba53_7d00cff19704_
#define _h_battlecallc_b5be201a_71af_3e96_ba53_7d00cff19704_

#include <hub_service.h>
#include <signals.h>

#include "common.h"

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this caller code is codegen by abelkhan codegen for cpp*/
/*this cb code is codegen by abelkhan for cpp*/
    class battle_client_rsp_cb : public common::imodule, public std::enable_shared_from_this<battle_client_rsp_cb>{
    public:
        battle_client_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class battle_client_clientproxy
{
    public:
        std::string client_uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124;
        std::atomic<uint64_t> uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124;

        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<battle_client_rsp_cb> rsp_cb_battle_client_handle;

        battle_client_clientproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<battle_client_rsp_cb> rsp_cb_battle_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_battle_client_handle = rsp_cb_battle_client_handle_;
            uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124.store(random());

        }

        void be_displacement(){
            msgpack11::MsgPack::array _argv_156d31bb_d697_3042_a3e8_88d0a5d0484c;
            _hub_handle->_gatemng->call_client(client_uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_be_displacement", _argv_156d31bb_d697_3042_a3e8_88d0a5d0484c);
        }

        void main_role_info_ntf(main_role_info _role_info){
            msgpack11::MsgPack::array _argv_20d5813d_0c33_3fdf_bcb5_1b66e1c465ab;
            _argv_20d5813d_0c33_3fdf_bcb5_1b66e1c465ab.push_back(main_role_info::main_role_info_to_protcol(_role_info));
            _hub_handle->_gatemng->call_client(client_uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_main_role_info_ntf", _argv_20d5813d_0c33_3fdf_bcb5_1b66e1c465ab);
        }

        void battle_start(){
            msgpack11::MsgPack::array _argv_36bbe5d5_6397_3ec0_bcee_cffc6c619d86;
            _hub_handle->_gatemng->call_client(client_uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_battle_start", _argv_36bbe5d5_6397_3ec0_bcee_cffc6c619d86);
        }

        void role_gun_info(std::string gun_uuid, int32_t bullet_num){
            msgpack11::MsgPack::array _argv_040dc927_70de_3239_90c0_ed646e0d8607;
            _argv_040dc927_70de_3239_90c0_ed646e0d8607.push_back(gun_uuid);
            _argv_040dc927_70de_3239_90c0_ed646e0d8607.push_back(bullet_num);
            _hub_handle->_gatemng->call_client(client_uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_role_gun_info", _argv_040dc927_70de_3239_90c0_ed646e0d8607);
        }

        void role_grenade_num(int32_t grenade_num){
            msgpack11::MsgPack::array _argv_d3ed58b3_bddc_3c4b_b2c6_722847431c99;
            _argv_d3ed58b3_bddc_3c4b_b2c6_722847431c99.push_back(grenade_num);
            _hub_handle->_gatemng->call_client(client_uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_role_grenade_num", _argv_d3ed58b3_bddc_3c4b_b2c6_722847431c99);
        }

        void in_out_house(int32_t state){
            msgpack11::MsgPack::array _argv_55305a75_a6bb_365f_9403_f8e1e12e2286;
            _argv_55305a75_a6bb_365f_9403_f8e1e12e2286.push_back(state);
            _hub_handle->_gatemng->call_client(client_uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_in_out_house", _argv_55305a75_a6bb_365f_9403_f8e1e12e2286);
        }

        void role_use_skill(std::string skill_name){
            msgpack11::MsgPack::array _argv_d6d0fc8d_6420_3681_9977_974d5c6a4af4;
            _argv_d6d0fc8d_6420_3681_9977_974d5c6a4af4.push_back(skill_name);
            _hub_handle->_gatemng->call_client(client_uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_role_use_skill", _argv_d6d0fc8d_6420_3681_9977_974d5c6a4af4);
        }

        void bag_info(std::vector<item> item_list){
            msgpack11::MsgPack::array _argv_45e1916e_6991_3fbf_86b8_ea4c1f1adac1;
            msgpack11::MsgPack::array _array_8eac3ee2_4399_3b84_ba03_10f6017cfb15;
            for(auto v_f3ec0616_9c26_5a3d_9269_d87822e12262 : item_list){
                _array_8eac3ee2_4399_3b84_ba03_10f6017cfb15.push_back(item::item_to_protcol(v_f3ec0616_9c26_5a3d_9269_d87822e12262));
            }
            _argv_45e1916e_6991_3fbf_86b8_ea4c1f1adac1.push_back(_array_8eac3ee2_4399_3b84_ba03_10f6017cfb15);
            _hub_handle->_gatemng->call_client(client_uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_bag_info", _argv_45e1916e_6991_3fbf_86b8_ea4c1f1adac1);
        }

        void battle_info(role_battle_info battle_info){
            msgpack11::MsgPack::array _argv_504125a2_a75d_3fa2_9a35_a9fdc5331928;
            _argv_504125a2_a75d_3fa2_9a35_a9fdc5331928.push_back(role_battle_info::role_battle_info_to_protcol(battle_info));
            _hub_handle->_gatemng->call_client(client_uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_battle_info", _argv_504125a2_a75d_3fa2_9a35_a9fdc5331928);
        }

        void balance(int32_t rank, int32_t kill_num){
            msgpack11::MsgPack::array _argv_b4af6052_ccc5_303b_a671_32052d4e5d36;
            _argv_b4af6052_ccc5_303b_a671_32052d4e5d36.push_back(rank);
            _argv_b4af6052_ccc5_303b_a671_32052d4e5d36.push_back(kill_num);
            _hub_handle->_gatemng->call_client(client_uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_balance", _argv_b4af6052_ccc5_303b_a671_32052d4e5d36);
        }

    };

    class battle_client_multicast
{
    public:
        std::vector<std::string> client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124;
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<battle_client_rsp_cb> rsp_cb_battle_client_handle;

        battle_client_multicast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<battle_client_rsp_cb> rsp_cb_battle_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_battle_client_handle = rsp_cb_battle_client_handle_;
        }

        void field_info(std::vector<role_info> field_list){
            msgpack11::MsgPack::array _argv_a8989d99_1a7f_3e2a_821a_37e0d16c9a83;
            msgpack11::MsgPack::array _array_08b837ca_a893_3345_b002_ac378832736e;
            for(auto v_c4bef4c9_ccd7_514a_8242_2dcc0868d70f : field_list){
                _array_08b837ca_a893_3345_b002_ac378832736e.push_back(role_info::role_info_to_protcol(v_c4bef4c9_ccd7_514a_8242_2dcc0868d70f));
            }
            _argv_a8989d99_1a7f_3e2a_821a_37e0d16c9a83.push_back(_array_08b837ca_a893_3345_b002_ac378832736e);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_field_info", _argv_a8989d99_1a7f_3e2a_821a_37e0d16c9a83);
        }

        void leave_field_info(std::vector<std::string> field_list){
            msgpack11::MsgPack::array _argv_6cf5262b_91da_3105_b05d_26b551438949;
            msgpack11::MsgPack::array _array_08b837ca_a893_3345_b002_ac378832736e;
            for(auto v_c4bef4c9_ccd7_514a_8242_2dcc0868d70f : field_list){
                _array_08b837ca_a893_3345_b002_ac378832736e.push_back(v_c4bef4c9_ccd7_514a_8242_2dcc0868d70f);
            }
            _argv_6cf5262b_91da_3105_b05d_26b551438949.push_back(_array_08b837ca_a893_3345_b002_ac378832736e);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_leave_field_info", _argv_6cf5262b_91da_3105_b05d_26b551438949);
        }

        void role_move_status(std::string id, int32_t x, int32_t y, bool is_squat, int32_t direction, int32_t move_speed, int32_t jump, int32_t jump_speed, int32_t ladder, int32_t ladder_speed, int64_t timetmp){
            msgpack11::MsgPack::array _argv_ec137da3_49f9_30f2_bdc9_ca7fe817ef6f;
            _argv_ec137da3_49f9_30f2_bdc9_ca7fe817ef6f.push_back(id);
            _argv_ec137da3_49f9_30f2_bdc9_ca7fe817ef6f.push_back(x);
            _argv_ec137da3_49f9_30f2_bdc9_ca7fe817ef6f.push_back(y);
            _argv_ec137da3_49f9_30f2_bdc9_ca7fe817ef6f.push_back(is_squat);
            _argv_ec137da3_49f9_30f2_bdc9_ca7fe817ef6f.push_back(direction);
            _argv_ec137da3_49f9_30f2_bdc9_ca7fe817ef6f.push_back(move_speed);
            _argv_ec137da3_49f9_30f2_bdc9_ca7fe817ef6f.push_back(jump);
            _argv_ec137da3_49f9_30f2_bdc9_ca7fe817ef6f.push_back(jump_speed);
            _argv_ec137da3_49f9_30f2_bdc9_ca7fe817ef6f.push_back(ladder);
            _argv_ec137da3_49f9_30f2_bdc9_ca7fe817ef6f.push_back(ladder_speed);
            _argv_ec137da3_49f9_30f2_bdc9_ca7fe817ef6f.push_back(timetmp);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_role_move_status", _argv_ec137da3_49f9_30f2_bdc9_ca7fe817ef6f);
        }

        void role_skill_info(std::string id, std::string skill_name, int64_t timetmp){
            msgpack11::MsgPack::array _argv_8f043adf_566c_3fb0_830c_6411824271a2;
            _argv_8f043adf_566c_3fb0_830c_6411824271a2.push_back(id);
            _argv_8f043adf_566c_3fb0_830c_6411824271a2.push_back(skill_name);
            _argv_8f043adf_566c_3fb0_830c_6411824271a2.push_back(timetmp);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_role_skill_info", _argv_8f043adf_566c_3fb0_830c_6411824271a2);
        }

        void role_aim_status(std::string id, int32_t gun, int32_t angle){
            msgpack11::MsgPack::array _argv_5138263d_ba2b_3cea_83c0_3b88004d4265;
            _argv_5138263d_ba2b_3cea_83c0_3b88004d4265.push_back(id);
            _argv_5138263d_ba2b_3cea_83c0_3b88004d4265.push_back(gun);
            _argv_5138263d_ba2b_3cea_83c0_3b88004d4265.push_back(angle);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_role_aim_status", _argv_5138263d_ba2b_3cea_83c0_3b88004d4265);
        }

        void role_orientation_status(std::string id, int32_t direction){
            msgpack11::MsgPack::array _argv_8c8b05f9_b7b2_37b4_b5fb_d31a06c422b2;
            _argv_8c8b05f9_b7b2_37b4_b5fb_d31a06c422b2.push_back(id);
            _argv_8c8b05f9_b7b2_37b4_b5fb_d31a06c422b2.push_back(direction);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_role_orientation_status", _argv_8c8b05f9_b7b2_37b4_b5fb_d31a06c422b2);
        }

        void role_immediately_shoot_player(std::string id, int32_t gun, int32_t angle, int32_t x, int32_t y, role_info behiter){
            msgpack11::MsgPack::array _argv_6cddbfc8_6149_33af_9cd5_c2714aabdb14;
            _argv_6cddbfc8_6149_33af_9cd5_c2714aabdb14.push_back(id);
            _argv_6cddbfc8_6149_33af_9cd5_c2714aabdb14.push_back(gun);
            _argv_6cddbfc8_6149_33af_9cd5_c2714aabdb14.push_back(angle);
            _argv_6cddbfc8_6149_33af_9cd5_c2714aabdb14.push_back(x);
            _argv_6cddbfc8_6149_33af_9cd5_c2714aabdb14.push_back(y);
            _argv_6cddbfc8_6149_33af_9cd5_c2714aabdb14.push_back(role_info::role_info_to_protcol(behiter));
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_role_immediately_shoot_player", _argv_6cddbfc8_6149_33af_9cd5_c2714aabdb14);
        }

        void role_immediately_shoot_miss(std::string id, int32_t gun, int32_t angle, int32_t x, int32_t y, int32_t end_x, int32_t end_y){
            msgpack11::MsgPack::array _argv_127ea1f0_4ab3_3b45_87bd_37d7afa176c1;
            _argv_127ea1f0_4ab3_3b45_87bd_37d7afa176c1.push_back(id);
            _argv_127ea1f0_4ab3_3b45_87bd_37d7afa176c1.push_back(gun);
            _argv_127ea1f0_4ab3_3b45_87bd_37d7afa176c1.push_back(angle);
            _argv_127ea1f0_4ab3_3b45_87bd_37d7afa176c1.push_back(x);
            _argv_127ea1f0_4ab3_3b45_87bd_37d7afa176c1.push_back(y);
            _argv_127ea1f0_4ab3_3b45_87bd_37d7afa176c1.push_back(end_x);
            _argv_127ea1f0_4ab3_3b45_87bd_37d7afa176c1.push_back(end_y);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_role_immediately_shoot_miss", _argv_127ea1f0_4ab3_3b45_87bd_37d7afa176c1);
        }

        void role_immediately_shoot_map_element(std::string id, int32_t gun, int32_t angle, int32_t x, int32_t y, house_info map_element){
            msgpack11::MsgPack::array _argv_c9bf73c1_2031_3ac5_953b_6c6f526eb169;
            _argv_c9bf73c1_2031_3ac5_953b_6c6f526eb169.push_back(id);
            _argv_c9bf73c1_2031_3ac5_953b_6c6f526eb169.push_back(gun);
            _argv_c9bf73c1_2031_3ac5_953b_6c6f526eb169.push_back(angle);
            _argv_c9bf73c1_2031_3ac5_953b_6c6f526eb169.push_back(x);
            _argv_c9bf73c1_2031_3ac5_953b_6c6f526eb169.push_back(y);
            _argv_c9bf73c1_2031_3ac5_953b_6c6f526eb169.push_back(house_info::house_info_to_protcol(map_element));
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_role_immediately_shoot_map_element", _argv_c9bf73c1_2031_3ac5_953b_6c6f526eb169);
        }

        void bullet_fly(std::string uuid, int32_t gun_id, int32_t bullet_id, int32_t x, int32_t y, int32_t speed_x, int32_t speed_y){
            msgpack11::MsgPack::array _argv_24c5c70c_c120_3c91_842c_d49595e15c61;
            _argv_24c5c70c_c120_3c91_842c_d49595e15c61.push_back(uuid);
            _argv_24c5c70c_c120_3c91_842c_d49595e15c61.push_back(gun_id);
            _argv_24c5c70c_c120_3c91_842c_d49595e15c61.push_back(bullet_id);
            _argv_24c5c70c_c120_3c91_842c_d49595e15c61.push_back(x);
            _argv_24c5c70c_c120_3c91_842c_d49595e15c61.push_back(y);
            _argv_24c5c70c_c120_3c91_842c_d49595e15c61.push_back(speed_x);
            _argv_24c5c70c_c120_3c91_842c_d49595e15c61.push_back(speed_y);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_bullet_fly", _argv_24c5c70c_c120_3c91_842c_d49595e15c61);
        }

        void bullet_hide(std::string uuid, int32_t bullet_id, int32_t x, int32_t y){
            msgpack11::MsgPack::array _argv_ca7d1339_f452_3af0_8c47_bb93ed3721b1;
            _argv_ca7d1339_f452_3af0_8c47_bb93ed3721b1.push_back(uuid);
            _argv_ca7d1339_f452_3af0_8c47_bb93ed3721b1.push_back(bullet_id);
            _argv_ca7d1339_f452_3af0_8c47_bb93ed3721b1.push_back(x);
            _argv_ca7d1339_f452_3af0_8c47_bb93ed3721b1.push_back(y);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_bullet_hide", _argv_ca7d1339_f452_3af0_8c47_bb93ed3721b1);
        }

        void bullet_hit_elements(std::string uuid, int32_t bullet_id, int32_t x, int32_t y, std::vector<role_info> elements){
            msgpack11::MsgPack::array _argv_78236b2c_cee4_32cf_ba64_f39ae2bd5310;
            _argv_78236b2c_cee4_32cf_ba64_f39ae2bd5310.push_back(uuid);
            _argv_78236b2c_cee4_32cf_ba64_f39ae2bd5310.push_back(bullet_id);
            _argv_78236b2c_cee4_32cf_ba64_f39ae2bd5310.push_back(x);
            _argv_78236b2c_cee4_32cf_ba64_f39ae2bd5310.push_back(y);
            msgpack11::MsgPack::array _array_6bf40faa_ad8e_301d_aaca_eec64fbb02ac;
            for(auto v_4cac9942_8eaa_53c3_8f04_02d410a816c7 : elements){
                _array_6bf40faa_ad8e_301d_aaca_eec64fbb02ac.push_back(role_info::role_info_to_protcol(v_4cac9942_8eaa_53c3_8f04_02d410a816c7));
            }
            _argv_78236b2c_cee4_32cf_ba64_f39ae2bd5310.push_back(_array_6bf40faa_ad8e_301d_aaca_eec64fbb02ac);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_bullet_hit_elements", _argv_78236b2c_cee4_32cf_ba64_f39ae2bd5310);
        }

        void bullet_hit_house(std::string uuid, int32_t bullet_id, int32_t x, int32_t y, std::vector<house_info> elements){
            msgpack11::MsgPack::array _argv_16c9d0e0_4265_3842_a0aa_f41f924b07a0;
            _argv_16c9d0e0_4265_3842_a0aa_f41f924b07a0.push_back(uuid);
            _argv_16c9d0e0_4265_3842_a0aa_f41f924b07a0.push_back(bullet_id);
            _argv_16c9d0e0_4265_3842_a0aa_f41f924b07a0.push_back(x);
            _argv_16c9d0e0_4265_3842_a0aa_f41f924b07a0.push_back(y);
            msgpack11::MsgPack::array _array_6bf40faa_ad8e_301d_aaca_eec64fbb02ac;
            for(auto v_4cac9942_8eaa_53c3_8f04_02d410a816c7 : elements){
                _array_6bf40faa_ad8e_301d_aaca_eec64fbb02ac.push_back(house_info::house_info_to_protcol(v_4cac9942_8eaa_53c3_8f04_02d410a816c7));
            }
            _argv_16c9d0e0_4265_3842_a0aa_f41f924b07a0.push_back(_array_6bf40faa_ad8e_301d_aaca_eec64fbb02ac);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_bullet_hit_house", _argv_16c9d0e0_4265_3842_a0aa_f41f924b07a0);
        }

        void bullet_hit_map_box(std::string uuid, int32_t bullet_id, int32_t x, int32_t y, std::vector<house_info> elements){
            msgpack11::MsgPack::array _argv_dd9ad1b4_7be0_3c7f_9b72_73ef48029849;
            _argv_dd9ad1b4_7be0_3c7f_9b72_73ef48029849.push_back(uuid);
            _argv_dd9ad1b4_7be0_3c7f_9b72_73ef48029849.push_back(bullet_id);
            _argv_dd9ad1b4_7be0_3c7f_9b72_73ef48029849.push_back(x);
            _argv_dd9ad1b4_7be0_3c7f_9b72_73ef48029849.push_back(y);
            msgpack11::MsgPack::array _array_6bf40faa_ad8e_301d_aaca_eec64fbb02ac;
            for(auto v_4cac9942_8eaa_53c3_8f04_02d410a816c7 : elements){
                _array_6bf40faa_ad8e_301d_aaca_eec64fbb02ac.push_back(house_info::house_info_to_protcol(v_4cac9942_8eaa_53c3_8f04_02d410a816c7));
            }
            _argv_dd9ad1b4_7be0_3c7f_9b72_73ef48029849.push_back(_array_6bf40faa_ad8e_301d_aaca_eec64fbb02ac);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_bullet_hit_map_box", _argv_dd9ad1b4_7be0_3c7f_9b72_73ef48029849);
        }

        void bullet_hit_miss(std::string uuid, int32_t bullet_id, int32_t end_x, int32_t end_y){
            msgpack11::MsgPack::array _argv_575fc4df_59fb_37f0_98e6_387b2c7e168c;
            _argv_575fc4df_59fb_37f0_98e6_387b2c7e168c.push_back(uuid);
            _argv_575fc4df_59fb_37f0_98e6_387b2c7e168c.push_back(bullet_id);
            _argv_575fc4df_59fb_37f0_98e6_387b2c7e168c.push_back(end_x);
            _argv_575fc4df_59fb_37f0_98e6_387b2c7e168c.push_back(end_y);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_bullet_hit_miss", _argv_575fc4df_59fb_37f0_98e6_387b2c7e168c);
        }

        void role_hp_change(std::string uuid, int32_t hp){
            msgpack11::MsgPack::array _argv_e82b7eaf_cb82_35fb_a192_20707434cbcd;
            _argv_e82b7eaf_cb82_35fb_a192_20707434cbcd.push_back(uuid);
            _argv_e82b7eaf_cb82_35fb_a192_20707434cbcd.push_back(hp);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_role_hp_change", _argv_e82b7eaf_cb82_35fb_a192_20707434cbcd);
        }

        void drop_item_list(std::vector<drop_item_info> drop_item_list){
            msgpack11::MsgPack::array _argv_04739402_610f_3b58_8baf_541fbbeff588;
            msgpack11::MsgPack::array _array_04739402_610f_3b58_8baf_541fbbeff588;
            for(auto v_ba6e503f_48f3_549f_b741_43c063d98bd7 : drop_item_list){
                _array_04739402_610f_3b58_8baf_541fbbeff588.push_back(drop_item_info::drop_item_info_to_protcol(v_ba6e503f_48f3_549f_b741_43c063d98bd7));
            }
            _argv_04739402_610f_3b58_8baf_541fbbeff588.push_back(_array_04739402_610f_3b58_8baf_541fbbeff588);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_drop_item_list", _argv_04739402_610f_3b58_8baf_541fbbeff588);
        }

        void be_wreck_box(std::string layer, std::vector<wreck_box_info> wreck_box_list){
            msgpack11::MsgPack::array _argv_e28f2c8a_866f_3e11_a48f_a6648c642a77;
            _argv_e28f2c8a_866f_3e11_a48f_a6648c642a77.push_back(layer);
            msgpack11::MsgPack::array _array_8415cf24_7dc5_374a_8035_fc98911da894;
            for(auto v_2ec6626e_cd4a_58c5_9df3_32fa96f8a408 : wreck_box_list){
                _array_8415cf24_7dc5_374a_8035_fc98911da894.push_back(wreck_box_info::wreck_box_info_to_protcol(v_2ec6626e_cd4a_58c5_9df3_32fa96f8a408));
            }
            _argv_e28f2c8a_866f_3e11_a48f_a6648c642a77.push_back(_array_8415cf24_7dc5_374a_8035_fc98911da894);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_be_wreck_box", _argv_e28f2c8a_866f_3e11_a48f_a6648c642a77);
        }

        void refresh_poison(int32_t poison_left, int32_t poison_right, int32_t next_poison_left, int32_t next_poison_right){
            msgpack11::MsgPack::array _argv_42bfabe2_5529_3694_9a1a_3de07839bd7a;
            _argv_42bfabe2_5529_3694_9a1a_3de07839bd7a.push_back(poison_left);
            _argv_42bfabe2_5529_3694_9a1a_3de07839bd7a.push_back(poison_right);
            _argv_42bfabe2_5529_3694_9a1a_3de07839bd7a.push_back(next_poison_left);
            _argv_42bfabe2_5529_3694_9a1a_3de07839bd7a.push_back(next_poison_right);
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_refresh_poison", _argv_42bfabe2_5529_3694_9a1a_3de07839bd7a);
        }

        void back_match(std::string match_hub_name, match_team team_info){
            msgpack11::MsgPack::array _argv_3e64467f_f3a9_3216_907f_0e9bfd6381fc;
            _argv_3e64467f_f3a9_3216_907f_0e9bfd6381fc.push_back(match_hub_name);
            _argv_3e64467f_f3a9_3216_907f_0e9bfd6381fc.push_back(match_team::match_team_to_protcol(team_info));
            _hub_handle->_gatemng->call_group_client(client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124, "battle_client_back_match", _argv_3e64467f_f3a9_3216_907f_0e9bfd6381fc);
        }

    };

    class battle_client_broadcast
{
    public:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<battle_client_rsp_cb> rsp_cb_battle_client_handle;

        battle_client_broadcast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<battle_client_rsp_cb> rsp_cb_battle_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_battle_client_handle = rsp_cb_battle_client_handle_;
        }

    };

    class battle_client_clientproxy;
    class battle_client_multicast;
    class battle_client_broadcast;
    class battle_client_caller {
    private:
        static std::shared_ptr<battle_client_rsp_cb> rsp_cb_battle_client_handle;

    private:
        std::shared_ptr<battle_client_clientproxy> _clientproxy;
        std::shared_ptr<battle_client_multicast> _multicast;
        std::shared_ptr<battle_client_broadcast> _broadcast;

    public:
        battle_client_caller(std::shared_ptr<hub::hub_service> hub_service_) 
        {
            if (rsp_cb_battle_client_handle == nullptr) {
                rsp_cb_battle_client_handle = std::make_shared<battle_client_rsp_cb>();
                rsp_cb_battle_client_handle->Init(hub_service_);
            }
            _clientproxy = std::make_shared<battle_client_clientproxy>(hub_service_, rsp_cb_battle_client_handle);
            _multicast = std::make_shared<battle_client_multicast>(hub_service_, rsp_cb_battle_client_handle);
            _broadcast = std::make_shared<battle_client_broadcast>(hub_service_, rsp_cb_battle_client_handle);
        }

        std::shared_ptr<battle_client_clientproxy> get_client(std::string client_uuid) {
            _clientproxy->client_uuid_268d2967_7c6f_34d2_80c7_77a6da2f6124 = client_uuid;
            return _clientproxy;
        }

        std::shared_ptr<battle_client_multicast> get_multicast(std::vector<std::string> client_uuids) {
            _multicast->client_uuids_268d2967_7c6f_34d2_80c7_77a6da2f6124 = client_uuids;
            return _multicast;
        }

        std::shared_ptr<battle_client_broadcast> get_broadcast() {
            return _broadcast;
        }

    };

}

#endif //_h_battlecallc_b5be201a_71af_3e96_ba53_7d00cff19704_
