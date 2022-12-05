#ifndef _h_matchcallc_4469e89b_854f_3b7a_b691_75c9b21e787b_
#define _h_matchcallc_4469e89b_854f_3b7a_b691_75c9b21e787b_

#include <hub_service.h>
#include <signals.h>

#include "common.h"

namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
/*this caller code is codegen by abelkhan codegen for cpp*/
/*this cb code is codegen by abelkhan for cpp*/
    class match_team_client_rsp_cb : public common::imodule, public std::enable_shared_from_this<match_team_client_rsp_cb>{
    public:
        match_team_client_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class match_team_client_clientproxy
{
    public:
        std::string client_uuid_1296640a_d80f_3b3d_bd63_0b0c2dda4c2c;
        std::atomic<uint64_t> uuid_1296640a_d80f_3b3d_bd63_0b0c2dda4c2c;

        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<match_team_client_rsp_cb> rsp_cb_match_team_client_handle;

        match_team_client_clientproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<match_team_client_rsp_cb> rsp_cb_match_team_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_match_team_client_handle = rsp_cb_match_team_client_handle_;
            uuid_1296640a_d80f_3b3d_bd63_0b0c2dda4c2c.store(random());

        }

        void role_leave_team_success(){
            msgpack11::MsgPack::array _argv_2f446e65_f329_34bc_b2e9_0e2f47ac82c8;
            _hub_handle->_gatemng->call_client(client_uuid_1296640a_d80f_3b3d_bd63_0b0c2dda4c2c, "match_team_client_role_leave_team_success", _argv_2f446e65_f329_34bc_b2e9_0e2f47ac82c8);
        }

        void be_kicked(){
            msgpack11::MsgPack::array _argv_2616b459_0117_393c_86a2_1eec5764c007;
            _hub_handle->_gatemng->call_client(client_uuid_1296640a_d80f_3b3d_bd63_0b0c2dda4c2c, "match_team_client_be_kicked", _argv_2616b459_0117_393c_86a2_1eec5764c007);
        }

    };

    class match_team_client_multicast
{
    public:
        std::vector<std::string> client_uuids_1296640a_d80f_3b3d_bd63_0b0c2dda4c2c;
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<match_team_client_rsp_cb> rsp_cb_match_team_client_handle;

        match_team_client_multicast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<match_team_client_rsp_cb> rsp_cb_match_team_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_match_team_client_handle = rsp_cb_match_team_client_handle_;
        }

        void refresh_team_info(match_team team_info){
            msgpack11::MsgPack::array _argv_23a8d4e1_4f72_376e_b32d_288f25519c08;
            _argv_23a8d4e1_4f72_376e_b32d_288f25519c08.push_back(match_team::match_team_to_protcol(team_info));
            _hub_handle->_gatemng->call_group_client(client_uuids_1296640a_d80f_3b3d_bd63_0b0c2dda4c2c, "match_team_client_refresh_team_info", _argv_23a8d4e1_4f72_376e_b32d_288f25519c08);
        }

        void team_is_free(){
            msgpack11::MsgPack::array _argv_3ebf6e91_5a75_3df4_acf0_5f8f25d28dd7;
            _hub_handle->_gatemng->call_group_client(client_uuids_1296640a_d80f_3b3d_bd63_0b0c2dda4c2c, "match_team_client_team_is_free", _argv_3ebf6e91_5a75_3df4_acf0_5f8f25d28dd7);
        }

        void team_leave_match(){
            msgpack11::MsgPack::array _argv_ed528a71_e12c_38fd_87d6_de17ba64896d;
            _hub_handle->_gatemng->call_group_client(client_uuids_1296640a_d80f_3b3d_bd63_0b0c2dda4c2c, "match_team_client_team_leave_match", _argv_ed528a71_e12c_38fd_87d6_de17ba64896d);
        }

        void team_into_match(){
            msgpack11::MsgPack::array _argv_5b55326f_4ad9_3e5e_ac7a_53955a3768f7;
            _hub_handle->_gatemng->call_group_client(client_uuids_1296640a_d80f_3b3d_bd63_0b0c2dda4c2c, "match_team_client_team_into_match", _argv_5b55326f_4ad9_3e5e_ac7a_53955a3768f7);
        }

    };

    class match_team_client_broadcast
{
    public:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<match_team_client_rsp_cb> rsp_cb_match_team_client_handle;

        match_team_client_broadcast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<match_team_client_rsp_cb> rsp_cb_match_team_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_match_team_client_handle = rsp_cb_match_team_client_handle_;
        }

    };

    class match_team_client_clientproxy;
    class match_team_client_multicast;
    class match_team_client_broadcast;
    class match_team_client_caller {
    private:
        static std::shared_ptr<match_team_client_rsp_cb> rsp_cb_match_team_client_handle;

    private:
        std::shared_ptr<match_team_client_clientproxy> _clientproxy;
        std::shared_ptr<match_team_client_multicast> _multicast;
        std::shared_ptr<match_team_client_broadcast> _broadcast;

    public:
        match_team_client_caller(std::shared_ptr<hub::hub_service> hub_service_) 
        {
            if (rsp_cb_match_team_client_handle == nullptr) {
                rsp_cb_match_team_client_handle = std::make_shared<match_team_client_rsp_cb>();
                rsp_cb_match_team_client_handle->Init(hub_service_);
            }
            _clientproxy = std::make_shared<match_team_client_clientproxy>(hub_service_, rsp_cb_match_team_client_handle);
            _multicast = std::make_shared<match_team_client_multicast>(hub_service_, rsp_cb_match_team_client_handle);
            _broadcast = std::make_shared<match_team_client_broadcast>(hub_service_, rsp_cb_match_team_client_handle);
        }

        std::shared_ptr<match_team_client_clientproxy> get_client(std::string client_uuid) {
            _clientproxy->client_uuid_1296640a_d80f_3b3d_bd63_0b0c2dda4c2c = client_uuid;
            return _clientproxy;
        }

        std::shared_ptr<match_team_client_multicast> get_multicast(std::vector<std::string> client_uuids) {
            _multicast->client_uuids_1296640a_d80f_3b3d_bd63_0b0c2dda4c2c = client_uuids;
            return _multicast;
        }

        std::shared_ptr<match_team_client_broadcast> get_broadcast() {
            return _broadcast;
        }

    };
