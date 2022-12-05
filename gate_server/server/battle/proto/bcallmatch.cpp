#include "bcallmatch.h"

namespace abelkhan
{

/*this caller code is codegen by abelkhan codegen for cpp*/
std::shared_ptr<battle_match_rsp_cb> battle_match_caller::rsp_cb_battle_match_handle = nullptr;
battle_match_back_match_cb::battle_match_back_match_cb(uint64_t _cb_uuid, std::shared_ptr<battle_match_rsp_cb> _module_rsp_cb) {
    cb_uuid = _cb_uuid;
    module_rsp_cb = _module_rsp_cb;
}

std::shared_ptr<battle_match_back_match_cb> battle_match_back_match_cb::callBack(std::function<void(std::string match_hub_name, match_team team_info)> cb, std::function<void(int32_t err)> err) {
    sig_back_match_cb.connect(cb);
    sig_back_match_err.connect(err);
    return shared_from_this();
}

void battle_match_back_match_cb::timeout(uint64_t tick, std::function<void()> timeout_cb) {
    auto _module_rsp_cb = module_rsp_cb;
    auto _cb_uuid = cb_uuid;
    TinyTimer::add_timer(tick, [_module_rsp_cb, _cb_uuid](){
        _module_rsp_cb->back_match_timeout(_cb_uuid);
    });
    sig_back_match_timeout.connect(timeout_cb);
}


}
