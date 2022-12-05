/*
 * qianqians
 * 2020-1-22
 * battle
 * team.h
 */
#ifndef _team_h
#define _team_h

#include <string>
#include <memory>
#include <unordered_map>

#include <absl/container/node_hash_map.h>

#include <hub.h>
#include <memory>

#include "battle.h"
#include "role.h"
#include "robot.h"

#include "../singleton.h"
#include "../call_mng.h"

namespace battle {

class team : public std::enable_shared_from_this<team> {
public:
    bool is_fall = false;
    bool is_robot_team = false;
    int32_t rank = 0;
    std::string team_id;
    std::weak_ptr<battle> _battle_handle;
    std::vector<std::string> uuids;
    absl::node_hash_map<std::string, std::shared_ptr<role> > members;

    static int count;

public:
    team() {
        ++count;
    }

    virtual ~team() {
        spdlog::trace("team destruction count:{0}", --count);
    }

    void Init(abelkhan::team team_info, std::shared_ptr<battle> _battle) {
        spdlog::trace("Init team begin!");

        team_id = team_info.id;
        _battle_handle = _battle;
        
        for (auto cs_role : team_info.members) {
            auto _role = std::make_shared<role>();
            _role->Init(_battle->_map_handle, cs_role);
            members[_role->id] = _role;
            _role->_team_handle = shared_from_this();
            _role->_battle_handle = _battle;
            _role->_role_scene_handle->_map_handle = _battle->_map_handle;
            _role->_role_scene_handle->check_and_init();

            _singleton_handle->_role_mng_handle->add_role(_role);

            uuids.push_back(_role->uuid);
        }

        spdlog::trace("Init team end!");
    }

    void Init(int team_role_num, std::shared_ptr<battle> _battle) {
        spdlog::trace("Init robot team begin!");

        team_id = xg::newGuid().str();
        _battle_handle = _battle;
        is_robot_team = true;

        for (auto i = 0; i < team_role_num; i++) {
            auto _robot = std::make_shared<robot>();
            _robot->Init(_battle->_map_handle);
            members[_robot->id] = std::static_pointer_cast<role>(_robot);
            _robot->_team_handle = shared_from_this();
            _robot->_battle_handle = _battle;
            _robot->_role_scene_handle->_map_handle = _battle->_map_handle;
            _robot->_role_scene_handle->check_and_init();

            _singleton_handle->_role_mng_handle->add_role(std::static_pointer_cast<role>(_robot));

            uuids.push_back(_robot->uuid);
        }

        spdlog::trace("Init robot team end!");
    }

    bool check_fall() {
        bool is_one_live = false;
        for (auto it : members) {
            if (it.second->is_live) {
                is_one_live = true;
                break;
            }
        }

        if (!is_one_live) {
            is_fall = true;

            auto _battle = _battle_handle.lock();
            if (_battle) {
                _battle->del_check_team_rank(team_id);
            }
            
            if (!is_robot_team) {
                balance();
            }
        }

        return is_fall;
    }

    void balance() {
        for (auto _it_role : members) {
            _call_mng_handle->battle_client_caller->get_client(_it_role.second->uuid)->balance(rank, _it_role.second->_kill_list.size());
        }
    }

};

}

#endif //_team_h