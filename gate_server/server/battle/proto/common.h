#ifndef _h_common_30959b42_b957_3c40_83bb_68014285b0b7_
#define _h_common_30959b42_b957_3c40_83bb_68014285b0b7_

#include <hub_service.h>
#include <signals.h>


namespace abelkhan
{
/*this enum code is codegen by abelkhan codegen for cpp*/

/*this struct code is codegen by abelkhan codegen for cpp*/
    class item {
    public:
        std::string uuid;
        int32_t desc_id;
        int32_t num;

    public:
        static msgpack11::MsgPack::object item_to_protcol(item _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("uuid", _struct.uuid));
            _protocol.insert(std::make_pair("desc_id", _struct.desc_id));
            _protocol.insert(std::make_pair("num", _struct.num));
            return _protocol;
        }

        static item protcol_to_item(const msgpack11::MsgPack::object& _protocol){
            item _struct6be2e26d_6cd6_3912_93ab_87a2fb9d1b5a;
            for(auto i : _protocol){
                if (i.first == "uuid"){
                    _struct6be2e26d_6cd6_3912_93ab_87a2fb9d1b5a.uuid = i.second.string_value();
                }
                else if (i.first == "desc_id"){
                    _struct6be2e26d_6cd6_3912_93ab_87a2fb9d1b5a.desc_id = i.second.int32_value();
                }
                else if (i.first == "num"){
                    _struct6be2e26d_6cd6_3912_93ab_87a2fb9d1b5a.num = i.second.int32_value();
                }
            }
            return _struct6be2e26d_6cd6_3912_93ab_87a2fb9d1b5a;
        }
    };

    class equip {
    public:
        std::string uuid;
        int32_t desc_id;

    public:
        static msgpack11::MsgPack::object equip_to_protcol(equip _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("uuid", _struct.uuid));
            _protocol.insert(std::make_pair("desc_id", _struct.desc_id));
            return _protocol;
        }

        static equip protcol_to_equip(const msgpack11::MsgPack::object& _protocol){
            equip _struct5cc639b6_15a5_3a1e_8b9f_bfc3a8335522;
            for(auto i : _protocol){
                if (i.first == "uuid"){
                    _struct5cc639b6_15a5_3a1e_8b9f_bfc3a8335522.uuid = i.second.string_value();
                }
                else if (i.first == "desc_id"){
                    _struct5cc639b6_15a5_3a1e_8b9f_bfc3a8335522.desc_id = i.second.int32_value();
                }
            }
            return _struct5cc639b6_15a5_3a1e_8b9f_bfc3a8335522;
        }
    };

    class role_battle_info {
    public:
        int32_t title;
        int32_t score;
        int32_t hp;
        int32_t gun;
        int32_t bullets_num;
        int32_t rpg_gun;
        int32_t rpg_bullets_num;
        int32_t grenade_num;
        float angle;
        std::vector<equip> equip_info;

    public:
        static msgpack11::MsgPack::object role_battle_info_to_protcol(role_battle_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("title", _struct.title));
            _protocol.insert(std::make_pair("score", _struct.score));
            _protocol.insert(std::make_pair("hp", _struct.hp));
            _protocol.insert(std::make_pair("gun", _struct.gun));
            _protocol.insert(std::make_pair("bullets_num", _struct.bullets_num));
            _protocol.insert(std::make_pair("rpg_gun", _struct.rpg_gun));
            _protocol.insert(std::make_pair("rpg_bullets_num", _struct.rpg_bullets_num));
            _protocol.insert(std::make_pair("grenade_num", _struct.grenade_num));
            _protocol.insert(std::make_pair("angle", _struct.angle));
            msgpack11::MsgPack::array _array_equip_info;
            for(auto v_ : _struct.equip_info){
                _array_equip_info.push_back(equip::equip_to_protcol(v_));
            }
            _protocol.insert(std::make_pair("equip_info", _array_equip_info));
            return _protocol;
        }

        static role_battle_info protcol_to_role_battle_info(const msgpack11::MsgPack::object& _protocol){
            role_battle_info _struct5593ca57_affb_33f2_aea1_7df161fb4a06;
            for(auto i : _protocol){
                if (i.first == "title"){
                    _struct5593ca57_affb_33f2_aea1_7df161fb4a06.title = i.second.int32_value();
                }
                else if (i.first == "score"){
                    _struct5593ca57_affb_33f2_aea1_7df161fb4a06.score = i.second.int32_value();
                }
                else if (i.first == "hp"){
                    _struct5593ca57_affb_33f2_aea1_7df161fb4a06.hp = i.second.int32_value();
                }
                else if (i.first == "gun"){
                    _struct5593ca57_affb_33f2_aea1_7df161fb4a06.gun = i.second.int32_value();
                }
                else if (i.first == "bullets_num"){
                    _struct5593ca57_affb_33f2_aea1_7df161fb4a06.bullets_num = i.second.int32_value();
                }
                else if (i.first == "rpg_gun"){
                    _struct5593ca57_affb_33f2_aea1_7df161fb4a06.rpg_gun = i.second.int32_value();
                }
                else if (i.first == "rpg_bullets_num"){
                    _struct5593ca57_affb_33f2_aea1_7df161fb4a06.rpg_bullets_num = i.second.int32_value();
                }
                else if (i.first == "grenade_num"){
                    _struct5593ca57_affb_33f2_aea1_7df161fb4a06.grenade_num = i.second.int32_value();
                }
                else if (i.first == "angle"){
                    _struct5593ca57_affb_33f2_aea1_7df161fb4a06.angle = i.second.float32_value();
                }
                else if (i.first == "equip_info"){
                    auto _protocol_array = i.second.array_items();
                    for(auto it_ : _protocol_array){
                        _struct5593ca57_affb_33f2_aea1_7df161fb4a06.equip_info.push_back(equip::protcol_to_equip(it_.object_items()));
            }
                }
            }
            return _struct5593ca57_affb_33f2_aea1_7df161fb4a06;
        }
    };

    class role_battle_base_info {
    public:
        int32_t title;
        int32_t score;

    public:
        static msgpack11::MsgPack::object role_battle_base_info_to_protcol(role_battle_base_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("title", _struct.title));
            _protocol.insert(std::make_pair("score", _struct.score));
            return _protocol;
        }

        static role_battle_base_info protcol_to_role_battle_base_info(const msgpack11::MsgPack::object& _protocol){
            role_battle_base_info _struct740fed13_3e9e_3ac0_962d_d473f0519e42;
            for(auto i : _protocol){
                if (i.first == "title"){
                    _struct740fed13_3e9e_3ac0_962d_d473f0519e42.title = i.second.int32_value();
                }
                else if (i.first == "score"){
                    _struct740fed13_3e9e_3ac0_962d_d473f0519e42.score = i.second.int32_value();
                }
            }
            return _struct740fed13_3e9e_3ac0_962d_d473f0519e42;
        }
    };

    class role_battle_svr_info {
    public:
        std::string battle_hub_name;
        std::string room_id;

    public:
        static msgpack11::MsgPack::object role_battle_svr_info_to_protcol(role_battle_svr_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("battle_hub_name", _struct.battle_hub_name));
            _protocol.insert(std::make_pair("room_id", _struct.room_id));
            return _protocol;
        }

        static role_battle_svr_info protcol_to_role_battle_svr_info(const msgpack11::MsgPack::object& _protocol){
            role_battle_svr_info _structad088a36_0f1f_3e8f_b7b6_08fcb457efe0;
            for(auto i : _protocol){
                if (i.first == "battle_hub_name"){
                    _structad088a36_0f1f_3e8f_b7b6_08fcb457efe0.battle_hub_name = i.second.string_value();
                }
                else if (i.first == "room_id"){
                    _structad088a36_0f1f_3e8f_b7b6_08fcb457efe0.room_id = i.second.string_value();
                }
            }
            return _structad088a36_0f1f_3e8f_b7b6_08fcb457efe0;
        }
    };

    class role_battle_end_info {
    public:
        std::string battle_hub_name;
        std::string room_id;
        int32_t score;

    public:
        static msgpack11::MsgPack::object role_battle_end_info_to_protcol(role_battle_end_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("battle_hub_name", _struct.battle_hub_name));
            _protocol.insert(std::make_pair("room_id", _struct.room_id));
            _protocol.insert(std::make_pair("score", _struct.score));
            return _protocol;
        }

        static role_battle_end_info protcol_to_role_battle_end_info(const msgpack11::MsgPack::object& _protocol){
            role_battle_end_info _struct92c59290_c0d5_316c_b1e1_b03a4217325b;
            for(auto i : _protocol){
                if (i.first == "battle_hub_name"){
                    _struct92c59290_c0d5_316c_b1e1_b03a4217325b.battle_hub_name = i.second.string_value();
                }
                else if (i.first == "room_id"){
                    _struct92c59290_c0d5_316c_b1e1_b03a4217325b.room_id = i.second.string_value();
                }
                else if (i.first == "score"){
                    _struct92c59290_c0d5_316c_b1e1_b03a4217325b.score = i.second.int32_value();
                }
            }
            return _struct92c59290_c0d5_316c_b1e1_b03a4217325b;
        }
    };

    class role_scene_info {
    public:
        int32_t x;
        int32_t y;
        int32_t direction;
        int32_t shoot_direction;

    public:
        static msgpack11::MsgPack::object role_scene_info_to_protcol(role_scene_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("x", _struct.x));
            _protocol.insert(std::make_pair("y", _struct.y));
            _protocol.insert(std::make_pair("direction", _struct.direction));
            _protocol.insert(std::make_pair("shoot_direction", _struct.shoot_direction));
            return _protocol;
        }

        static role_scene_info protcol_to_role_scene_info(const msgpack11::MsgPack::object& _protocol){
            role_scene_info _structcb391230_45c5_3ce8_b9f4_2f34b0b56f83;
            for(auto i : _protocol){
                if (i.first == "x"){
                    _structcb391230_45c5_3ce8_b9f4_2f34b0b56f83.x = i.second.int32_value();
                }
                else if (i.first == "y"){
                    _structcb391230_45c5_3ce8_b9f4_2f34b0b56f83.y = i.second.int32_value();
                }
                else if (i.first == "direction"){
                    _structcb391230_45c5_3ce8_b9f4_2f34b0b56f83.direction = i.second.int32_value();
                }
                else if (i.first == "shoot_direction"){
                    _structcb391230_45c5_3ce8_b9f4_2f34b0b56f83.shoot_direction = i.second.int32_value();
                }
            }
            return _structcb391230_45c5_3ce8_b9f4_2f34b0b56f83;
        }
    };

    class role_body_info {
    public:
        int32_t head;
        int32_t body;
        int32_t foot;

    public:
        static msgpack11::MsgPack::object role_body_info_to_protcol(role_body_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("head", _struct.head));
            _protocol.insert(std::make_pair("body", _struct.body));
            _protocol.insert(std::make_pair("foot", _struct.foot));
            return _protocol;
        }

        static role_body_info protcol_to_role_body_info(const msgpack11::MsgPack::object& _protocol){
            role_body_info _struct127f2dc6_799c_39fc_908f_844853267606;
            for(auto i : _protocol){
                if (i.first == "head"){
                    _struct127f2dc6_799c_39fc_908f_844853267606.head = i.second.int32_value();
                }
                else if (i.first == "body"){
                    _struct127f2dc6_799c_39fc_908f_844853267606.body = i.second.int32_value();
                }
                else if (i.first == "foot"){
                    _struct127f2dc6_799c_39fc_908f_844853267606.foot = i.second.int32_value();
                }
            }
            return _struct127f2dc6_799c_39fc_908f_844853267606;
        }
    };

    class role_info {
    public:
        std::string id;
        std::string account;
        std::string name;
        role_scene_info _scene_info;
        role_body_info _body_info;
        role_battle_info _battle_info;

    public:
        static msgpack11::MsgPack::object role_info_to_protcol(role_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("id", _struct.id));
            _protocol.insert(std::make_pair("account", _struct.account));
            _protocol.insert(std::make_pair("name", _struct.name));
            _protocol.insert(std::make_pair("_scene_info", role_scene_info::role_scene_info_to_protcol(_struct._scene_info)));
            _protocol.insert(std::make_pair("_body_info", role_body_info::role_body_info_to_protcol(_struct._body_info)));
            _protocol.insert(std::make_pair("_battle_info", role_battle_info::role_battle_info_to_protcol(_struct._battle_info)));
            return _protocol;
        }

        static role_info protcol_to_role_info(const msgpack11::MsgPack::object& _protocol){
            role_info _struct758de124_1110_363e_89ed_9051178bed84;
            for(auto i : _protocol){
                if (i.first == "id"){
                    _struct758de124_1110_363e_89ed_9051178bed84.id = i.second.string_value();
                }
                else if (i.first == "account"){
                    _struct758de124_1110_363e_89ed_9051178bed84.account = i.second.string_value();
                }
                else if (i.first == "name"){
                    _struct758de124_1110_363e_89ed_9051178bed84.name = i.second.string_value();
                }
                else if (i.first == "_scene_info"){
                    _struct758de124_1110_363e_89ed_9051178bed84._scene_info = role_scene_info::protcol_to_role_scene_info(i.second.object_items());
                }
                else if (i.first == "_body_info"){
                    _struct758de124_1110_363e_89ed_9051178bed84._body_info = role_body_info::protcol_to_role_body_info(i.second.object_items());
                }
                else if (i.first == "_battle_info"){
                    _struct758de124_1110_363e_89ed_9051178bed84._battle_info = role_battle_info::protcol_to_role_battle_info(i.second.object_items());
                }
            }
            return _struct758de124_1110_363e_89ed_9051178bed84;
        }
    };

    class role_lobby_info {
    public:
        std::string session_uuid;
        std::string id;
        std::string account;
        std::string name;
        std::string lobby;
        role_body_info _body_info;
        role_battle_base_info _battle_base_info;

    public:
        static msgpack11::MsgPack::object role_lobby_info_to_protcol(role_lobby_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("session_uuid", _struct.session_uuid));
            _protocol.insert(std::make_pair("id", _struct.id));
            _protocol.insert(std::make_pair("account", _struct.account));
            _protocol.insert(std::make_pair("name", _struct.name));
            _protocol.insert(std::make_pair("lobby", _struct.lobby));
            _protocol.insert(std::make_pair("_body_info", role_body_info::role_body_info_to_protcol(_struct._body_info)));
            _protocol.insert(std::make_pair("_battle_base_info", role_battle_base_info::role_battle_base_info_to_protcol(_struct._battle_base_info)));
            return _protocol;
        }

        static role_lobby_info protcol_to_role_lobby_info(const msgpack11::MsgPack::object& _protocol){
            role_lobby_info _struct5bc6f6d5_e07c_3405_9201_72b38241fffd;
            for(auto i : _protocol){
                if (i.first == "session_uuid"){
                    _struct5bc6f6d5_e07c_3405_9201_72b38241fffd.session_uuid = i.second.string_value();
                }
                else if (i.first == "id"){
                    _struct5bc6f6d5_e07c_3405_9201_72b38241fffd.id = i.second.string_value();
                }
                else if (i.first == "account"){
                    _struct5bc6f6d5_e07c_3405_9201_72b38241fffd.account = i.second.string_value();
                }
                else if (i.first == "name"){
                    _struct5bc6f6d5_e07c_3405_9201_72b38241fffd.name = i.second.string_value();
                }
                else if (i.first == "lobby"){
                    _struct5bc6f6d5_e07c_3405_9201_72b38241fffd.lobby = i.second.string_value();
                }
                else if (i.first == "_body_info"){
                    _struct5bc6f6d5_e07c_3405_9201_72b38241fffd._body_info = role_body_info::protcol_to_role_body_info(i.second.object_items());
                }
                else if (i.first == "_battle_base_info"){
                    _struct5bc6f6d5_e07c_3405_9201_72b38241fffd._battle_base_info = role_battle_base_info::protcol_to_role_battle_base_info(i.second.object_items());
                }
            }
            return _struct5bc6f6d5_e07c_3405_9201_72b38241fffd;
        }
    };

    class role_find_info {
    public:
        std::string account;
        std::string name;
        role_body_info _body_info;
        role_battle_base_info _battle_base_info;

    public:
        static msgpack11::MsgPack::object role_find_info_to_protcol(role_find_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("account", _struct.account));
            _protocol.insert(std::make_pair("name", _struct.name));
            _protocol.insert(std::make_pair("_body_info", role_body_info::role_body_info_to_protcol(_struct._body_info)));
            _protocol.insert(std::make_pair("_battle_base_info", role_battle_base_info::role_battle_base_info_to_protcol(_struct._battle_base_info)));
            return _protocol;
        }

        static role_find_info protcol_to_role_find_info(const msgpack11::MsgPack::object& _protocol){
            role_find_info _struct409ea6c7_a99e_3928_938d_f52afc2c8cf3;
            for(auto i : _protocol){
                if (i.first == "account"){
                    _struct409ea6c7_a99e_3928_938d_f52afc2c8cf3.account = i.second.string_value();
                }
                else if (i.first == "name"){
                    _struct409ea6c7_a99e_3928_938d_f52afc2c8cf3.name = i.second.string_value();
                }
                else if (i.first == "_body_info"){
                    _struct409ea6c7_a99e_3928_938d_f52afc2c8cf3._body_info = role_body_info::protcol_to_role_body_info(i.second.object_items());
                }
                else if (i.first == "_battle_base_info"){
                    _struct409ea6c7_a99e_3928_938d_f52afc2c8cf3._battle_base_info = role_battle_base_info::protcol_to_role_battle_base_info(i.second.object_items());
                }
            }
            return _struct409ea6c7_a99e_3928_938d_f52afc2c8cf3;
        }
    };

    class role_friend_info {
    public:
        std::string account;
        std::string name;

    public:
        static msgpack11::MsgPack::object role_friend_info_to_protcol(role_friend_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("account", _struct.account));
            _protocol.insert(std::make_pair("name", _struct.name));
            return _protocol;
        }

        static role_friend_info protcol_to_role_friend_info(const msgpack11::MsgPack::object& _protocol){
            role_friend_info _structaa75f85e_956e_356b_963e_d1da39a70f5d;
            for(auto i : _protocol){
                if (i.first == "account"){
                    _structaa75f85e_956e_356b_963e_d1da39a70f5d.account = i.second.string_value();
                }
                else if (i.first == "name"){
                    _structaa75f85e_956e_356b_963e_d1da39a70f5d.name = i.second.string_value();
                }
            }
            return _structaa75f85e_956e_356b_963e_d1da39a70f5d;
        }
    };

    class main_role_info {
    public:
        std::string id;
        std::string account;
        std::string name;
        std::string team_id;
        std::vector<item> _bag_info;
        role_scene_info _scene_info;
        role_body_info _body_info;
        role_battle_info _battle_info;
        std::vector<std::string> _skill_info;

    public:
        static msgpack11::MsgPack::object main_role_info_to_protcol(main_role_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("id", _struct.id));
            _protocol.insert(std::make_pair("account", _struct.account));
            _protocol.insert(std::make_pair("name", _struct.name));
            _protocol.insert(std::make_pair("team_id", _struct.team_id));
            msgpack11::MsgPack::array _array__bag_info;
            for(auto v_ : _struct._bag_info){
                _array__bag_info.push_back(item::item_to_protcol(v_));
            }
            _protocol.insert(std::make_pair("_bag_info", _array__bag_info));
            _protocol.insert(std::make_pair("_scene_info", role_scene_info::role_scene_info_to_protcol(_struct._scene_info)));
            _protocol.insert(std::make_pair("_body_info", role_body_info::role_body_info_to_protcol(_struct._body_info)));
            _protocol.insert(std::make_pair("_battle_info", role_battle_info::role_battle_info_to_protcol(_struct._battle_info)));
            msgpack11::MsgPack::array _array__skill_info;
            for(auto v_ : _struct._skill_info){
                _array__skill_info.push_back(v_);
            }
            _protocol.insert(std::make_pair("_skill_info", _array__skill_info));
            return _protocol;
        }

        static main_role_info protcol_to_main_role_info(const msgpack11::MsgPack::object& _protocol){
            main_role_info _struct451a594b_4b36_3ca1_a38d_d048310f079e;
            for(auto i : _protocol){
                if (i.first == "id"){
                    _struct451a594b_4b36_3ca1_a38d_d048310f079e.id = i.second.string_value();
                }
                else if (i.first == "account"){
                    _struct451a594b_4b36_3ca1_a38d_d048310f079e.account = i.second.string_value();
                }
                else if (i.first == "name"){
                    _struct451a594b_4b36_3ca1_a38d_d048310f079e.name = i.second.string_value();
                }
                else if (i.first == "team_id"){
                    _struct451a594b_4b36_3ca1_a38d_d048310f079e.team_id = i.second.string_value();
                }
                else if (i.first == "_bag_info"){
                    auto _protocol_array = i.second.array_items();
                    for(auto it_ : _protocol_array){
                        _struct451a594b_4b36_3ca1_a38d_d048310f079e._bag_info.push_back(item::protcol_to_item(it_.object_items()));
            }
                }
                else if (i.first == "_scene_info"){
                    _struct451a594b_4b36_3ca1_a38d_d048310f079e._scene_info = role_scene_info::protcol_to_role_scene_info(i.second.object_items());
                }
                else if (i.first == "_body_info"){
                    _struct451a594b_4b36_3ca1_a38d_d048310f079e._body_info = role_body_info::protcol_to_role_body_info(i.second.object_items());
                }
                else if (i.first == "_battle_info"){
                    _struct451a594b_4b36_3ca1_a38d_d048310f079e._battle_info = role_battle_info::protcol_to_role_battle_info(i.second.object_items());
                }
                else if (i.first == "_skill_info"){
                    auto _protocol_array = i.second.array_items();
                    for(auto it_ : _protocol_array){
                        _struct451a594b_4b36_3ca1_a38d_d048310f079e._skill_info.push_back(it_.string_value());
            }
                }
            }
            return _struct451a594b_4b36_3ca1_a38d_d048310f079e;
        }
    };

    class house_info {
    public:
        int32_t x;
        int32_t y;
        int32_t collision;
        int32_t hp;

    public:
        static msgpack11::MsgPack::object house_info_to_protcol(house_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("x", _struct.x));
            _protocol.insert(std::make_pair("y", _struct.y));
            _protocol.insert(std::make_pair("collision", _struct.collision));
            _protocol.insert(std::make_pair("hp", _struct.hp));
            return _protocol;
        }

        static house_info protcol_to_house_info(const msgpack11::MsgPack::object& _protocol){
            house_info _struct00f32214_fd5b_3242_9e5b_6352f8568e6b;
            for(auto i : _protocol){
                if (i.first == "x"){
                    _struct00f32214_fd5b_3242_9e5b_6352f8568e6b.x = i.second.int32_value();
                }
                else if (i.first == "y"){
                    _struct00f32214_fd5b_3242_9e5b_6352f8568e6b.y = i.second.int32_value();
                }
                else if (i.first == "collision"){
                    _struct00f32214_fd5b_3242_9e5b_6352f8568e6b.collision = i.second.int32_value();
                }
                else if (i.first == "hp"){
                    _struct00f32214_fd5b_3242_9e5b_6352f8568e6b.hp = i.second.int32_value();
                }
            }
            return _struct00f32214_fd5b_3242_9e5b_6352f8568e6b;
        }
    };

    class drop_item_info {
    public:
        std::string uuid;
        int32_t desc_id;
        bool is_in_house;
        int32_t x;
        int32_t y;

    public:
        static msgpack11::MsgPack::object drop_item_info_to_protcol(drop_item_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("uuid", _struct.uuid));
            _protocol.insert(std::make_pair("desc_id", _struct.desc_id));
            _protocol.insert(std::make_pair("is_in_house", _struct.is_in_house));
            _protocol.insert(std::make_pair("x", _struct.x));
            _protocol.insert(std::make_pair("y", _struct.y));
            return _protocol;
        }

        static drop_item_info protcol_to_drop_item_info(const msgpack11::MsgPack::object& _protocol){
            drop_item_info _structf7c10a1c_715c_34ad_a718_0d4bbab0ade8;
            for(auto i : _protocol){
                if (i.first == "uuid"){
                    _structf7c10a1c_715c_34ad_a718_0d4bbab0ade8.uuid = i.second.string_value();
                }
                else if (i.first == "desc_id"){
                    _structf7c10a1c_715c_34ad_a718_0d4bbab0ade8.desc_id = i.second.int32_value();
                }
                else if (i.first == "is_in_house"){
                    _structf7c10a1c_715c_34ad_a718_0d4bbab0ade8.is_in_house = i.second.bool_value();
                }
                else if (i.first == "x"){
                    _structf7c10a1c_715c_34ad_a718_0d4bbab0ade8.x = i.second.int32_value();
                }
                else if (i.first == "y"){
                    _structf7c10a1c_715c_34ad_a718_0d4bbab0ade8.y = i.second.int32_value();
                }
            }
            return _structf7c10a1c_715c_34ad_a718_0d4bbab0ade8;
        }
    };

    class wreck_box_info {
    public:
        int32_t x;
        int32_t y;
        int32_t tiled_x;
        int32_t tiled_y;

    public:
        static msgpack11::MsgPack::object wreck_box_info_to_protcol(wreck_box_info _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("x", _struct.x));
            _protocol.insert(std::make_pair("y", _struct.y));
            _protocol.insert(std::make_pair("tiled_x", _struct.tiled_x));
            _protocol.insert(std::make_pair("tiled_y", _struct.tiled_y));
            return _protocol;
        }

        static wreck_box_info protcol_to_wreck_box_info(const msgpack11::MsgPack::object& _protocol){
            wreck_box_info _struct30b47e3b_4cfd_315e_9cfe_c0208c3d3e1b;
            for(auto i : _protocol){
                if (i.first == "x"){
                    _struct30b47e3b_4cfd_315e_9cfe_c0208c3d3e1b.x = i.second.int32_value();
                }
                else if (i.first == "y"){
                    _struct30b47e3b_4cfd_315e_9cfe_c0208c3d3e1b.y = i.second.int32_value();
                }
                else if (i.first == "tiled_x"){
                    _struct30b47e3b_4cfd_315e_9cfe_c0208c3d3e1b.tiled_x = i.second.int32_value();
                }
                else if (i.first == "tiled_y"){
                    _struct30b47e3b_4cfd_315e_9cfe_c0208c3d3e1b.tiled_y = i.second.int32_value();
                }
            }
            return _struct30b47e3b_4cfd_315e_9cfe_c0208c3d3e1b;
        }
    };

    class team_member {
    public:
        std::string session_uuid;
        std::string lobby;
        std::string account;
        std::string name;
        std::string id;
        bool is_ready;
        role_body_info _body_info;
        role_battle_base_info _battle_base_info;

    public:
        static msgpack11::MsgPack::object team_member_to_protcol(team_member _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("session_uuid", _struct.session_uuid));
            _protocol.insert(std::make_pair("lobby", _struct.lobby));
            _protocol.insert(std::make_pair("account", _struct.account));
            _protocol.insert(std::make_pair("name", _struct.name));
            _protocol.insert(std::make_pair("id", _struct.id));
            _protocol.insert(std::make_pair("is_ready", _struct.is_ready));
            _protocol.insert(std::make_pair("_body_info", role_body_info::role_body_info_to_protcol(_struct._body_info)));
            _protocol.insert(std::make_pair("_battle_base_info", role_battle_base_info::role_battle_base_info_to_protcol(_struct._battle_base_info)));
            return _protocol;
        }

        static team_member protcol_to_team_member(const msgpack11::MsgPack::object& _protocol){
            team_member _struct9182bddb_444c_3e06_99d7_bda264b1e3a3;
            for(auto i : _protocol){
                if (i.first == "session_uuid"){
                    _struct9182bddb_444c_3e06_99d7_bda264b1e3a3.session_uuid = i.second.string_value();
                }
                else if (i.first == "lobby"){
                    _struct9182bddb_444c_3e06_99d7_bda264b1e3a3.lobby = i.second.string_value();
                }
                else if (i.first == "account"){
                    _struct9182bddb_444c_3e06_99d7_bda264b1e3a3.account = i.second.string_value();
                }
                else if (i.first == "name"){
                    _struct9182bddb_444c_3e06_99d7_bda264b1e3a3.name = i.second.string_value();
                }
                else if (i.first == "id"){
                    _struct9182bddb_444c_3e06_99d7_bda264b1e3a3.id = i.second.string_value();
                }
                else if (i.first == "is_ready"){
                    _struct9182bddb_444c_3e06_99d7_bda264b1e3a3.is_ready = i.second.bool_value();
                }
                else if (i.first == "_body_info"){
                    _struct9182bddb_444c_3e06_99d7_bda264b1e3a3._body_info = role_body_info::protcol_to_role_body_info(i.second.object_items());
                }
                else if (i.first == "_battle_base_info"){
                    _struct9182bddb_444c_3e06_99d7_bda264b1e3a3._battle_base_info = role_battle_base_info::protcol_to_role_battle_base_info(i.second.object_items());
                }
            }
            return _struct9182bddb_444c_3e06_99d7_bda264b1e3a3;
        }
    };

    class team {
    public:
        std::string id;
        std::vector<team_member> members;

    public:
        static msgpack11::MsgPack::object team_to_protcol(team _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("id", _struct.id));
            msgpack11::MsgPack::array _array_members;
            for(auto v_ : _struct.members){
                _array_members.push_back(team_member::team_member_to_protcol(v_));
            }
            _protocol.insert(std::make_pair("members", _array_members));
            return _protocol;
        }

        static team protcol_to_team(const msgpack11::MsgPack::object& _protocol){
            team _struct4069bbd0_98ae_3a36_b524_1bc296e83c22;
            for(auto i : _protocol){
                if (i.first == "id"){
                    _struct4069bbd0_98ae_3a36_b524_1bc296e83c22.id = i.second.string_value();
                }
                else if (i.first == "members"){
                    auto _protocol_array = i.second.array_items();
                    for(auto it_ : _protocol_array){
                        _struct4069bbd0_98ae_3a36_b524_1bc296e83c22.members.push_back(team_member::protcol_to_team_member(it_.object_items()));
            }
                }
            }
            return _struct4069bbd0_98ae_3a36_b524_1bc296e83c22;
        }
    };

    class match_team {
    public:
        std::string id;
        std::string leader;
        std::vector<team_member> members;

    public:
        static msgpack11::MsgPack::object match_team_to_protcol(match_team _struct){
            msgpack11::MsgPack::object _protocol;
            _protocol.insert(std::make_pair("id", _struct.id));
            _protocol.insert(std::make_pair("leader", _struct.leader));
            msgpack11::MsgPack::array _array_members;
            for(auto v_ : _struct.members){
                _array_members.push_back(team_member::team_member_to_protcol(v_));
            }
            _protocol.insert(std::make_pair("members", _array_members));
            return _protocol;
        }

        static match_team protcol_to_match_team(const msgpack11::MsgPack::object& _protocol){
            match_team _structad3e21aa_ee57_3bad_b8e7_00c8cd7b338a;
            for(auto i : _protocol){
                if (i.first == "id"){
                    _structad3e21aa_ee57_3bad_b8e7_00c8cd7b338a.id = i.second.string_value();
                }
                else if (i.first == "leader"){
                    _structad3e21aa_ee57_3bad_b8e7_00c8cd7b338a.leader = i.second.string_value();
                }
                else if (i.first == "members"){
                    auto _protocol_array = i.second.array_items();
                    for(auto it_ : _protocol_array){
                        _structad3e21aa_ee57_3bad_b8e7_00c8cd7b338a.members.push_back(team_member::protcol_to_team_member(it_.object_items()));
            }
                }
            }
            return _structad3e21aa_ee57_3bad_b8e7_00c8cd7b338a;
        }
    };

/*this caller code is codegen by abelkhan codegen for cpp*/
/*this module code is codegen by abelkhan codegen for cpp*/

}

#endif //_h_common_30959b42_b957_3c40_83bb_68014285b0b7_
