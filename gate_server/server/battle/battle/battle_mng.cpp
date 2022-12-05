/*
 * qianqians
 * 2020-1-25
 * battle
 * battle_mng.cpp
 */
#include <memory>
#include "battle_mng.h"
#include "battle.h"

namespace battle {

std::shared_ptr<battle> battle_mng::create_battle(std::string source_match_hub_name, std::vector<abelkhan::team> battle_team_list) {
    auto _battle = std::make_shared<battle>();
    _battle->Init(source_match_hub_name, battle_team_list);
    battles[_battle->room_id] = _battle;
    return _battle;
}

void battle_mng::end_battle(std::string room_id) {
    battles.erase(room_id);
}

bool battle_mng::check_is_busy(){
    return battles.size() >= 10;
}

}