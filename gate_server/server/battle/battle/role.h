/*
 * qianqians
 * 2020-1-23
 * battle
 * role.h
 */
#ifndef _role_h
#define _role_h

#include <memory>
#include <string>

#include <hub.h>
#include <memory>

#include "../call_mng.h"

#include "role_scene.h"
#include "role_battle.h"
#include "role_bag.h"
#include "role_body.h"
#include "role_skill.h"
#include "buff.h"
#include "battle.h"

namespace battle {

class team;
class role : public std::enable_shared_from_this<role> {
public:
    std::string id;
    std::string uuid;
    std::string account;
    std::string name;
    std::string lobby;

    std::vector<std::shared_ptr<buff> > _buff_list;
    std::vector<std::weak_ptr<role> > _kill_list;

    std::weak_ptr<team> _team_handle;
    std::weak_ptr<battle> _battle_handle;

    int64_t last_active_timetmp = 0;

    bool is_robot = false;
    bool load_scene_done = false;
    bool is_live = true;
    bool is_exception = false;
    bool is_leave_battle = false;

public:
    std::shared_ptr<role_bag> _role_bag_handle;
    std::shared_ptr<role_body> _role_body_handle;
    std::shared_ptr<role_scene> _role_scene_handle;
    std::shared_ptr<role_battle> _role_battle_handle;
    std::shared_ptr<role_skill> _role_skill_handle;

private:
    static int count;

public:
    role() {
        ++count;
    }

    virtual ~role() {
        spdlog::trace("role destruction count:{0}", --count);
    }

    void Init(std::shared_ptr<map> _map, abelkhan::team_member cs_role) {
        spdlog::trace("Init role begin!");

        uuid = cs_role.session_uuid;
        lobby = cs_role.lobby;
        account = cs_role.account;
        name = cs_role.name;
        id = cs_role.id;

        _role_body_handle = std::make_shared<role_body>(cs_role._body_info);
        _role_battle_handle = std::make_shared<role_battle>(cs_role._battle_base_info, shared_from_this());
        _role_bag_handle = std::make_shared<role_bag>(shared_from_this());
        _role_scene_handle = std::make_shared<role_scene>(shared_from_this(), _map->random_born(), 128);
        std::vector<std::string> skill_list = {"roll", "sprint", "treatment", "twostepjump"};
        _role_skill_handle = std::make_shared<role_skill>(shared_from_this(), skill_list);

        //Fossilizid::JsonParse::JsonCast<Fossilizid::JsonParse::JsonArray>((*cs_role)["bag"]));
        _role_bag_handle->Init();

        _role_battle_handle->ntf_shoot_direction();

        //_team_handle = nullptr;
        //_battle_handle = nullptr;

        is_robot = false;
        load_scene_done = false;
        is_live = true;

        is_exception = false;

        spdlog::trace("Init role end!");
    }

    abelkhan::role_info cs_info() {
        abelkhan::role_info info;
        info.id = id;
        info.account = account;
        info.name = name;
        info._scene_info = _role_scene_handle->cs_info();
        info._body_info = _role_body_handle->cs_info();
        info._battle_info = _role_battle_handle->cs_info();
        return info;
    }

    abelkhan::main_role_info main_cs_info();

