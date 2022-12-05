/*
 * role_skill.cpp
 *
 *  Created on: 2021-6-20
 *      Author: qianqians
 */
#include <memory>

#include "role_skill.h"
#include "role.h"
#include "skill.h"
#include "../singleton.h"
#include "../call_mng.h"

namespace battle {

role_skill::role_skill(std::shared_ptr<role> _role, std::vector<std::string> skill_list) {
	for (auto skill_name : skill_list) {
		auto _skill = std::make_shared<skill>(skill_name, _role);
		role_skill_list.insert(std::make_pair(skill_name, _skill));
	}
}

std::vector<std::string> role_skill::cs_info() {
	std::vector<std::string> _skill;
	for (auto skill : role_skill_list) {
		_skill.push_back(skill.first);
	}
	return _skill;
}

void role_skill::do_skill(std::string skill_name) {
	auto it = role_skill_list.find(skill_name);
	if (it == role_skill_list.end()) {
		return;
	}
	
	it->second->do_skill();
}

void role_skill::set_skill_status(std::string _skill_name) {
	skill_name = _skill_name;
	skill_time = _singleton_handle->_hub_handle->_timerservice->Tick;
}

void role_skill::clear_skill_status() {
	skill_name = "";
	skill_time = 0;
}

void role_skill::send_skill_info(std::shared_ptr<role> _role) {
	spdlog::trace("send_skill_info begin!");

	auto timetmp = _singleton_handle->_hub_handle->_timerservice->Tick - skill_time;
	auto filed_roles = _role->_role_scene_handle->get_role_field();
	_call_mng_handle->battle_client_caller->get_multicast(filed_roles)->role_skill_info(_role->id, skill_name, timetmp);

	for (auto uuid : filed_roles) {
		spdlog::trace("send_skill_info uuid:{0}", uuid);
	}
	spdlog::trace("send_skill_info end! role_uuid:{0}, skill_name:{1}, skill_time:{2}", _role->id, skill_name, timetmp);
}

void role_skill::check_and_send_skill_info_to_role(std::shared_ptr<role> _self, std::shared_ptr<role> _role) {
	if (skill_name != "") {
		_call_mng_handle->battle_client_caller->get_multicast({ _role->uuid})->role_skill_info(_self->uuid, skill_name,
			_singleton_handle->_hub_handle->_timerservice->Tick - skill_time);
	}
}

} /* namespace battle */