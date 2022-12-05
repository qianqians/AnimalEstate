/*
 * qianqians
 * 2020-1-22
 * battle
 * json_config_mng.cpp
 */

#include <io.h>
#include <fstream>

#include "json_config_mng.h"

namespace json_config {

std::shared_ptr<json_config_mng> _json_config_mng = nullptr;

json_config_mng::json_config_mng(std::vector<std::string> load_modules) {
    for (auto file_name : load_modules) {
        spdlog::trace(file_name);
        std::string file_path = "./excel_json/" + file_name + ".json";
        json_configs[file_name] = std::make_shared<config::config>(file_path);
        spdlog::trace("{0} end!", file_name);
    }
}

}