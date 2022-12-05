/*
 * qianqians
 * 2020-1-22
 * battle
 * role_bag.h
 */
#ifndef _role_bag_h
#define _role_bag_h

#include <cstdint>
#include <vector>
#include <memory>

#include <hub.h>

#include <common.h>

#include "../json_config/json_config_mng.h"

namespace battle {

class item {
public:
    bool is_in_house = false;
    int32_t desc_id = 0;
    int32_t num = 0;
    std::string uuid;
    std::string type;

    int32_t x = 0;
    int32_t y = 0;

private:
    static int count;

public:
    item();

    virtual ~item() {
        spdlog::trace("item destruction count:{}", --count);
    }

};

class gun : public item {
public:
    uint64_t lv;
    uint64_t desc_cd_time;
    uint64_t cd_time;

public:
    gun(int32_t _desc_id);

    virtual ~gun() {
        spdlog::trace("gun destruction");
    }

};

class gun_bullet : public item {
public:
    gun_bullet(int32_t _desc_id);

    virtual ~gun_bullet() {
        spdlog::trace("gun_bullet destruction");
    }

};

enum struct EM_EQUIP_TYPE {
    EM_EQUIP_TYPE_CASQUE = 1,
    EM_EQUIP_TYPE_BULLETPROOF = 2,
    EM_EQUIP_TYPE_BOOTS = 3,
};

class equip : public item {
public:
    EM_EQUIP_TYPE equip_type;
    int32_t hp;
    int32_t defense;

public:
    equip(int32_t _desc_id);

    virtual ~equip() {
        spdlog::trace("equip destruction");
    }

};

class medicine : public item {
public:
    int32_t buff_id;

public:
    medicine(int32_t _desc_id);

    virtual ~medicine() {
        spdlog::trace("medicine destruction");
    }

};

std::shared_ptr<item> create_item(int32_t item_id, int32_t num);

class role;
class role_battle;
class role_bag {
public:
    std::weak_ptr<role> _role_handle;
    std::vector<std::shared_ptr<item> > bag;

private:
    static int count;

public:
    role_bag(std::shared_ptr<role> _role);

    virtual ~role_bag() {
        spdlog::trace("role_bag destruction count:{0}", --count);
    }

    void Init();

    std::vector<abelkhan::item> cs_info();

    bool change_equip(std::string item_uuid, std::shared_ptr<role_battle> _role_battle);

};

}

#endif //_role_bag_h