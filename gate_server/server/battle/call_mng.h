/*
 * qianqians
 * 2020-1-23
 * battle
 * call_mng.h
 */
#ifndef _call_mng_h
#define _call_mng_h

#include <memory>

#include <bcallmatch.h>
#include <bcalllobby.h>
#include <battlecallc.h>
#include <error.h>

namespace battle {

class call_mng {
public:
    std::shared_ptr<abelkhan::battle_match_caller> battle_match_caller;
    std::shared_ptr<abelkhan::battle_lobby_caller> battle_lobby_caller;
    std::shared_ptr<abelkhan::battle_client_caller> battle_client_caller;
    std::shared_ptr<abelkhan::error_code_ntf_caller> error_code_caller;

public:
    call_mng(std::shared_ptr<hub::hub_service> _hub) {
        battle_match_caller = std::make_shared<abelkhan::battle_match_caller>(_hub);
        battle_lobby_caller = std::make_shared<abelkhan::battle_lobby_caller>(_hub);
        battle_client_caller = std::make_shared<abelkhan::battle_client_caller>(_hub);
        error_code_caller = std::make_shared<abelkhan::error_code_ntf_caller>(_hub);
    }
};
extern std::shared_ptr<call_mng> _call_mng_handle;

}

#endif // !_call_mng_h
