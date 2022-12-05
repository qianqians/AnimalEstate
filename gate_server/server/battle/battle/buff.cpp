/*
 * buff.cpp
 *
 *  Created on: 2021-6-7
 *      Author: qianqians
 */
#include "buff.h"
#include "role.h"
#include "../singleton.h"
#include "../json_config/json_config_mng.h"

namespace battle {

/*
   0 无效果
   1 加血
   2 扣血
   3 改变速度
 */
enum EM_BUFF_EFFECT {
	EM_TREATMENT = 1,
	EM_HURT = 2,
	EM_SPEED = 3,
	EM_INVINCIBLE = 4,
	EM_IGNORE_ATTACK = 5,
};
	
buff::buff(int32_t buff_id, std::shared_ptr<role> self, std::shared_ptr<role> caster) {
	auto _config = json_config::_json_config_mng->json_configs["buff"]->get_value_dict(std::to_string(buff_id));
	_end_time = _config->get_value_int("time") + _singleton_handle->_hub_handle->_timerservice->Tick;
	_init_effect = (int32_t)_config->get_value_int("init_effect");
	_init_effect_num = (int32_t)_config->get_value_int("init_effect_num");
	_continued_effect = (int32_t)_config->get_value_int("continued_effect");
	_continued_effect_num = (int32_t)_config->get_value_int("continued_effect_num");
	_end_effect = (int32_t)_config->get_value_int("end_effect");
	_end_effect_num = (int32_t)_config->get_value_int("end_effect_num");
	_attack_break = _config->get_value_bool("attack_break");

	_self = self;
	_caster = caster;
}

void buff::init_effect() {
	auto _self_ptr = _self.lock();
	if (!_self_ptr) {
		return;
	}

	if (_init_effect == EM_TREATMENT) {
		_self_ptr->add_hp(_init_effect_num);
	}
	else if (_init_effect == EM_HURT) {
		_self_ptr->_role_battle_handle->behit(_init_effect_num, _caster.lock());
	}
	else if (_init_effect == EM_SPEED) {
		_self_ptr->_role_scene_handle->move_speed_rate = _init_effect_num;
	}
	else if (_init_effect == EM_INVINCIBLE) {
		_self_ptr->_role_battle_handle->be_invincible = true;
	}
	else if (_init_effect == EM_IGNORE_ATTACK) {
		_self_ptr->_role_battle_handle->be_ignore_attack = true;
	}
}

bool buff::update() {
	if (_end_time > (uint64_t)_singleton_handle->_hub_handle->_timerservice->Tick) {
		auto _self_ptr = _self.lock();
		if (!_self_ptr) {
			return false;
		}

		if (_continued_effect == EM_TREATMENT) {
			_self_ptr->add_hp(_continued_effect_num);
		}
		else if (_continued_effect == EM_HURT) {
			_self_ptr->_role_battle_handle->behit(_continued_effect_num, _caster.lock());
		}
		else if (_continued_effect == EM_SPEED) {
		}
		else if (_continued_effect == EM_INVINCIBLE) {
		}
		else if (_continued_effect == EM_IGNORE_ATTACK) {
		}
	}
	else {
		end_effect();
		return false;
	}

	return true;
}

void buff::end_effect() {
	auto _self_ptr = _self.lock();
	if (!_self_ptr) {
		return;
	}

	if (_end_effect == EM_TREATMENT) {
		_self_ptr->add_hp(_end_effect_num);
	}
	else if (_end_effect == EM_HURT) {
		_self_ptr->_role_battle_handle->behit(_end_effect_num, _caster.lock());
	}
	else if (_end_effect == EM_SPEED) {
	}
	else if (_end_effect == EM_INVINCIBLE) {
	}
	else if (_end_effect == EM_IGNORE_ATTACK) {
	}
}

void buff::clear() {
	auto _self_ptr = _self.lock();
	if (!_self_ptr) {
		return;
	}

	spdlog::trace("buff clear!");

	_self_ptr->_role_scene_handle->move_speed_rate = 100;
	_self_ptr->_role_battle_handle->be_invincible = false;
	_self_ptr->_role_battle_handle->be_ignore_attack = false;

	if (!sig_end_buff.empty()) {
		sig_end_buff.emit();
	}
}

} /* namespace battle */