/*this cb code is codegen by abelkhan for cpp*/
    class match_battle_client_rsp_cb : public common::imodule, public std::enable_shared_from_this<match_battle_client_rsp_cb>{
    public:
        match_battle_client_rsp_cb() 
        {
        }

        void Init(std::shared_ptr<hub::hub_service> _hub_service){
        }

    };

    class match_battle_client_clientproxy
{
    public:
        std::string client_uuid_1592abb4_a633_3425_a089_a7299018573b;
        std::atomic<uint64_t> uuid_1592abb4_a633_3425_a089_a7299018573b;

        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<match_battle_client_rsp_cb> rsp_cb_match_battle_client_handle;

        match_battle_client_clientproxy(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<match_battle_client_rsp_cb> rsp_cb_match_battle_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_match_battle_client_handle = rsp_cb_match_battle_client_handle_;
            uuid_1592abb4_a633_3425_a089_a7299018573b.store(random());

        }

        void role_into_battle(std::string battle, std::string host, int32_t port, std::string room_id, std::string account){
            msgpack11::MsgPack::array _argv_a6ddc5a9_dcd4_3bed_abef_26fb6df08fab;
            _argv_a6ddc5a9_dcd4_3bed_abef_26fb6df08fab.push_back(battle);
            _argv_a6ddc5a9_dcd4_3bed_abef_26fb6df08fab.push_back(host);
            _argv_a6ddc5a9_dcd4_3bed_abef_26fb6df08fab.push_back(port);
            _argv_a6ddc5a9_dcd4_3bed_abef_26fb6df08fab.push_back(room_id);
            _argv_a6ddc5a9_dcd4_3bed_abef_26fb6df08fab.push_back(account);
            _hub_handle->_gatemng->call_client(client_uuid_1592abb4_a633_3425_a089_a7299018573b, "match_battle_client_role_into_battle", _argv_a6ddc5a9_dcd4_3bed_abef_26fb6df08fab);
        }

    };

    class match_battle_client_multicast
{
    public:
        std::vector<std::string> client_uuids_1592abb4_a633_3425_a089_a7299018573b;
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<match_battle_client_rsp_cb> rsp_cb_match_battle_client_handle;

        match_battle_client_multicast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<match_battle_client_rsp_cb> rsp_cb_match_battle_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_match_battle_client_handle = rsp_cb_match_battle_client_handle_;
        }

    };

    class match_battle_client_broadcast
{
    public:
        std::shared_ptr<hub::hub_service> _hub_handle;
        std::shared_ptr<match_battle_client_rsp_cb> rsp_cb_match_battle_client_handle;

        match_battle_client_broadcast(std::shared_ptr<hub::hub_service> hub_service_, std::shared_ptr<match_battle_client_rsp_cb> rsp_cb_match_battle_client_handle_)
        {
            _hub_handle = hub_service_;
            rsp_cb_match_battle_client_handle = rsp_cb_match_battle_client_handle_;
        }

    };

    class match_battle_client_clientproxy;
    class match_battle_client_multicast;
    class match_battle_client_broadcast;
    class match_battle_client_caller {
    private:
        static std::shared_ptr<match_battle_client_rsp_cb> rsp_cb_match_battle_client_handle;

    private:
        std::shared_ptr<match_battle_client_clientproxy> _clientproxy;
        std::shared_ptr<match_battle_client_multicast> _multicast;
        std::shared_ptr<match_battle_client_broadcast> _broadcast;

    public:
        match_battle_client_caller(std::shared_ptr<hub::hub_service> hub_service_) 
        {
            if (rsp_cb_match_battle_client_handle == nullptr) {
                rsp_cb_match_battle_client_handle = std::make_shared<match_battle_client_rsp_cb>();
                rsp_cb_match_battle_client_handle->Init(hub_service_);
            }
            _clientproxy = std::make_shared<match_battle_client_clientproxy>(hub_service_, rsp_cb_match_battle_client_handle);
            _multicast = std::make_shared<match_battle_client_multicast>(hub_service_, rsp_cb_match_battle_client_handle);
            _broadcast = std::make_shared<match_battle_client_broadcast>(hub_service_, rsp_cb_match_battle_client_handle);
        }

        std::shared_ptr<match_battle_client_clientproxy> get_client(std::string client_uuid) {
            _clientproxy->client_uuid_1592abb4_a633_3425_a089_a7299018573b = client_uuid;
            return _clientproxy;
        }

        std::shared_ptr<match_battle_client_multicast> get_multicast(std::vector<std::string> client_uuids) {
            _multicast->client_uuids_1592abb4_a633_3425_a089_a7299018573b = client_uuids;
            return _multicast;
        }

        std::shared_ptr<match_battle_client_broadcast> get_broadcast() {
            return _broadcast;
        }

    };

}

#endif //_h_matchcallc_4469e89b_854f_3b7a_b691_75c9b21e787b_
