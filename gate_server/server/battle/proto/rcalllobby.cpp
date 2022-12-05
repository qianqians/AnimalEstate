#include "rcalllobby.h"

namespace abelkhan
{

/*this caller code is codegen by abelkhan codegen for cpp*/
std::shared_ptr<router_lobby_rsp_cb> router_lobby_caller::rsp_cb_router_lobby_handle = nullptr;
router_lobby_role_login_cb::router_lobby_role_login_cb(uint64_t _cb_uuid, std::shared_ptr<router_lobby_rsp_cb> _module_rsp_cb) {
    cb_uuid = _cb_uuid;
    module_rsp_cb = _module_rsp_cb;
}

std::shared_ptr<router_lobby_role_login_cb> router_lobby_role_login_cb::callBack(std::function<void(bool is_busy)> cb, std::function<void(int32_t err)> err) {
    sig_role_login_cb.connect(cb);
    sig_role_login_err.connect(err);
    return shared_from_this();
}

void router_lobby_role_login_cb::timeout(uint64_t tick, std::function<void()> timeout_cb) {
    auto _module_rsp_cb = module_rsp_cb;
    auto _cb_uuid = cb_uuid;
    TinyTimer::add_timer(tick, [_module_rsp_cb, _cb_uuid](){
        _module_rsp_cb->role_login_timeout(_cb_uuid);
    });
    sig_role_login_timeout.connect(timeout_cb);
}


}
