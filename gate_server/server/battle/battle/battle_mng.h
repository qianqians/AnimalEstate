/*
 * qianqians
 * 2020-1-23
 * battle
 * battle_mng.h
 */
#ifndef _battle_mng_h
#define _battle_mng_h

#include <unordered_map>
#include <string>
#include <memory>

#include <absl/container/node_hash_map.h>

#include <hub.h>
#include <common.h>

namespace battle {

class battle;
class battle_mng {
public:
    absl::node_hash_map<std::string, std::shared_ptr<battle> > battles;

public:
    std::shared_ptr<battle> create_battle(std::string source_match_hub_name, std::vector<abelkhan::team> battle_team_list);

    void end_battle(std::string room_id);

    bool check_is_busy();

};

}

#endif //_battle_mng_h