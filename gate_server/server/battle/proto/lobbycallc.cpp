#include "lobbycallc.h"

namespace abelkhan
{

/*this caller code is codegen by abelkhan codegen for cpp*/
std::shared_ptr<lobby_client_rsp_cb> lobby_client_caller::rsp_cb_lobby_client_handle = nullptr;
std::shared_ptr<lobby_battle_client_rsp_cb> lobby_battle_client_caller::rsp_cb_lobby_battle_client_handle = nullptr;
std::shared_ptr<lobby_team_client_rsp_cb> lobby_team_client_caller::rsp_cb_lobby_team_client_handle = nullptr;
std::shared_ptr<lobby_friend_client_rsp_cb> lobby_friend_client_caller::rsp_cb_lobby_friend_client_handle = nullptr;
lobby_friend_client_invite_role_friend_cb::lobby_friend_client_invite_role_friend_cb(uint64_t _cb_uuid, std::shared_ptr<lobby_friend_client_rsp_cb> _module_rsp_cb) {
    cb_uuid = _cb_uuid;
    module_rsp_cb = _module_rsp_cb;
}

std::shared_ptr<lobby_friend_client_invite_role_friend_cb> lobby_friend_client_invite_role_friend_cb::callBack(std::function<void()> cb, std::function<void()> err) {
    sig_invite_role_friend_cb.connect(cb);
    sig_invite_role_friend_err.connect(err);
    return shared_from_this();
}

void lobby_friend_client_invite_role_friend_cb::timeout(uint64_t tick, std::function<void()> timeout_cb) {
    auto _module_rsp_cb = module_rsp_cb;
    auto _cb_uuid = cb_uuid;
    TinyTimer::add_timer(tick, [_module_rsp_cb, _cb_uuid](){
        _module_rsp_cb->invite_role_friend_timeout(_cb_uuid);
    });
    sig_invite_role_friend_timeout.connect(timeout_cb);
}

lobby_friend_client_agree_role_friend_cb::lobby_friend_client_agree_role_friend_cb(uint64_t _cb_uuid, std::shared_ptr<lobby_friend_client_rsp_cb> _module_rsp_cb) {
    cb_uuid = _cb_uuid;
    module_rsp_cb = _module_rsp_cb;
}

std::shared_ptr<lobby_friend_client_agree_role_friend_cb> lobby_friend_client_agree_role_friend_cb::callBack(std::function<void()> cb, std::function<void()> err) {
    sig_agree_role_friend_cb.connect(cb);
    sig_agree_role_friend_err.connect(err);
    return shared_from_this();
}

void lobby_friend_client_agree_role_friend_cb::timeout(uint64_t tick, std::function<void()> timeout_cb) {
    auto _module_rsp_cb = module_rsp_cb;
    auto _cb_uuid = cb_uuid;
    TinyTimer::add_timer(tick, [_module_rsp_cb, _cb_uuid](){
        _module_rsp_cb->agree_role_friend_timeout(_cb_uuid);
    });
    sig_agree_role_friend_timeout.connect(timeout_cb);
}


}
