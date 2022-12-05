#ifndef _h_lobbycallc_f7fb0da4_4d0e_36db_aefb_2be2d0698dbf_
#define _h_lobbycallc_f7fb0da4_4d0e_36db_aefb_2be2d0698dbf_

#include <hub_service.h>
#include <signals.h>

#include "common.h"

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this caller code is codegen by abelkhan codegen for cpp*/
/*this cb code is codegen by abelkhan for cpp*/
    class lobby_client_rsp_cb : public common::imodule, public std::enable_shared_from_this<lobby_client_rsp_cb>{
    public:
        lobby_client_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class lobby_client_clientproxy
{
    public:
        std::string client_uuid_e2673d0c_1bee_308d_b6fa_d9d36579f8b0;
        std::atomic<uint64_t> uuid_e2673d0c_1bee_308d_b6fa_d9d36579f8b0;

        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<lobby_client_rsp_cb> rsp_cb_lobby_client_handle;

        lobby_client_clientproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_client_rsp_cb> rsp_cb_lobby_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_lobby_client_handle = rsp_cb_lobby_client_handle_;
            uuid_e2673d0c_1bee_308d_b6fa_d9d36579f8b0.store(random());

        }

        void player_login_sucess(role_lobby_info role_info){
            msgpack11::MsgPack::array _argv_ace0ce26_8791_358f_981f_f55fda1b9e90;
            _argv_ace0ce26_8791_358f_981f_f55fda1b9e90.push_back(role_lobby_info::role_lobby_info_to_protcol(role_info));
            _hub_handle->_gatemng->call_client(client_uuid_e2673d0c_1bee_308d_b6fa_d9d36579f8b0, "lobby_client_player_login_sucess", _argv_ace0ce26_8791_358f_981f_f55fda1b9e90);
        }

        void player_login_non_account(){
            msgpack11::MsgPack::array _argv_4872c19a_0d57_3d90_9bd2_651887950904;
            _hub_handle->_gatemng->call_client(client_uuid_e2673d0c_1bee_308d_b6fa_d9d36579f8b0, "lobby_client_player_login_non_account", _argv_4872c19a_0d57_3d90_9bd2_651887950904);
        }

        void be_displacement(){
            msgpack11::MsgPack::array _argv_156d31bb_d697_3042_a3e8_88d0a5d0484c;
            _hub_handle->_gatemng->call_client(client_uuid_e2673d0c_1bee_308d_b6fa_d9d36579f8b0, "lobby_client_be_displacement", _argv_156d31bb_d697_3042_a3e8_88d0a5d0484c);
        }

        void server_close(){
            msgpack11::MsgPack::array _argv_a5607be0_6a2c_34ea_b33e_f26dfd9227c3;
            _hub_handle->_gatemng->call_client(client_uuid_e2673d0c_1bee_308d_b6fa_d9d36579f8b0, "lobby_client_server_close", _argv_a5607be0_6a2c_34ea_b33e_f26dfd9227c3);
        }

    };

    class lobby_client_multicast
{
    public:
        std::vector<std::string> client_uuids_e2673d0c_1bee_308d_b6fa_d9d36579f8b0;
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<lobby_client_rsp_cb> rsp_cb_lobby_client_handle;

        lobby_client_multicast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_client_rsp_cb> rsp_cb_lobby_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_lobby_client_handle = rsp_cb_lobby_client_handle_;
        }

    };

    class lobby_client_broadcast
{
    public:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<lobby_client_rsp_cb> rsp_cb_lobby_client_handle;

