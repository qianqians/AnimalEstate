/*
 * qianqians
 * 2020-1-23
 * battle
 * role_mng.h
 */
#ifndef _role_mng_h
#define _role_mng_h

#include <memory>
#include <string>
#include <unordered_map>

#include <absl/container/node_hash_map.h>

#include "./call_mng.h"
#include "./battle/role.h"

namespace battle {

class role_mng {
public:
    absl::node_hash_map<std::string, std::shared_ptr<role> > roles_id;
    absl::node_hash_map<std::string, std::shared_ptr<role> > roles_uuid;

    void add_role(std::shared_ptr<role> _role) {
        auto it = roles_id.find(_role->id);
        if (it != roles_id.end()) {
            if (roles_uuid.find(it->second->uuid) != roles_uuid.end()) {
                roles_uuid.erase(it->second->uuid);
            }
            roles_id.erase(it);
        }
        roles_id[_role->id] = _role;
        roles_uuid[_role->uuid] = _role;
    }

    std::shared_ptr<role> get_role_by_id(std::string id) {
        if (roles_id.find(id) != roles_id.end()) {
            return roles_id[id];
        }
        return nullptr;
    }

    std::shared_ptr<role> get_role_by_uuid(std::string uuid) {
        if (roles_uuid.find(uuid) != roles_uuid.end()) {
            return roles_uuid[uuid];
        }
        return nullptr;
    }

    void refresh_uuid(std::string id, std::string uuid) {
        spdlog::trace("refresh_uuid begin");

        auto _role = roles_id[id];
        if (_role == nullptr) {
            return;
        }

        auto tmp_uuid = _role->uuid;
        _role->uuid = uuid;
        auto it = roles_uuid.find(tmp_uuid);
        if (it != roles_uuid.end()) {
            roles_uuid.erase(it);
            _call_mng_handle->battle_client_caller->get_client(tmp_uuid)->be_displacement();
        }
        spdlog::trace("refresh_uuid start uuid:{0}", uuid);
        roles_uuid[uuid] = _role;
    }

    void delete_role(std::shared_ptr<role> _role) {
        if (roles_uuid.find(_role->uuid) != roles_uuid.end()) {
            roles_uuid.erase(_role->uuid);
        }
        if (roles_id.find(_role->id) != roles_id.end()) {
            roles_id.erase(_role->id);
        }
    }
};

}

#endif //_role_mng_h