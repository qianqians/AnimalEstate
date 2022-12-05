#include "mcallbattle.h"

namespace abelkhan
{

/*this caller code is codegen by abelkhan codegen for cpp*/
std::shared_ptr<match_battle_rsp_cb> match_battle_caller::rsp_cb_match_battle_handle = nullptr;
match_battle_create_room_cb::match_battle_create_room_cb(uint64_t _cb_uuid, std::shared_ptr<match_battle_rsp_cb> _module_rsp_cb) {
    cb_uuid = _cb_uuid;
    module_rsp_cb = _module_rsp_cb;
}

std::shared_ptr<match_battle_create_room_cb> match_battle_create_room_cb::callBack(std::function<void(std::string room_id, std::string host, int32_t port, bool is_busy)> cb, std::function<void(int32_t err)> err) {
    sig_create_room_cb.connect(cb);
    sig_create_room_err.connect(err);
    return shared_from_this();
}

void match_battle_create_room_cb::timeout(uint64_t tick, std::function<void()> timeout_cb) {
    auto _module_rsp_cb = module_rsp_cb;
    auto _cb_uuid = cb_uuid;
    TinyTimer::add_timer(tick, [_module_rsp_cb, _cb_uuid](){
        _module_rsp_cb->create_room_timeout(_cb_uuid);
    });
    sig_create_room_timeout.connect(timeout_cb);
}


}