        lobby_client_broadcast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_client_rsp_cb> rsp_cb_lobby_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_lobby_client_handle = rsp_cb_lobby_client_handle_;
        }

    };

    class lobby_client_clientproxy;
    class lobby_client_multicast;
    class lobby_client_broadcast;
    class lobby_client_caller {
    private:
        static std::shared_ptr<lobby_client_rsp_cb> rsp_cb_lobby_client_handle;

    private:
        std::shared_ptr<lobby_client_clientproxy> _clientproxy;
        std::shared_ptr<lobby_client_multicast> _multicast;
        std::shared_ptr<lobby_client_broadcast> _broadcast;

    public:
        lobby_client_caller(std::shared_ptr<hub::hub_service> hub_service_) 
        {
            if (rsp_cb_lobby_client_handle == nullptr) {
                rsp_cb_lobby_client_handle = std::make_shared<lobby_client_rsp_cb>();
                rsp_cb_lobby_client_handle->Init(hub_service_);
            }
            _clientproxy = std::make_shared<lobby_client_clientproxy>(hub_service_, rsp_cb_lobby_client_handle);
            _multicast = std::make_shared<lobby_client_multicast>(hub_service_, rsp_cb_lobby_client_handle);
            _broadcast = std::make_shared<lobby_client_broadcast>(hub_service_, rsp_cb_lobby_client_handle);
        }

        std::shared_ptr<lobby_client_clientproxy> get_client(std::string client_uuid) {
            _clientproxy->client_uuid_e2673d0c_1bee_308d_b6fa_d9d36579f8b0 = client_uuid;
            return _clientproxy;
        }

        std::shared_ptr<lobby_client_multicast> get_multicast(std::vector<std::string> client_uuids) {
            _multicast->client_uuids_e2673d0c_1bee_308d_b6fa_d9d36579f8b0 = client_uuids;
            return _multicast;
        }

        std::shared_ptr<lobby_client_broadcast> get_broadcast() {
            return _broadcast;
        }

    };
/*this cb code is codegen by abelkhan for cpp*/
    class lobby_battle_client_rsp_cb : public common::imodule, public std::enable_shared_from_this<lobby_battle_client_rsp_cb>{
    public:
        lobby_battle_client_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class lobby_battle_client_clientproxy
{
    public:
        std::string client_uuid_14784e66_280f_3ccc_a6ca_281e763faaa7;
        std::atomic<uint64_t> uuid_14784e66_280f_3ccc_a6ca_281e763faaa7;

        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<lobby_battle_client_rsp_cb> rsp_cb_lobby_battle_client_handle;

        lobby_battle_client_clientproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_battle_client_rsp_cb> rsp_cb_lobby_battle_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_lobby_battle_client_handle = rsp_cb_lobby_battle_client_handle_;
            uuid_14784e66_280f_3ccc_a6ca_281e763faaa7.store(random());

        }

        void battle_svr(std::string battle, std::string host, int32_t port){
            msgpack11::MsgPack::array _argv_481d9421_49d4_3df6_84ef_72d24a0b3440;
            _argv_481d9421_49d4_3df6_84ef_72d24a0b3440.push_back(battle);
            _argv_481d9421_49d4_3df6_84ef_72d24a0b3440.push_back(host);
            _argv_481d9421_49d4_3df6_84ef_72d24a0b3440.push_back(port);
            _hub_handle->_gatemng->call_client(client_uuid_14784e66_280f_3ccc_a6ca_281e763faaa7, "lobby_battle_client_battle_svr", _argv_481d9421_49d4_3df6_84ef_72d24a0b3440);
        }

        void end_battle(role_battle_end_info battle_end_info){
            msgpack11::MsgPack::array _argv_12fd17d3_1937_3241_ad95_532c02932439;
            _argv_12fd17d3_1937_3241_ad95_532c02932439.push_back(role_battle_end_info::role_battle_end_info_to_protcol(battle_end_info));
            _hub_handle->_gatemng->call_client(client_uuid_14784e66_280f_3ccc_a6ca_281e763faaa7, "lobby_battle_client_end_battle", _argv_12fd17d3_1937_3241_ad95_532c02932439);
        }

    };

    class lobby_battle_client_multicast
{
    public:
        std::vector<std::string> client_uuids_14784e66_280f_3ccc_a6ca_281e763faaa7;
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<lobby_battle_client_rsp_cb> rsp_cb_lobby_battle_client_handle;

