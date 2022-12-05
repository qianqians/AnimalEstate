/*
 * qianqians
 * 2020-1-26
 * battle
 * json_config_mng.h
 */
#ifndef _json_config_mng_h
#define _json_config_mng_h

#include <memory>
#include <string>
#include <unordered_map>

#include <absl/container/node_hash_map.h>

#include <hub.h>

#include <config.h>

namespace json_config {

class json_config_mng {
public:
    absl::node_hash_map<std::string, std::shared_ptr<config::config> > json_configs;

public:
    json_config_mng(std::vector<std::string> load_modules);

};
extern std::shared_ptr<json_config_mng> _json_config_mng;

}

#endif //_json_config_mng_h