    void role_dead() {
        spdlog::trace("role_dead begin!");

        is_live = false;

        auto _battle = _battle_handle.lock();
        if (!_battle) {
            return;
        }

        auto _map = _role_scene_handle->_map_handle.lock();
        if (!_map) {
            return;
        }

        auto pos = _role_scene_handle->_obb->get_center_pos();
        auto _sub_map = _map->get_sub_map(pos.x);

        std::vector<abelkhan::drop_item_info> _drop_item_list;
        int32_t count = 0;
        for (auto item : _role_bag_handle->bag) {
            if (count > 5) {
                break;
            }

            int32_t offset = 8 * (count / 2);
            item->is_in_house = _role_battle_handle->is_in_house;
            item->x = pos.x + offset;
            item->y = pos.y;
            _map->check_and_init(item->is_in_house, item->x, item->y);
            _sub_map->item_box_list.push_back(item);

            abelkhan::drop_item_info _drop_item_info;
            _drop_item_info.uuid = item->uuid;
            _drop_item_info.desc_id = item->desc_id;
            _drop_item_info.is_in_house = item->is_in_house;
            _drop_item_info.x = item->x;
            _drop_item_info.y = item->y;
            _drop_item_list.push_back(_drop_item_info);

            count++;
        }
        {
            if (count <= 5) {
                if (_role_battle_handle->_gun) {
                    _role_battle_handle->_gun->is_in_house = _role_battle_handle->is_in_house;
                    int32_t offset = 8 * (count / 2);
                    offset = (count % 2) == 0 ? (0 - offset) : offset;
                    _role_battle_handle->_gun->x = pos.x + offset;
                    _role_battle_handle->_gun->y = pos.y;
                    _role_battle_handle->_gun->num = _role_battle_handle->_bullets_num;
                    _map->check_and_init(_role_battle_handle->_gun->is_in_house, _role_battle_handle->_gun->x, _role_battle_handle->_gun->y);
                    _sub_map->item_box_list.push_back(_role_battle_handle->_gun);

                    abelkhan::drop_item_info _drop_item_info;
                    _drop_item_info.uuid = _role_battle_handle->_gun->uuid;
                    _drop_item_info.desc_id = _role_battle_handle->_gun->desc_id;
                    _drop_item_info.is_in_house = _role_battle_handle->_gun->is_in_house;
                    _drop_item_info.x = _role_battle_handle->_gun->x;
                    _drop_item_info.y = _role_battle_handle->_gun->y;
                    _drop_item_list.push_back(_drop_item_info);

                    count++;
                }
            }

            for (auto equip : _role_battle_handle->_equip) {
                if (count > 5) {
                    break;
                }

                equip.second->is_in_house = _role_battle_handle->is_in_house;
                int32_t offset = 8 * (++count / 2);
                offset = (count % 2) == 0 ? (0 - offset) : offset;
                equip.second->x = pos.x + offset;
                equip.second->y = pos.y;
                _map->check_and_init(equip.second->is_in_house, equip.second->x, equip.second->y);
                _sub_map->item_box_list.push_back(equip.second);

                abelkhan::drop_item_info _drop_item_info;
                _drop_item_info.uuid = equip.second->uuid;
                _drop_item_info.desc_id = equip.second->desc_id;
                _drop_item_info.is_in_house = equip.second->is_in_house;
                _drop_item_info.x = equip.second->x;
                _drop_item_info.y = equip.second->y;
                _drop_item_list.push_back(_drop_item_info);

                count++;
            }
        }
        _call_mng_handle->battle_client_caller->get_multicast(_battle->battle_field_uudis())->drop_item_list(_drop_item_list);

        spdlog::trace("role_dead end!");
    }