        lobby_battle_client_multicast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_battle_client_rsp_cb> rsp_cb_lobby_battle_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_lobby_battle_client_handle = rsp_cb_lobby_battle_client_handle_;
        }

    };

    class lobby_battle_client_broadcast
{
    public:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<lobby_battle_client_rsp_cb> rsp_cb_lobby_battle_client_handle;

        lobby_battle_client_broadcast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_battle_client_rsp_cb> rsp_cb_lobby_battle_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_lobby_battle_client_handle = rsp_cb_lobby_battle_client_handle_;
        }

    };

    class lobby_battle_client_clientproxy;
    class lobby_battle_client_multicast;
    class lobby_battle_client_broadcast;
    class lobby_battle_client_caller {
    private:
        static std::shared_ptr<lobby_battle_client_rsp_cb> rsp_cb_lobby_battle_client_handle;

    private:
        std::shared_ptr<lobby_battle_client_clientproxy> _clientproxy;
        std::shared_ptr<lobby_battle_client_multicast> _multicast;
        std::shared_ptr<lobby_battle_client_broadcast> _broadcast;

    public:
        lobby_battle_client_caller(std::shared_ptr<hub::hub_service> hub_service_) 
        {
            if (rsp_cb_lobby_battle_client_handle == nullptr) {
                rsp_cb_lobby_battle_client_handle = std::make_shared<lobby_battle_client_rsp_cb>();
                rsp_cb_lobby_battle_client_handle->Init(hub_service_);
            }
            _clientproxy = std::make_shared<lobby_battle_client_clientproxy>(hub_service_, rsp_cb_lobby_battle_client_handle);
            _multicast = std::make_shared<lobby_battle_client_multicast>(hub_service_, rsp_cb_lobby_battle_client_handle);
            _broadcast = std::make_shared<lobby_battle_client_broadcast>(hub_service_, rsp_cb_lobby_battle_client_handle);
        }

        std::shared_ptr<lobby_battle_client_clientproxy> get_client(std::string client_uuid) {
            _clientproxy->client_uuid_14784e66_280f_3ccc_a6ca_281e763faaa7 = client_uuid;
            return _clientproxy;
        }

        std::shared_ptr<lobby_battle_client_multicast> get_multicast(std::vector<std::string> client_uuids) {
            _multicast->client_uuids_14784e66_280f_3ccc_a6ca_281e763faaa7 = client_uuids;
            return _multicast;
        }

        std::shared_ptr<lobby_battle_client_broadcast> get_broadcast() {
            return _broadcast;
        }

    };
/*this cb code is codegen by abelkhan for cpp*/
    class lobby_team_client_rsp_cb : public common::imodule, public std::enable_shared_from_this<lobby_team_client_rsp_cb>{
    public:
        lobby_team_client_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class lobby_team_client_clientproxy
{
    public:
        std::string client_uuid_b3f192e8_5b71_3b34_8ebf_16ad7cc7fa76;
        std::atomic<uint64_t> uuid_b3f192e8_5b71_3b34_8ebf_16ad7cc7fa76;

        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<lobby_team_client_rsp_cb> rsp_cb_lobby_team_client_handle;

        lobby_team_client_clientproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_team_client_rsp_cb> rsp_cb_lobby_team_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_lobby_team_client_handle = rsp_cb_lobby_team_client_handle_;
            uuid_b3f192e8_5b71_3b34_8ebf_16ad7cc7fa76.store(random());

        }

        void invite_role_join_team(int32_t team_role_num, std::string team_id, std::string invite_role_name){
            msgpack11::MsgPack::array _argv_29707771_ccbe_3ac7_adb1_a24ff0d29d04;
            _argv_29707771_ccbe_3ac7_adb1_a24ff0d29d04.push_back(team_role_num);
            _argv_29707771_ccbe_3ac7_adb1_a24ff0d29d04.push_back(team_id);
            _argv_29707771_ccbe_3ac7_adb1_a24ff0d29d04.push_back(invite_role_name);
            _hub_handle->_gatemng->call_client(client_uuid_b3f192e8_5b71_3b34_8ebf_16ad7cc7fa76, "lobby_team_client_invite_role_join_team", _argv_29707771_ccbe_3ac7_adb1_a24ff0d29d04);
        }

    };

    class lobby_team_client_multicast
{
    public:
        std::vector<std::string> client_uuids_b3f192e8_5b71_3b34_8ebf_16ad7cc7fa76;
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<lobby_team_client_rsp_cb> rsp_cb_lobby_team_client_handle;

