#include "lcallmatch.h"

namespace abelkhan
{

/*this caller code is codegen by abelkhan codegen for cpp*/
std::shared_ptr<lobby_match_rsp_cb> lobby_match_caller::rsp_cb_lobby_match_handle = nullptr;
lobby_match_create_team_cb::lobby_match_create_team_cb(uint64_t _cb_uuid, std::shared_ptr<lobby_match_rsp_cb> _module_rsp_cb) {
    cb_uuid = _cb_uuid;
    module_rsp_cb = _module_rsp_cb;
}

std::shared_ptr<lobby_match_create_team_cb> lobby_match_create_team_cb::callBack(std::function<void(match_team team_info)> cb, std::function<void(int32_t err)> err) {
    sig_create_team_cb.connect(cb);
    sig_create_team_err.connect(err);
    return shared_from_this();
}

void lobby_match_create_team_cb::timeout(uint64_t tick, std::function<void()> timeout_cb) {
    auto _module_rsp_cb = module_rsp_cb;
    auto _cb_uuid = cb_uuid;
    TinyTimer::add_timer(tick, [_module_rsp_cb, _cb_uuid](){
        _module_rsp_cb->create_team_timeout(_cb_uuid);
    });
    sig_create_team_timeout.connect(timeout_cb);
}

lobby_match_agree_join_team_cb::lobby_match_agree_join_team_cb(uint64_t _cb_uuid, std::shared_ptr<lobby_match_rsp_cb> _module_rsp_cb) {
    cb_uuid = _cb_uuid;
    module_rsp_cb = _module_rsp_cb;
}

std::shared_ptr<lobby_match_agree_join_team_cb> lobby_match_agree_join_team_cb::callBack(std::function<void(match_team team_info)> cb, std::function<void(int32_t err)> err) {
    sig_agree_join_team_cb.connect(cb);
    sig_agree_join_team_err.connect(err);
    return shared_from_this();
}

void lobby_match_agree_join_team_cb::timeout(uint64_t tick, std::function<void()> timeout_cb) {
    auto _module_rsp_cb = module_rsp_cb;
    auto _cb_uuid = cb_uuid;
    TinyTimer::add_timer(tick, [_module_rsp_cb, _cb_uuid](){
        _module_rsp_cb->agree_join_team_timeout(_cb_uuid);
    });
    sig_agree_join_team_timeout.connect(timeout_cb);
}

std::shared_ptr<match_lobby_rsp_cb> match_lobby_caller::rsp_cb_match_lobby_handle = nullptr;

}
