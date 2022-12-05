/*
 * qianqians
 * 2020-1-22
 * battle
 * role_bag.cpp
 */

#include "role_bag.h"
#include "role.h"
#include "role_battle.h"

namespace battle {

int item::count = 0;

item::item() {
    uuid = xg::newGuid().str();
    ++count;
}

gun::gun(int32_t _desc_id) : item() {
    spdlog::trace("Init gun begin!");

    auto _config = json_config::_json_config_mng->json_configs["item"]->get_value_dict(std::to_string(_desc_id));
    desc_id = _desc_id;
    type = _config->get_value_string("type");

    auto _gun_config = json_config::_json_config_mng->json_configs[type]->get_value_dict(std::to_string(_desc_id));
    lv = _gun_config->get_value_int("lv");
    desc_cd_time = _gun_config->get_value_int("cd");
    cd_time = 0;

    spdlog::trace("Init gun end!");
}

gun_bullet::gun_bullet(int32_t _desc_id) : item() {
    spdlog::trace("Init bullet begin!");

    auto _config = json_config::_json_config_mng->json_configs["item"]->get_value_dict(std::to_string(_desc_id));
    auto _gun_config = json_config::_json_config_mng->json_configs["bullet"]->get_value_dict(std::to_string(_desc_id));

    desc_id = _desc_id;
    type = _config->get_value_string("type");

    spdlog::trace("Init bullet end!");
}

equip::equip(int32_t _desc_id) : item() {
    spdlog::trace("Init equip begin!");

    auto _config = json_config::_json_config_mng->json_configs["item"]->get_value_dict(std::to_string(_desc_id));
    auto _equip_config = json_config::_json_config_mng->json_configs["equip"]->get_value_dict(std::to_string(_desc_id));

    desc_id = _desc_id;
    num = 1;
    type = _config->get_value_string("type");

    equip_type = (EM_EQUIP_TYPE)_equip_config->get_value_int("equip_type");
    hp = (int32_t)_equip_config->get_value_int("hp");
    defense = (int32_t)_equip_config->get_value_int("defense");

    spdlog::trace("Init equip end!");
}

medicine::medicine(int32_t _desc_id) : item() {
    spdlog::trace("Init medicine begin!");

    auto _config = json_config::_json_config_mng->json_configs["item"]->get_value_dict(std::to_string(_desc_id));
    auto _medicine_config = json_config::_json_config_mng->json_configs["medicine"]->get_value_dict(std::to_string(_desc_id));

    desc_id = _desc_id;
    num = 1;
    type = _config->get_value_string("type");

    buff_id = (int32_t)_medicine_config->get_value_int("buff");

    spdlog::trace("Init medicine end!");
}

std::shared_ptr<item> create_item(int32_t item_id, int32_t num) {
    spdlog::trace("create_item begin!");

    auto _config = json_config::_json_config_mng->json_configs["item"]->get_value_dict(std::to_string(item_id));
    auto _type = _config->get_value_string("type");
    if (_type == "gun") {
        auto i = std::make_shared<gun>(item_id);
        i->num = num;

        return i;
    }
    if (_type == "rpg") {
        auto i = std::make_shared<gun>(item_id);
        i->num = num;

        return i;
    }
    if (_type == "bullet") {
        auto i = std::make_shared<gun_bullet>(item_id);
        i->num = num;

        return i;
    }
    else if (_type == "equip") {
        auto i = std::make_shared<equip>(item_id);
        return i;
    }
    else if (_type == "medicine") {
        auto i = std::make_shared<medicine>(item_id);
        i->num = num;

        return i;
    }

    spdlog::trace("create_item end!");

    return nullptr;
}

int role_bag::count = 0;

role_bag::role_bag(std::shared_ptr<role> _role) {
    spdlog::trace("Init role_bag begin!");
    _role_handle = _role;
    ++count;
    spdlog::trace("Init role_bag end!");
}

void role_bag::Init() {
    auto _role = _role_handle.lock();
    if (!_role) {
        return;
    }
    //_role->pickup_item(create_item(1001, 30));
    _role->pickup_item(create_item(1102, 30));
    _role->pickup_item(create_item(10002, 30));
    _role->pickup_item(create_item(10003, 30));
}

std::vector<abelkhan::item> role_bag::cs_info() {
    std::vector<abelkhan::item> _bag;
    for (auto item : bag) {
        abelkhan::item _item;
        _item.uuid = item->uuid;
        _item.desc_id = item->desc_id;
        _item.num = item->num;
        _bag.push_back(_item);
    }
    return _bag;
}

bool role_bag::change_equip(std::string item_uuid, std::shared_ptr<role_battle> _role_battle) {
    for (auto item = bag.begin(); item != bag.end(); item++) {
        if ((*item)->uuid != item_uuid) {
            continue;
        }

        auto _equip = *item;
        bag.erase(item);

        if (_equip->type == "gun") {
            _equip = _role_battle->change_gun(std::static_pointer_cast<gun>(_equip));
            if (_equip) {
                bag.push_back(_equip);
            }
        }
        else if (_equip->type == "equip") {
            _equip = _role_battle->change_equip(std::static_pointer_cast<equip>(_equip));
            if (_equip) {
                bag.push_back(_equip);
            }
        }

        return true;
    }

    spdlog::error("change_equip bag not have item:{0}", item_uuid);

    return false;
}

}
