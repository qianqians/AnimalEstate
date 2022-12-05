/*
 * qianqians
 * 2021-4-3
 * robot
 * robot.h
 */
#ifndef _robot_h
#define _robot_h

#include <memory>
#include <string>
#include <unordered_map>
#include <random>

#include "map.h"
#include "role.h"

namespace battle {

class robot : public role{
public:
    void Init(std::shared_ptr<map> _map);

    void ai_work();

    void check_shoot();

private:
    bool is_aim_right = true;
    bool is_in_battle = false;

};

}

#endif //_battle_h