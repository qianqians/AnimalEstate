/*
 * qianqians
 * 2020-1-22
 * battle
 * role_battle.h
 */
#ifndef _role_battle_h
#define _role_battle_h

#include <memory>
#include <map>
#include <cstdint>
#include <string>
#include <cmath>

#include <hub.h>

#include <common.h>

#include <config.h>

#include "role_bag.h"

namespace battle {

enum shoot_mode_def {
    immediate_mode = 0,
    bullet_mode = 1,
};

class gun;
class role;
class map;
class box;
class bullet {
public:
    bool is_in_house;
    bool is_expose;
    bool is_gravity;
    bool is_aim_shoot;
    bool range_damage;
    int32_t target_x;
    int32_t target_y;
    int32_t x_speed;
    int32_t y_speed;
    int32_t pos_x;
    int32_t pos_y;
    int32_t gun_id = 0;
    int32_t id;
    int32_t collision;
    int32_t range;
    int32_t blast_radius;
    int32_t speed;
    int32_t attack;
    int32_t hit_terrain;
    int32_t step_distance;
    float shoot_angle;
    uint64_t last_time;
    std::string uuid;
    std::weak_ptr<role> self_role;

private:
    static int count;

public:
    bullet(bool _is_in_house, int32_t _pos_x, int32_t _pos_y, int32_t angle, std::shared_ptr<config::config> bullet_config, std::weak_ptr<role> _self_role);
    bullet(bool _is_in_house, int32_t _pos_x, int32_t _pos_y, int32_t _target_x, int32_t _target_y, std::shared_ptr<config::config> bullet_config, std::weak_ptr<role> _self_role);

    virtual ~bullet() {
        spdlog::trace("bullet destruction count:{0}", --count);
    }

    void make_up(int32_t _gun_id, int range_addition, int speed_addition, int attack_addition, int radius, bool range_damage);

    void send_fly_info(float _old_x, std::shared_ptr<map> _map);

    bool tick_and_check_end();

private:
    std::vector<std::string> get_filed_uuids(std::shared_ptr<map> _map, std::shared_ptr<box> _house_box, int32_t old_pos_x);
    bool check_end_in_house(std::shared_ptr<role> _role, std::shared_ptr<map> _map, int32_t old_pos_x, float step_time);
    bool check_end_out_house(std::shared_ptr<role> _role, std::shared_ptr<map> _map, int32_t old_pos_x, float step_time);

    bool tick_and_check_end_in_house();
    bool tick_and_check_end_out_house();

    bool blast(std::shared_ptr<role> _role, std::shared_ptr<map> _map, std::vector<std::string> filed_uuids, int32_t old_x, int32_t pos_x, int32_t pos_y, int32_t end_pos_x, int32_t end_pos_y);

};

class role_battle {
public:
    std::weak_ptr<role> self_role;

    bool is_in_house;

    int32_t title;
    int32_t score;
    
    int32_t base_hp;
    int32_t total_hp;
    int32_t hp;
    
    int32_t base_defense;
    int32_t defense;

    bool be_invincible = false;
    bool be_ignore_attack = false;
    
    std::shared_ptr<gun> _gun;
    int32_t _bullets_num;
    float angle;

    std::shared_ptr<gun> _rpg_gun;
    int32_t _rpg_bullets_num;

    int32_t _grenade_num;
    uint64_t _grenade_cd_time;

    int32_t _shoot_direction = 0;
    int64_t _shoot_direction_time = 0;

    std::map<EM_EQUIP_TYPE, std::shared_ptr<equip> > _equip;

    std::vector<std::shared_ptr<bullet> > bullets;

private:
    static int count;

public:
    role_battle(abelkhan::role_battle_base_info db_battle, std::shared_ptr<role> _role);
    role_battle(std::shared_ptr<role> _role);

    virtual ~role_battle() {
        spdlog::trace("role_battle destruction count:{0}", --count);
    }

    abelkhan::role_battle_info cs_info();

    void aim(float angle);

    std::shared_ptr<gun> change_gun(std::shared_ptr<gun> _gun);

    std::shared_ptr<equip> change_equip(std::shared_ptr<equip> _equip);

    void bullet_shoot(std::shared_ptr<config::config> gun_config, std::shared_ptr<config::config> bullet_config);

    void shoot();

    void rpg_shoot(int64_t angle);

    void rpg_aim_shoot(int64_t target_x, int64_t target_y);

    void grenade_shoot(float angle);

    void grenade_aim_shoot(int64_t target_x, int64_t target_y);

    void ntf_shoot_direction();

    int32_t behit(int32_t attack, std::shared_ptr<role> attacker);

    bool hurt(int32_t _hurt, std::shared_ptr<role> attacker);

    void bullet_tick();

private:
    void random_shoot_direction();

    void check_shoot_direction(float angle);

    void check_shoot_direction(int32_t pos_x, int32_t target_x);

};


}

#endif //_role_battle_h