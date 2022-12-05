/*
 * buff.cpp
 *
 *  Created on: 2021-6-20
 *      Author: qianqians
 */
#include "skill.h"
#include "role.h"
#include "team.h"
#include "battle.h"
#include "../singleton.h"
#include "../json_config/json_config_mng.h"

namespace battle {

enum EMSkillTargetType {
	em_skill_target_self = 1,
	em_skill_target_friend = 2,
	em_skill_target_enemy = 3,
};

skill::skill(std::string skill_name, std::shared_ptr<role> self) {
	_skill_name = skill_name;
	_self = self;

	auto _skill_config = json_config::_json_config_mng->json_configs["skill"]->get_value_dict(_skill_name);
	target = (int32_t)(_skill_config->get_value_int("target"));
	range = (int32_t)(_skill_config->get_value_int("range"));
	desc_cd_time = (uint64_t)(_skill_config->get_value_int("cd"));
	auto _skill_buff = _skill_config->get_value_string("buff");
	auto _skill_buff_list = split(_skill_buff, "_");
	for (auto buff_str : _skill_buff_list) {
		buff_list.push_back(std::stoul(buff_str));
	}
}

void skill::set_direction(int32_t _direction) {
	spdlog::trace("set_direction _direction:{0}", _direction);
	_old_direction = _direction;
}

void skill::do_skill() {
	auto self = _self.lock();
	if (!self) {
		return;
	}

	if (cd_time > (uint64_t)_singleton_handle->_hub_handle->_timerservice->Tick) {
		return;
	}

	if (self->_role_skill_handle->skill_name != "") {
		return;
	}

	if (_skill_name == "twostepjump") {
		self->_role_scene_handle->is_twostepjump = true;
		cd_time = (uint64_t)(_singleton_handle->_hub_handle->_timerservice->Tick + desc_cd_time * 0.9);
		return;
	}

	std::shared_ptr<buff> _buff = nullptr;
	if (target == em_skill_target_self) {
		for (auto buff_id : buff_list) {
			_buff = std::make_shared<buff>(buff_id, self, self);
			self->_buff_list.push_back(_buff);
			_buff->init_effect();
		}

		if (_buff && _skill_name == "roll") {
			_old_direction = self->_role_scene_handle->direction;
			if (_old_direction == 0) {
				self->_role_scene_handle->force_set_direction(self->_role_battle_handle->_shoot_direction);
				self->_role_scene_handle->check_and_move();
			}
			_buff->sig_end_buff.connect([this, self]() {
				spdlog::trace("sig_end_buff _old_direction:{0}", _old_direction);
				self->_role_scene_handle->force_set_direction(_old_direction);
				self->_role_scene_handle->check_and_move();
			});
		}
	}
	else if (target == em_skill_target_friend) {
		auto _team = self->_team_handle.lock();
		for (auto f : _team->members) {
			auto dis = (int32_t)(abs((int)f.second->_role_scene_handle->get_scene_x() - (int)self->_role_scene_handle->get_scene_x()));
			if (dis > range){
				continue;
			}

			for (auto buff_id : buff_list) {
				_buff = std::make_shared<buff>(buff_id, f.second, self);
				f.second->_buff_list.push_back(_buff);
				_buff->init_effect();
			}
		}
	}
	else if (target == em_skill_target_enemy) {
		auto _map = self->_role_scene_handle->_map_handle.lock();
		if (!_map) {
			return;
		}

		auto _target = _map->get_field_roles(self->_role_scene_handle->get_scene_x());
		for (auto t : _target) {
			if (t->check_camp(self)) {
				continue;
			}

			auto dis = (int32_t)(abs((int)t->_role_scene_handle->get_scene_x() - (int)self->_role_scene_handle->get_scene_x()));
			if (dis > range) {
				continue;
			}

			for (auto buff_id : buff_list) {
				_buff = std::make_shared<buff>(buff_id, t, self);
				t->_buff_list.push_back(_buff);
				_buff->init_effect();
			}
		}
	}
	cd_time = (uint64_t)(_singleton_handle->_hub_handle->_timerservice->Tick + desc_cd_time * 0.9);
	if (_buff != nullptr) {
		_buff->sig_end_buff.connect([this, self]() {
			spdlog::trace("sig_end_buff clear skill status!");
			self->_role_skill_handle->clear_skill_status();
			self->_role_skill_handle->send_skill_info(self);
		});
	}

	self->_role_skill_handle->set_skill_status(_skill_name);
	self->_role_skill_handle->send_skill_info(self);
}

} /* namespace battle */