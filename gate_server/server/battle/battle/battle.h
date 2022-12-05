/*
 * qianqians
 * 2020-1-22
 * battle
 * battle.h
 */
#ifndef _battle_h
#define _battle_h

#include <memory>
#include <string>
#include <unordered_map>
#include <random>

#include <absl/container/node_hash_map.h>

#include "map.h"

namespace battle {

class team;
class role;
class robot;
class battle : public std::enable_shared_from_this<battle> {
public:
    std::string source_match_hub_name;
    std::string room_id; 
    std::shared_ptr<map> _map_handle;
    std::vector<std::shared_ptr<team> > faild_teams;
    absl::node_hash_map<std::string, std::shared_ptr<team> > teams;
    absl::node_hash_map<std::string, std::weak_ptr<role> > wait_roles;
    absl::node_hash_map<std::string, std::weak_ptr<role> > roles;
    absl::node_hash_map<std::string, std::weak_ptr<robot> > robots;
    int32_t surplus_team_count = 0;
    int32_t refresh_item_round = 1;
    int32_t poison_round = 0;
    int32_t poison_left = 0;
    int32_t poison_right = 0;
    int32_t next_poison_round = 0;
    int32_t next_poison_left = 0;
    int32_t next_poison_right = 0;
    bool is_start = false;
    bool is_end = false;

    std::shared_ptr<service::timerservice::timerimpl> poison_timer;
    std::shared_ptr<service::timerservice::timerimpl> poison_hurt_timer;
    std::shared_ptr<service::timerservice::timerimpl> refresh_item_timer;
    std::shared_ptr<service::timerservice::timerimpl> ai_timer;
    std::shared_ptr<service::timerservice::timerimpl> tick_timer;
    std::shared_ptr<service::timerservice::timerimpl> buff_timer;

private:
    static int count;

public:
    battle();

    virtual ~battle();

    void Init(std::string _source_match_hub_name, std::vector<abelkhan::team> battle_team_list);

    void start(int64_t tick);

    void ai_work(int64_t tick);

    void end_battle();

    void register_poison();

    void poison_update(int64_t tick);

    void poison_hurt(int64_t tick);

	void register_refresh_item();

	void refresh_item(int64_t tick);

    std::shared_ptr<item> drop_item(int32_t drop_lv, int32_t pos_x, int32_t pos_y);

    void role_into_battle(std::string id);

    void del_check_team_rank(std::string team_id);

    bool check_battle_end();

    std::vector<abelkhan::role_info> battle_field_info();

    std::vector<std::string> battle_field_uudis();

    void tick_buff(int64_t tick);

    void tick(int64_t tick);

};

std::vector<std::string> split(std::string in, std::string token);

}

#endif //_battle_h