        lobby_team_client_multicast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_team_client_rsp_cb> rsp_cb_lobby_team_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_lobby_team_client_handle = rsp_cb_lobby_team_client_handle_;
        }

    };

    class lobby_team_client_broadcast
{
    public:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<lobby_team_client_rsp_cb> rsp_cb_lobby_team_client_handle;

        lobby_team_client_broadcast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_team_client_rsp_cb> rsp_cb_lobby_team_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_lobby_team_client_handle = rsp_cb_lobby_team_client_handle_;
        }

    };

    class lobby_team_client_clientproxy;
    class lobby_team_client_multicast;
    class lobby_team_client_broadcast;
    class lobby_team_client_caller {
    private:
        static std::shared_ptr<lobby_team_client_rsp_cb> rsp_cb_lobby_team_client_handle;

    private:
        std::shared_ptr<lobby_team_client_clientproxy> _clientproxy;
        std::shared_ptr<lobby_team_client_multicast> _multicast;
        std::shared_ptr<lobby_team_client_broadcast> _broadcast;

    public:
        lobby_team_client_caller(std::shared_ptr<hub::hub_service> hub_service_) 
        {
            if (rsp_cb_lobby_team_client_handle == nullptr) {
                rsp_cb_lobby_team_client_handle = std::make_shared<lobby_team_client_rsp_cb>();
                rsp_cb_lobby_team_client_handle->Init(hub_service_);
            }
            _clientproxy = std::make_shared<lobby_team_client_clientproxy>(hub_service_, rsp_cb_lobby_team_client_handle);
            _multicast = std::make_shared<lobby_team_client_multicast>(hub_service_, rsp_cb_lobby_team_client_handle);
            _broadcast = std::make_shared<lobby_team_client_broadcast>(hub_service_, rsp_cb_lobby_team_client_handle);
        }

        std::shared_ptr<lobby_team_client_clientproxy> get_client(std::string client_uuid) {
            _clientproxy->client_uuid_b3f192e8_5b71_3b34_8ebf_16ad7cc7fa76 = client_uuid;
            return _clientproxy;
        }

        std::shared_ptr<lobby_team_client_multicast> get_multicast(std::vector<std::string> client_uuids) {
            _multicast->client_uuids_b3f192e8_5b71_3b34_8ebf_16ad7cc7fa76 = client_uuids;
            return _multicast;
        }

        std::shared_ptr<lobby_team_client_broadcast> get_broadcast() {
            return _broadcast;
        }

    };
    class lobby_friend_client_rsp_cb;
    class lobby_friend_client_invite_role_friend_cb : public std::enable_shared_from_this<lobby_friend_client_invite_role_friend_cb>{
    private:
        uint64_t cb_uuid;
        std::shared_ptr<lobby_friend_client_rsp_cb> module_rsp_cb;

    public:
        lobby_friend_client_invite_role_friend_cb(uint64_t _cb_uuid, std::shared_ptr<lobby_friend_client_rsp_cb> _module_rsp_cb);
    public:
        concurrent::signals<void()> sig_invite_role_friend_cb;
        concurrent::signals<void()> sig_invite_role_friend_err;
        concurrent::signals<void()> sig_invite_role_friend_timeout;

        std::shared_ptr<lobby_friend_client_invite_role_friend_cb> callBack(std::function<void()> cb, std::function<void()> err);
        void timeout(uint64_t tick, std::function<void()> timeout_cb);
    };

    class lobby_friend_client_rsp_cb;
    class lobby_friend_client_agree_role_friend_cb : public std::enable_shared_from_this<lobby_friend_client_agree_role_friend_cb>{
    private:
        uint64_t cb_uuid;
        std::shared_ptr<lobby_friend_client_rsp_cb> module_rsp_cb;

    public:
        lobby_friend_client_agree_role_friend_cb(uint64_t _cb_uuid, std::shared_ptr<lobby_friend_client_rsp_cb> _module_rsp_cb);
    public:
        concurrent::signals<void()> sig_agree_role_friend_cb;
        concurrent::signals<void()> sig_agree_role_friend_err;
        concurrent::signals<void()> sig_agree_role_friend_timeout;

        std::shared_ptr<lobby_friend_client_agree_role_friend_cb> callBack(std::function<void()> cb, std::function<void()> err);
        void timeout(uint64_t tick, std::function<void()> timeout_cb);
    };