    void drop_item(std::string item_uuid, int32_t num) {
        auto _battle = _battle_handle.lock();
        if (!_battle) {
            return;
        }

        auto _map = _role_scene_handle->_map_handle.lock();
        if (!_map) {
            return;
        }

        auto pos = _role_scene_handle->_obb->get_center_pos();
        auto _sub_map = _map->get_sub_map(pos.x);

        std::vector<abelkhan::drop_item_info> _drop_item_list;
        abelkhan::drop_item_info _drop_item_info;

        for (auto _item_it = _role_bag_handle->bag.begin(); _item_it != _role_bag_handle->bag.end(); _item_it++) {
            if ((*_item_it)->uuid != item_uuid) {
                continue;
            }

            if ((*_item_it)->type == "gun") {
                (*_item_it)->num = 1;
                (*_item_it)->x = pos.x;
                (*_item_it)->y = pos.y;
                (*_item_it)->is_in_house = _role_battle_handle->is_in_house;
                _map->check_and_init((*_item_it)->is_in_house, (*_item_it)->x, (*_item_it)->y);
                _sub_map->item_box_list.push_back((*_item_it));

                _drop_item_info.uuid = (*_item_it)->uuid;
                _drop_item_info.desc_id = (*_item_it)->desc_id;
                _drop_item_info.is_in_house = (*_item_it)->is_in_house;
                _drop_item_info.x = (*_item_it)->x;
                _drop_item_info.y = (*_item_it)->y;
                _drop_item_list.push_back(_drop_item_info);
                _call_mng_handle->battle_client_caller->get_multicast(_battle->battle_field_uudis())->drop_item_list(_drop_item_list);

                _role_bag_handle->bag.erase(_item_it);
            }
            else if ((*_item_it)->type == "medicine") {
                num = num > (*_item_it)->num ? (*_item_it)->num : num;
                (*_item_it)->num -= num;
                auto _drop_item = create_item((*_item_it)->desc_id, num);
                if ((*_item_it)->num <= 0) {
                    _role_bag_handle->bag.erase(_item_it);
                }
                _drop_item->x = pos.x;
                _drop_item->y = pos.y;
                _drop_item->is_in_house = _role_battle_handle->is_in_house;
                _map->check_and_init(_drop_item->is_in_house, _drop_item->x, _drop_item->y);
                _sub_map->item_box_list.push_back(_drop_item);

                _drop_item_info.uuid = _drop_item->uuid;
                _drop_item_info.desc_id = _drop_item->desc_id;
                _drop_item_info.is_in_house = _drop_item->is_in_house;
                _drop_item_info.x = _drop_item->x;
                _drop_item_info.y = _drop_item->y;
                _drop_item_list.push_back(_drop_item_info);
                _call_mng_handle->battle_client_caller->get_multicast(_battle->battle_field_uudis())->drop_item_list(_drop_item_list);
            }
            else {
                num = 1;
                (*_item_it)->x = pos.x;
                (*_item_it)->y = pos.y;
                (*_item_it)->is_in_house = _role_battle_handle->is_in_house;
                _map->check_and_init((*_item_it)->is_in_house, (*_item_it)->x, (*_item_it)->y);
                _sub_map->item_box_list.push_back((*_item_it));

                _drop_item_info.uuid = (*_item_it)->uuid;
                _drop_item_info.desc_id = (*_item_it)->desc_id;
                _drop_item_info.is_in_house = (*_item_it)->is_in_house;
                _drop_item_info.x = (*_item_it)->x;
                _drop_item_info.y = (*_item_it)->y;
                _drop_item_list.push_back(_drop_item_info);
                _call_mng_handle->battle_client_caller->get_multicast(_battle->battle_field_uudis())->drop_item_list(_drop_item_list);

                _role_bag_handle->bag.erase(_item_it);
            }
            return;
        }

        if (_role_battle_handle->_gun && _role_battle_handle->_gun->uuid == item_uuid) {
            _role_battle_handle->_gun->num = 1;
            _role_battle_handle->_gun->x = pos.x;
            _role_battle_handle->_gun->y = pos.y;
            _role_battle_handle->_gun->is_in_house = _role_battle_handle->is_in_house;
            _map->check_and_init(_role_battle_handle->_gun->is_in_house, _role_battle_handle->_gun->x, _role_battle_handle->_gun->y);
            _sub_map->item_box_list.push_back(_role_battle_handle->_gun);

            _drop_item_info.uuid = _role_battle_handle->_gun->uuid;
            _drop_item_info.desc_id = _role_battle_handle->_gun->desc_id;
            _drop_item_info.is_in_house = _role_battle_handle->_gun->is_in_house;
            _drop_item_info.x = _role_battle_handle->_gun->x;
            _drop_item_info.y = _role_battle_handle->_gun->y;
            _drop_item_list.push_back(_drop_item_info);
            _call_mng_handle->battle_client_caller->get_multicast(_battle->battle_field_uudis())->drop_item_list(_drop_item_list);

            _role_battle_handle->_gun = nullptr;
            return;
        }
        for (auto equip : _role_battle_handle->_equip) {
            if (equip.second->uuid == item_uuid) {
                num = 1;
                equip.second->x = pos.x;
                equip.second->y = pos.y;
                equip.second->is_in_house = _role_battle_handle->is_in_house;
                _map->check_and_init(equip.second->is_in_house, equip.second->x, equip.second->y);
                _sub_map->item_box_list.push_back(equip.second);

                _drop_item_info.uuid = equip.second->uuid;
                _drop_item_info.desc_id = equip.second->desc_id;
                _drop_item_info.is_in_house = equip.second->is_in_house;
                _drop_item_info.x = equip.second->x;
                _drop_item_info.y = equip.second->y;
                _drop_item_list.push_back(_drop_item_info);
                _call_mng_handle->battle_client_caller->get_multicast(_battle->battle_field_uudis())->drop_item_list(_drop_item_list);

                _role_battle_handle->_equip.erase(equip.first);
                return;
            }
        }
    }

