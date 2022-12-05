#ifndef _h_ccallbattle_0d637c09_0ee7_333b_99f9_b450dd48eabc_
#define _h_ccallbattle_0d637c09_0ee7_333b_99f9_b450dd48eabc_

#include <hub_service.h>
#include <signals.h>

#include "common.h"

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this module code is codegen by abelkhan codegen for cpp*/
    class battle_ping_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _client_cuuid_ca6794ee_a403_309d_b40e_f37578d53e8d;
        uint64_t uuid_94d71f95_a670_3916_89a9_44df18fb711b;

    public:
        battle_ping_rsp(std::shared_ptr<hub::hub_service> _hub, std::string client_cuuid, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _client_cuuid_ca6794ee_a403_309d_b40e_f37578d53e8d = client_cuuid;
            uuid_94d71f95_a670_3916_89a9_44df18fb711b = _uuid;
        }

        void rsp(){
            msgpack11::MsgPack::array _argv_ca6794ee_a403_309d_b40e_f37578d53e8d;
            _argv_ca6794ee_a403_309d_b40e_f37578d53e8d.push_back(uuid_94d71f95_a670_3916_89a9_44df18fb711b);
            _hub_handle->_gatemng->call_client(_client_cuuid_ca6794ee_a403_309d_b40e_f37578d53e8d, "battle_rsp_cb_ping_rsp", _argv_ca6794ee_a403_309d_b40e_f37578d53e8d);
        }

        void err(int32_t err_code){
            msgpack11::MsgPack::array _argv_ca6794ee_a403_309d_b40e_f37578d53e8d;
            _argv_ca6794ee_a403_309d_b40e_f37578d53e8d.push_back(uuid_94d71f95_a670_3916_89a9_44df18fb711b);
            _argv_ca6794ee_a403_309d_b40e_f37578d53e8d.push_back(err_code);
            _hub_handle->_gatemng->call_client(_client_cuuid_ca6794ee_a403_309d_b40e_f37578d53e8d, "battle_rsp_cb_ping_err", _argv_ca6794ee_a403_309d_b40e_f37578d53e8d);
        }

    };

    class battle_get_bag_info_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _client_cuuid_d1ef2382_172d_381b_a6a5_f199d980d60c;
        uint64_t uuid_d9b65413_91bd_3721_a1e3_9213bea76da5;

    public:
        battle_get_bag_info_rsp(std::shared_ptr<hub::hub_service> _hub, std::string client_cuuid, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _client_cuuid_d1ef2382_172d_381b_a6a5_f199d980d60c = client_cuuid;
            uuid_d9b65413_91bd_3721_a1e3_9213bea76da5 = _uuid;
        }

        void rsp(std::vector<item> item_list){
            msgpack11::MsgPack::array _argv_d1ef2382_172d_381b_a6a5_f199d980d60c;
            _argv_d1ef2382_172d_381b_a6a5_f199d980d60c.push_back(uuid_d9b65413_91bd_3721_a1e3_9213bea76da5);
            msgpack11::MsgPack::array _array_8eac3ee2_4399_3b84_ba03_10f6017cfb15;
            for(auto v_554db26f_d17f_5131_8b53_53629acae87f : item_list){
                _array_8eac3ee2_4399_3b84_ba03_10f6017cfb15.push_back(item::item_to_protcol(v_554db26f_d17f_5131_8b53_53629acae87f));
            }
            _argv_d1ef2382_172d_381b_a6a5_f199d980d60c.push_back(_array_8eac3ee2_4399_3b84_ba03_10f6017cfb15);
            _hub_handle->_gatemng->call_client(_client_cuuid_d1ef2382_172d_381b_a6a5_f199d980d60c, "battle_rsp_cb_get_bag_info_rsp", _argv_d1ef2382_172d_381b_a6a5_f199d980d60c);
        }

        void err(int32_t err_code){
            msgpack11::MsgPack::array _argv_d1ef2382_172d_381b_a6a5_f199d980d60c;
            _argv_d1ef2382_172d_381b_a6a5_f199d980d60c.push_back(uuid_d9b65413_91bd_3721_a1e3_9213bea76da5);
            _argv_d1ef2382_172d_381b_a6a5_f199d980d60c.push_back(err_code);
            _hub_handle->_gatemng->call_client(_client_cuuid_d1ef2382_172d_381b_a6a5_f199d980d60c, "battle_rsp_cb_get_bag_info_err", _argv_d1ef2382_172d_381b_a6a5_f199d980d60c);
        }

    };

    class battle_get_battle_info_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _client_cuuid_0e0198b7_cc8a_3e12_8988_98d6e19d9c0e;
        uint64_t uuid_e9214878_12c6_3b16_8e1f_24e296838704;

    public:
        battle_get_battle_info_rsp(std::shared_ptr<hub::hub_service> _hub, std::string client_cuuid, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _client_cuuid_0e0198b7_cc8a_3e12_8988_98d6e19d9c0e = client_cuuid;
            uuid_e9214878_12c6_3b16_8e1f_24e296838704 = _uuid;
        }

        void rsp(role_battle_info _info){
            msgpack11::MsgPack::array _argv_0e0198b7_cc8a_3e12_8988_98d6e19d9c0e;
            _argv_0e0198b7_cc8a_3e12_8988_98d6e19d9c0e.push_back(uuid_e9214878_12c6_3b16_8e1f_24e296838704);
            _argv_0e0198b7_cc8a_3e12_8988_98d6e19d9c0e.push_back(role_battle_info::role_battle_info_to_protcol(_info));
            _hub_handle->_gatemng->call_client(_client_cuuid_0e0198b7_cc8a_3e12_8988_98d6e19d9c0e, "battle_rsp_cb_get_battle_info_rsp", _argv_0e0198b7_cc8a_3e12_8988_98d6e19d9c0e);
        }

        void err(int32_t err_code){
            msgpack11::MsgPack::array _argv_0e0198b7_cc8a_3e12_8988_98d6e19d9c0e;
            _argv_0e0198b7_cc8a_3e12_8988_98d6e19d9c0e.push_back(uuid_e9214878_12c6_3b16_8e1f_24e296838704);
            _argv_0e0198b7_cc8a_3e12_8988_98d6e19d9c0e.push_back(err_code);
            _hub_handle->_gatemng->call_client(_client_cuuid_0e0198b7_cc8a_3e12_8988_98d6e19d9c0e, "battle_rsp_cb_get_battle_info_err", _argv_0e0198b7_cc8a_3e12_8988_98d6e19d9c0e);
        }

    };

    class battle_pickup_item_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _client_cuuid_6987f20c_62b0_3c5c_96d5_782b9d4866a6;
        uint64_t uuid_bb32f69d_f73e_3d47_b2f5_cb4d58e4b057;

    public:
        battle_pickup_item_rsp(std::shared_ptr<hub::hub_service> _hub, std::string client_cuuid, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _client_cuuid_6987f20c_62b0_3c5c_96d5_782b9d4866a6 = client_cuuid;
            uuid_bb32f69d_f73e_3d47_b2f5_cb4d58e4b057 = _uuid;
        }

        void rsp(){
            msgpack11::MsgPack::array _argv_6987f20c_62b0_3c5c_96d5_782b9d4866a6;
            _argv_6987f20c_62b0_3c5c_96d5_782b9d4866a6.push_back(uuid_bb32f69d_f73e_3d47_b2f5_cb4d58e4b057);
            _hub_handle->_gatemng->call_client(_client_cuuid_6987f20c_62b0_3c5c_96d5_782b9d4866a6, "battle_rsp_cb_pickup_item_rsp", _argv_6987f20c_62b0_3c5c_96d5_782b9d4866a6);
        }

        void err(int32_t err_code){
            msgpack11::MsgPack::array _argv_6987f20c_62b0_3c5c_96d5_782b9d4866a6;
            _argv_6987f20c_62b0_3c5c_96d5_782b9d4866a6.push_back(uuid_bb32f69d_f73e_3d47_b2f5_cb4d58e4b057);
            _argv_6987f20c_62b0_3c5c_96d5_782b9d4866a6.push_back(err_code);
            _hub_handle->_gatemng->call_client(_client_cuuid_6987f20c_62b0_3c5c_96d5_782b9d4866a6, "battle_rsp_cb_pickup_item_err", _argv_6987f20c_62b0_3c5c_96d5_782b9d4866a6);
        }

    };

    class battle_use_skill_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _client_cuuid_f54ecac1_af9c_3003_a2f2_ed93134bfdfe;
        uint64_t uuid_871186aa_104b_36ee_939d_9b8b1285e974;

    public:
        battle_use_skill_rsp(std::shared_ptr<hub::hub_service> _hub, std::string client_cuuid, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _client_cuuid_f54ecac1_af9c_3003_a2f2_ed93134bfdfe = client_cuuid;
            uuid_871186aa_104b_36ee_939d_9b8b1285e974 = _uuid;
        }

        void rsp(){
            msgpack11::MsgPack::array _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe;
            _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe.push_back(uuid_871186aa_104b_36ee_939d_9b8b1285e974);
            _hub_handle->_gatemng->call_client(_client_cuuid_f54ecac1_af9c_3003_a2f2_ed93134bfdfe, "battle_rsp_cb_use_skill_rsp", _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe);
        }

        void err(int32_t err_code){
            msgpack11::MsgPack::array _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe;
            _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe.push_back(uuid_871186aa_104b_36ee_939d_9b8b1285e974);
            _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe.push_back(err_code);
            _hub_handle->_gatemng->call_client(_client_cuuid_f54ecac1_af9c_3003_a2f2_ed93134bfdfe, "battle_rsp_cb_use_skill_err", _argv_f54ecac1_af9c_3003_a2f2_ed93134bfdfe);
        }

    };

    class battle_in_out_house_rsp : public common::Response {
    private:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::string _client_cuuid_55305a75_a6bb_365f_9403_f8e1e12e2286;
        uint64_t uuid_d5e63017_5738_360d_a05c_fcddcdf94ba0;

    public:
        battle_in_out_house_rsp(std::shared_ptr<hub::hub_service> _hub, std::string client_cuuid, uint64_t _uuid)
        {
            _hub_handle = _hub;
            _client_cuuid_55305a75_a6bb_365f_9403_f8e1e12e2286 = client_cuuid;
            uuid_d5e63017_5738_360d_a05c_fcddcdf94ba0 = _uuid;
        }

        void rsp(int32_t state){
            msgpack11::MsgPack::array _argv_55305a75_a6bb_365f_9403_f8e1e12e2286;
            _argv_55305a75_a6bb_365f_9403_f8e1e12e2286.push_back(uuid_d5e63017_5738_360d_a05c_fcddcdf94ba0);
            _argv_55305a75_a6bb_365f_9403_f8e1e12e2286.push_back(state);
            _hub_handle->_gatemng->call_client(_client_cuuid_55305a75_a6bb_365f_9403_f8e1e12e2286, "battle_rsp_cb_in_out_house_rsp", _argv_55305a75_a6bb_365f_9403_f8e1e12e2286);
        }

        void err(int32_t err_code){
            msgpack11::MsgPack::array _argv_55305a75_a6bb_365f_9403_f8e1e12e2286;
            _argv_55305a75_a6bb_365f_9403_f8e1e12e2286.push_back(uuid_d5e63017_5738_360d_a05c_fcddcdf94ba0);
            _argv_55305a75_a6bb_365f_9403_f8e1e12e2286.push_back(err_code);
            _hub_handle->_gatemng->call_client(_client_cuuid_55305a75_a6bb_365f_9403_f8e1e12e2286, "battle_rsp_cb_in_out_house_err", _argv_55305a75_a6bb_365f_9403_f8e1e12e2286);
        }

    };

    class battle_module : public common::imodule, public std::enable_shared_from_this<battle_module>{
    private:
        std::shared_ptr<hub::hub_service> hub_handle;

    public:
        battle_module()
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            hub_handle = _hub_service;
            _hub_service->modules.add_mothed("battle_ping", std::bind(&battle_module::ping, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_load_scene_done", std::bind(&battle_module::load_scene_done, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_role_rocker", std::bind(&battle_module::role_rocker, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_role_jump", std::bind(&battle_module::role_jump, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_role_aim", std::bind(&battle_module::role_aim, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_role_change_equip", std::bind(&battle_module::role_change_equip, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_role_shoot", std::bind(&battle_module::role_shoot, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_role_rpg_shoot", std::bind(&battle_module::role_rpg_shoot, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_role_rpg_target_shoot", std::bind(&battle_module::role_rpg_target_shoot, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_role_grenade_shoot", std::bind(&battle_module::role_grenade_shoot, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_role_grenade_target_shoot", std::bind(&battle_module::role_grenade_target_shoot, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_role_aim_shoot", std::bind(&battle_module::role_aim_shoot, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_get_bag_info", std::bind(&battle_module::get_bag_info, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_get_battle_info", std::bind(&battle_module::get_battle_info, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_drop_item", std::bind(&battle_module::drop_item, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_drop_bullet", std::bind(&battle_module::drop_bullet, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_pickup_item", std::bind(&battle_module::pickup_item, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_medicine", std::bind(&battle_module::medicine, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_use_skill", std::bind(&battle_module::use_skill, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("battle_in_out_house", std::bind(&battle_module::in_out_house, this, std::placeholders::_1));
        }

        concurrent::signals<void()> sig_ping;
        void ping(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            rsp = std::make_shared<battle_ping_rsp>(hub_handle, hub_handle->_gatemng->current_client_cuuid, _cb_uuid);
            sig_ping.emit();
            rsp = nullptr;
        }

        concurrent::signals<void(std::string)> sig_load_scene_done;
        void load_scene_done(const msgpack11::MsgPack::array& inArray){
            auto _role_id = inArray[0].string_value();
            sig_load_scene_done.emit(_role_id);
        }

        concurrent::signals<void(int32_t)> sig_role_rocker;
        void role_rocker(const msgpack11::MsgPack::array& inArray){
            auto _rocker_state = inArray[0].int32_value();
            sig_role_rocker.emit(_rocker_state);
        }

        concurrent::signals<void()> sig_role_jump;
        void role_jump(const msgpack11::MsgPack::array& inArray){
            sig_role_jump.emit();
        }

        concurrent::signals<void(int32_t)> sig_role_aim;
        void role_aim(const msgpack11::MsgPack::array& inArray){
            auto _angle = inArray[0].int32_value();
            sig_role_aim.emit(_angle);
        }

        concurrent::signals<void(std::string)> sig_role_change_equip;
        void role_change_equip(const msgpack11::MsgPack::array& inArray){
            auto _equip_uuid = inArray[0].string_value();
            sig_role_change_equip.emit(_equip_uuid);
        }

        concurrent::signals<void()> sig_role_shoot;
        void role_shoot(const msgpack11::MsgPack::array& inArray){
            sig_role_shoot.emit();
        }

        concurrent::signals<void(int32_t)> sig_role_rpg_shoot;
        void role_rpg_shoot(const msgpack11::MsgPack::array& inArray){
            auto _angle = inArray[0].int32_value();
            sig_role_rpg_shoot.emit(_angle);
        }

        concurrent::signals<void(int32_t, int32_t)> sig_role_rpg_target_shoot;
        void role_rpg_target_shoot(const msgpack11::MsgPack::array& inArray){
            auto _target_x = inArray[0].int32_value();
            auto _target_y = inArray[1].int32_value();
            sig_role_rpg_target_shoot.emit(_target_x, _target_y);
        }

        concurrent::signals<void(int32_t)> sig_role_grenade_shoot;
        void role_grenade_shoot(const msgpack11::MsgPack::array& inArray){
            auto _angle = inArray[0].int32_value();
            sig_role_grenade_shoot.emit(_angle);
        }

        concurrent::signals<void(int32_t, int32_t)> sig_role_grenade_target_shoot;
        void role_grenade_target_shoot(const msgpack11::MsgPack::array& inArray){
            auto _target_x = inArray[0].int32_value();
            auto _target_y = inArray[1].int32_value();
            sig_role_grenade_target_shoot.emit(_target_x, _target_y);
        }

        concurrent::signals<void(int32_t, int32_t)> sig_role_aim_shoot;
        void role_aim_shoot(const msgpack11::MsgPack::array& inArray){
            auto _x = inArray[0].int32_value();
            auto _y = inArray[1].int32_value();
            sig_role_aim_shoot.emit(_x, _y);
        }

        concurrent::signals<void()> sig_get_bag_info;
        void get_bag_info(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            rsp = std::make_shared<battle_get_bag_info_rsp>(hub_handle, hub_handle->_gatemng->current_client_cuuid, _cb_uuid);
            sig_get_bag_info.emit();
            rsp = nullptr;
        }

        concurrent::signals<void()> sig_get_battle_info;
        void get_battle_info(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            rsp = std::make_shared<battle_get_battle_info_rsp>(hub_handle, hub_handle->_gatemng->current_client_cuuid, _cb_uuid);
            sig_get_battle_info.emit();
            rsp = nullptr;
        }

        concurrent::signals<void(std::string, int32_t)> sig_drop_item;
        void drop_item(const msgpack11::MsgPack::array& inArray){
            auto _item_uuid = inArray[0].string_value();
            auto _num = inArray[1].int32_value();
            sig_drop_item.emit(_item_uuid, _num);
        }

        concurrent::signals<void(int32_t)> sig_drop_bullet;
        void drop_bullet(const msgpack11::MsgPack::array& inArray){
            auto _num = inArray[0].int32_value();
            sig_drop_bullet.emit(_num);
        }

        concurrent::signals<void(std::string)> sig_pickup_item;
        void pickup_item(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            auto _item_uuid = inArray[1].string_value();
            rsp = std::make_shared<battle_pickup_item_rsp>(hub_handle, hub_handle->_gatemng->current_client_cuuid, _cb_uuid);
            sig_pickup_item.emit(_item_uuid);
            rsp = nullptr;
        }

        concurrent::signals<void(std::string)> sig_medicine;
        void medicine(const msgpack11::MsgPack::array& inArray){
            auto _medicine_uuid = inArray[0].string_value();
            sig_medicine.emit(_medicine_uuid);
        }

        concurrent::signals<void(std::string)> sig_use_skill;
        void use_skill(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            auto _skill_name = inArray[1].string_value();
            rsp = std::make_shared<battle_use_skill_rsp>(hub_handle, hub_handle->_gatemng->current_client_cuuid, _cb_uuid);
            sig_use_skill.emit(_skill_name);
            rsp = nullptr;
        }

        concurrent::signals<void()> sig_in_out_house;
        void in_out_house(const msgpack11::MsgPack::array& inArray){
            auto _cb_uuid = inArray[0].uint64_value();
            rsp = std::make_shared<battle_in_out_house_rsp>(hub_handle, hub_handle->_gatemng->current_client_cuuid, _cb_uuid);
            sig_in_out_house.emit();
            rsp = nullptr;
        }

    };

}

#endif //_h_ccallbattle_0d637c09_0ee7_333b_99f9_b450dd48eabc_