/*this cb code is codegen by abelkhan for cpp*/
    class lobby_friend_client_rsp_cb : public common::imodule, public std::enable_shared_from_this<lobby_friend_client_rsp_cb>{
    public:
        std::mutex mutex_map_invite_role_friend;
        std::unordered_map<uint64_t, std::shared_ptr<lobby_friend_client_invite_role_friend_cb> > map_invite_role_friend;
        std::mutex mutex_map_agree_role_friend;
        std::unordered_map<uint64_t, std::shared_ptr<lobby_friend_client_agree_role_friend_cb> > map_agree_role_friend;
        lobby_friend_client_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
            _hub_service->modules.add_mothed("lobby_friend_client_rsp_cb_invite_role_friend_rsp", std::bind(&lobby_friend_client_rsp_cb::invite_role_friend_rsp, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("lobby_friend_client_rsp_cb_invite_role_friend_err", std::bind(&lobby_friend_client_rsp_cb::invite_role_friend_err, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("lobby_friend_client_rsp_cb_agree_role_friend_rsp", std::bind(&lobby_friend_client_rsp_cb::agree_role_friend_rsp, this, std::placeholders::_1));
            _hub_service->modules.add_mothed("lobby_friend_client_rsp_cb_agree_role_friend_err", std::bind(&lobby_friend_client_rsp_cb::agree_role_friend_err, this, std::placeholders::_1));
        }

        void invite_role_friend_rsp(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto rsp = try_get_and_del_invite_role_friend_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_invite_role_friend_cb.emit();
            }
        }

        void invite_role_friend_err(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto rsp = try_get_and_del_invite_role_friend_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_invite_role_friend_err.emit();
            }
        }

        void invite_role_friend_timeout(uint64_t cb_uuid){
            auto rsp = try_get_and_del_invite_role_friend_cb(cb_uuid);
            if (rsp != nullptr){
                rsp->sig_invite_role_friend_timeout.emit();
            }
        }

        std::shared_ptr<lobby_friend_client_invite_role_friend_cb> try_get_and_del_invite_role_friend_cb(uint64_t uuid){
            std::lock_guard<std::mutex> l(mutex_map_invite_role_friend);
            if (map_invite_role_friend.find(uuid) != map_invite_role_friend.end()) {
                auto rsp = map_invite_role_friend[uuid];
                map_invite_role_friend.erase(uuid);
                return rsp;
            }
            return nullptr;
        }

        void agree_role_friend_rsp(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto rsp = try_get_and_del_agree_role_friend_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_agree_role_friend_cb.emit();
            }
        }

        void agree_role_friend_err(const msgpack11::MsgPack::array& inArray){
            auto uuid = inArray[0].uint64_value();
            auto rsp = try_get_and_del_agree_role_friend_cb(uuid);
            if (rsp != nullptr){
                rsp->sig_agree_role_friend_err.emit();
            }
        }

        void agree_role_friend_timeout(uint64_t cb_uuid){
            auto rsp = try_get_and_del_agree_role_friend_cb(cb_uuid);
            if (rsp != nullptr){
                rsp->sig_agree_role_friend_timeout.emit();
            }
        }

        std::shared_ptr<lobby_friend_client_agree_role_friend_cb> try_get_and_del_agree_role_friend_cb(uint64_t uuid){
            std::lock_guard<std::mutex> l(mutex_map_agree_role_friend);
            if (map_agree_role_friend.find(uuid) != map_agree_role_friend.end()) {
                auto rsp = map_agree_role_friend[uuid];
                map_agree_role_friend.erase(uuid);
                return rsp;
            }
            return nullptr;
        }

    };

    class lobby_friend_client_clientproxy
{
    public:
        std::string client_uuid_2c6a39db_ca4c_3dfa_b050_99106a16771e;
        std::atomic<uint64_t> uuid_2c6a39db_ca4c_3dfa_b050_99106a16771e;

        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<lobby_friend_client_rsp_cb> rsp_cb_lobby_friend_client_handle;