    void drop_bullet(int32_t num) {
        auto _battle = _battle_handle.lock();
        if (!_battle) {
            return;
        }

        auto _map = _role_scene_handle->_map_handle.lock();
        if (!_map) {
            return;
        }

        auto pos = _role_scene_handle->_obb->get_center_pos();
        auto _sub_map = _map->get_sub_map(pos.x);

        std::vector<abelkhan::drop_item_info> _drop_item_list;
        abelkhan::drop_item_info _drop_item_info;

        num = num < _role_battle_handle->_bullets_num ? num : _role_battle_handle->_bullets_num;
        _role_battle_handle->_bullets_num -= num;
        auto _item = create_item(10001, num);
        _item->x = pos.x;
        _item->y = pos.y;
        _item->is_in_house = _role_battle_handle->is_in_house;
        _map->check_and_init(_item->is_in_house, _item->x, _item->y);
        _sub_map->item_box_list.push_back(_item);

        _drop_item_info.uuid = _item->uuid;
        _drop_item_info.desc_id = _item->desc_id;
        _drop_item_info.is_in_house = _item->is_in_house;
        _drop_item_info.x = _item->x;
        _drop_item_info.y = _item->y;
        _drop_item_list.push_back(_drop_item_info);
        _call_mng_handle->battle_client_caller->get_multicast(_battle->battle_field_uudis())->drop_item_list(_drop_item_list);
    }

    void check_pickup() {
        if (!is_live) {
            return;
        }

        auto _map = _role_scene_handle->_map_handle.lock();
        if (!_map) {
            return;
        }

        auto _battle = _battle_handle.lock();
        if (!_battle) {
            return;
        }

        std::vector<std::string> leave_field_drop_item_uuid;
        auto _sub_map = _map->get_sub_map(_role_scene_handle->get_scene_x());
        for (auto _drop_item = _sub_map->item_box_list.begin(); _drop_item != _sub_map->item_box_list.end(); ) {
            auto pos = _role_scene_handle->_obb->get_center_pos();
            int32_t offset_x = (int32_t)((*_drop_item)->x) - pos.x;
            int32_t offset_y = (int32_t)((*_drop_item)->y) - pos.y;

            if (abs(offset_x) < 16 && abs(offset_y) < 16) {
                pickup_item(*_drop_item);
                leave_field_drop_item_uuid.push_back((*_drop_item)->uuid);

                _drop_item = _sub_map->item_box_list.erase(_drop_item);
                continue;
            }

            _drop_item++;
        }

        _call_mng_handle->battle_client_caller->get_multicast(_battle->battle_field_uudis())->leave_field_info(leave_field_drop_item_uuid);

        if (leave_field_drop_item_uuid.size() > 0) {
            _call_mng_handle->battle_client_caller->get_client(uuid)->bag_info(_role_bag_handle->cs_info());
            _call_mng_handle->battle_client_caller->get_client(uuid)->battle_info(_role_battle_handle->cs_info());
        }
    }

