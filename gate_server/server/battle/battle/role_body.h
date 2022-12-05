/*
 * qianqians
 * 2020-1-22
 * battle
 * role_body.h
 */
#ifndef _role_body_h
#define _role_body_h

#include <cstdint>

#include <hub.h>
#include <common.h>

namespace battle {

class role_body {
public:
    int32_t head;
    int32_t body;
    int32_t foot;

private:
    static int count;

public:
    role_body(abelkhan::role_body_info db_body) {
        spdlog::trace("Init role_body begin!");
        head = (int32_t)db_body.head;
        body = (int32_t)db_body.body;
        foot = (int32_t)db_body.foot;
        ++count;
        spdlog::trace("Init role_body end!");
    }

    role_body() {
        spdlog::trace("Init robot role_body begin!");
        head = 1;
        body = 1;
        foot = 1;
        ++count;
        spdlog::trace("Init robot role_body end!");
    }

    virtual ~role_body() {
        spdlog::trace("role_body destruction count:{0}", --count);
    }

    abelkhan::role_body_info cs_info() {
        abelkhan::role_body_info info;
        info.head = head;
        info.body = body;
        info.foot = foot;
        return info;
    }


};


}

#endif //_role_body_h