        lobby_friend_client_clientproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_friend_client_rsp_cb> rsp_cb_lobby_friend_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_lobby_friend_client_handle = rsp_cb_lobby_friend_client_handle_;
            uuid_2c6a39db_ca4c_3dfa_b050_99106a16771e.store(random());

        }

        std::shared_ptr<lobby_friend_client_invite_role_friend_cb> invite_role_friend(role_friend_info invite_account){
            auto uuid_27e53be7_470d_5b98_b037_74e3de0f1203 = uuid_2c6a39db_ca4c_3dfa_b050_99106a16771e++;
            msgpack11::MsgPack::array _argv_f4abe68d_823d_33d5_a6f6_9ebff8eb6e18;
            _argv_f4abe68d_823d_33d5_a6f6_9ebff8eb6e18.push_back(uuid_27e53be7_470d_5b98_b037_74e3de0f1203);
            _argv_f4abe68d_823d_33d5_a6f6_9ebff8eb6e18.push_back(role_friend_info::role_friend_info_to_protcol(invite_account));
            _hub_handle->_gatemng->call_client(client_uuid_2c6a39db_ca4c_3dfa_b050_99106a16771e, "lobby_friend_client_invite_role_friend", _argv_f4abe68d_823d_33d5_a6f6_9ebff8eb6e18);
            auto cb_invite_role_friend_obj = std::make_shared<lobby_friend_client_invite_role_friend_cb>(uuid_27e53be7_470d_5b98_b037_74e3de0f1203, rsp_cb_lobby_friend_client_handle);
            std::lock_guard<std::mutex> l(rsp_cb_lobby_friend_client_handle->mutex_map_invite_role_friend);
            rsp_cb_lobby_friend_client_handle->map_invite_role_friend.insert(std::make_pair(uuid_27e53be7_470d_5b98_b037_74e3de0f1203, cb_invite_role_friend_obj));
            return cb_invite_role_friend_obj;
        }

        std::shared_ptr<lobby_friend_client_agree_role_friend_cb> agree_role_friend(role_friend_info target_account){
            auto uuid_67bfbc9a_7c4d_5698_93a0_364d7aa95a7e = uuid_2c6a39db_ca4c_3dfa_b050_99106a16771e++;
            msgpack11::MsgPack::array _argv_8d09e4bc_e374_3918_b734_2a4508dc1ab9;
            _argv_8d09e4bc_e374_3918_b734_2a4508dc1ab9.push_back(uuid_67bfbc9a_7c4d_5698_93a0_364d7aa95a7e);
            _argv_8d09e4bc_e374_3918_b734_2a4508dc1ab9.push_back(role_friend_info::role_friend_info_to_protcol(target_account));
            _hub_handle->_gatemng->call_client(client_uuid_2c6a39db_ca4c_3dfa_b050_99106a16771e, "lobby_friend_client_agree_role_friend", _argv_8d09e4bc_e374_3918_b734_2a4508dc1ab9);
            auto cb_agree_role_friend_obj = std::make_shared<lobby_friend_client_agree_role_friend_cb>(uuid_67bfbc9a_7c4d_5698_93a0_364d7aa95a7e, rsp_cb_lobby_friend_client_handle);
            std::lock_guard<std::mutex> l(rsp_cb_lobby_friend_client_handle->mutex_map_agree_role_friend);
            rsp_cb_lobby_friend_client_handle->map_agree_role_friend.insert(std::make_pair(uuid_67bfbc9a_7c4d_5698_93a0_364d7aa95a7e, cb_agree_role_friend_obj));
            return cb_agree_role_friend_obj;
        }

    };

    class lobby_friend_client_multicast
{
    public:
        std::vector<std::string> client_uuids_2c6a39db_ca4c_3dfa_b050_99106a16771e;
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<lobby_friend_client_rsp_cb> rsp_cb_lobby_friend_client_handle;