    void pickup_item(std::shared_ptr<item> item) {
        if (item->is_in_house != _role_battle_handle->is_in_house) {
            spdlog::error("item and player not in same layer role uuid:{0}", uuid);
            return;
        }

        if (item->type == "bullet") {
            if (item->desc_id == 10001) {
                _role_battle_handle->_bullets_num += item->num;
            }
            else if (item->desc_id == 10002) {
                _role_battle_handle->_rpg_bullets_num += item->num;
            }
            else if (item->desc_id == 10003) {
                _role_battle_handle->_grenade_num += item->num;
            }
            return;
        }

        if (item->type == "gun") {
            auto _gun = std::static_pointer_cast<gun>(item);
            if (_role_battle_handle->_gun == nullptr) {
                _role_battle_handle->_gun = _gun;
                _role_battle_handle->_bullets_num += _gun->num;
                item->num = 0;
                return;
            }
            else if (_gun->lv > _role_battle_handle->_gun->lv) {
                _role_bag_handle->bag.push_back(_role_battle_handle->_gun);
                _role_battle_handle->_gun = _gun;
                _role_battle_handle->_bullets_num += _gun->num;
                item->num = 0;
                return;
            }
            else {
                _role_battle_handle->_bullets_num += item->num;
                item->num = 0;
            }
        }

        if (item->type == "rpg") {
            if (_role_battle_handle->_rpg_gun == nullptr) {
                _role_battle_handle->_rpg_gun = std::static_pointer_cast<gun>(item);
                _role_battle_handle->_rpg_bullets_num += item->num;
                item->num = 0;
                return;
            }
            else {
                _role_battle_handle->_rpg_bullets_num += item->num;
                item->num = 0;
            }
        }

        for (auto it = _role_bag_handle->bag.begin(); it != _role_bag_handle->bag.end(); it++) {
            if (item->desc_id != (*it)->desc_id) {
                continue;
            }

            if ((*it)->type == "medicine") {
                (*it)->num += item->num;
                return;
            }
        }

        _role_bag_handle->bag.push_back(item);
    }

    void use_medicine(std::string medicine_uuid) {
        for (auto it = _role_bag_handle->bag.begin(); it != _role_bag_handle->bag.end(); it++) {
            if (medicine_uuid != (*it)->uuid) {
                continue;
            }

            auto _buff = std::make_shared<buff>(std::static_pointer_cast<medicine>((*it))->buff_id, shared_from_this(), shared_from_this());
            _buff_list.push_back(_buff);
            _buff->init_effect();

            (*it)->num--;
            if ((*it)->num <= 0) {
                _role_bag_handle->bag.erase(it);
            }

            break;
        }
    }

    void add_hp(int32_t _add_hp_num) {
        _role_battle_handle->hp += _add_hp_num;
        if (_role_battle_handle->hp > _role_battle_handle->total_hp) {
            _role_battle_handle->hp = _role_battle_handle->total_hp;
        }
        _call_mng_handle->battle_client_caller->get_multicast(_role_scene_handle->get_role_field())->role_hp_change(id, _role_battle_handle->hp);
    }

    bool check_camp(std::shared_ptr<role> other) {
        return _team_handle.lock() == other->_team_handle.lock();
    }

    void tick_buff() {
        for (auto it = _buff_list.begin(); it != _buff_list.end(); ) {
            if ((*it)->update()) {
                it++;
            }
            else {
                (*it)->clear();
                it = _buff_list.erase(it);
            }
        }
        for (auto _buff : _buff_list) {
            _buff->init_effect();
        }
    }

    void check_hurt_break_buff() {
        for (auto it = _buff_list.begin(); it != _buff_list.end(); ) {
            if ((*it)->_attack_break) {
                it = _buff_list.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    bool check_sync() {
        return !is_robot && load_scene_done;
    }

};

}

#endif //_role_h