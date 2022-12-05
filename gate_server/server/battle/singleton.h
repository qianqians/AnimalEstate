/*
 * qianqians
 * 2020-1-23
 * battle
 * singleton.h
 */
#ifndef _singleton_h
#define _singleton_h

#include <memory>

#include "role_mng.h"
#include "battle/battle_mng.h"

namespace battle {

class singleton {
public:
    std::shared_ptr<role_mng> _role_mng_handle;
    std::shared_ptr<battle_mng> _battle_mng_handle;
    std::shared_ptr<hub::hub_service> _hub_handle;

public:
    singleton(std::shared_ptr<hub::hub_service> _hub) {
        _role_mng_handle = std::make_shared<role_mng>();
        _battle_mng_handle = std::make_shared<battle_mng>();

        _hub_handle = _hub;
    }

};
extern std::shared_ptr<singleton> _singleton_handle;

}

#endif //_singleton_h