        lobby_friend_client_multicast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_friend_client_rsp_cb> rsp_cb_lobby_friend_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_lobby_friend_client_handle = rsp_cb_lobby_friend_client_handle_;
        }

    };

    class lobby_friend_client_broadcast
{
    public:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<lobby_friend_client_rsp_cb> rsp_cb_lobby_friend_client_handle;

        lobby_friend_client_broadcast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<lobby_friend_client_rsp_cb> rsp_cb_lobby_friend_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_lobby_friend_client_handle = rsp_cb_lobby_friend_client_handle_;
        }

    };

    class lobby_friend_client_clientproxy;
    class lobby_friend_client_multicast;
    class lobby_friend_client_broadcast;
    class lobby_friend_client_caller {
    private:
        static std::shared_ptr<lobby_friend_client_rsp_cb> rsp_cb_lobby_friend_client_handle;

    private:
        std::shared_ptr<lobby_friend_client_clientproxy> _clientproxy;
        std::shared_ptr<lobby_friend_client_multicast> _multicast;
        std::shared_ptr<lobby_friend_client_broadcast> _broadcast;

    public:
        lobby_friend_client_caller(std::shared_ptr<hub::hub_service> hub_service_) 
        {
            if (rsp_cb_lobby_friend_client_handle == nullptr) {
                rsp_cb_lobby_friend_client_handle = std::make_shared<lobby_friend_client_rsp_cb>();
                rsp_cb_lobby_friend_client_handle->Init(hub_service_);
            }
            _clientproxy = std::make_shared<lobby_friend_client_clientproxy>(hub_service_, rsp_cb_lobby_friend_client_handle);
            _multicast = std::make_shared<lobby_friend_client_multicast>(hub_service_, rsp_cb_lobby_friend_client_handle);
            _broadcast = std::make_shared<lobby_friend_client_broadcast>(hub_service_, rsp_cb_lobby_friend_client_handle);
        }

        std::shared_ptr<lobby_friend_client_clientproxy> get_client(std::string client_uuid) {
            _clientproxy->client_uuid_2c6a39db_ca4c_3dfa_b050_99106a16771e = client_uuid;
            return _clientproxy;
        }

        std::shared_ptr<lobby_friend_client_multicast> get_multicast(std::vector<std::string> client_uuids) {
            _multicast->client_uuids_2c6a39db_ca4c_3dfa_b050_99106a16771e = client_uuids;
            return _multicast;
        }

        std::shared_ptr<lobby_friend_client_broadcast> get_broadcast() {
            return _broadcast;
        }

    };

}

#endif //_h_lobbycallc_f7fb0da4_4d0e_36db_aefb_2be2d0698dbf_
