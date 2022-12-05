/*
 * qianqians
 * 2020-1-22
 * battle
 * battle.cpp
 */
#include <crossguid/guid.hpp>

#include "battle.h"
#include "team.h"
#include "robot.h"
#include "role_bag.h"
#include "constant.h"
#include "random.h"
#include "../singleton.h"
#include "../json_config/json_config_mng.h"

namespace battle {

int battle::count = 0;
int team::count = 0;

std::vector<std::string> split(std::string in, std::string token) {
	std::vector<std::string> vstr;

	do {
		if (in == "") {
			break;
		}

		while (true) {
			auto index = in.find(token);

			if (index == std::string::npos) {
				vstr.push_back(in);
				break;
			}

			vstr.push_back(in.substr(0, index));
			in = in.substr(index + token.size());
		}

	} while (false);

	return vstr;
}

battle::battle() {
	++count;
}

battle::~battle() {
	spdlog::trace("battle destruction count:{0}", --count);
}

void battle::Init(std::string _source_match_hub_name, std::vector<abelkhan::team> battle_team_list) {
    spdlog::trace("Init battle begin!");

	source_match_hub_name = _source_match_hub_name;
	room_id = xg::newGuid().str();
	_map_handle = std::make_shared<map>();
	int32_t poison_left = 0;
	int32_t poison_right = _map_handle->_map_width;

	surplus_team_count = (int32_t)battle_team_list.size();
	int _team_role_num = 0;
    for (auto team_info : battle_team_list) {
		auto _team = std::make_shared<team>();
        _team->Init(team_info, shared_from_this());
        teams[_team->team_id] = _team;

		_team_role_num = (int)_team->members.size();
        for (auto member : _team->members) {
            wait_roles.insert(member);
        }
    }

	int32_t max_team_num = (int32_t)(constant::max_battle_role_num / _team_role_num);
	for (auto i = surplus_team_count; i < max_team_num; i++) {
		auto _team = std::make_shared<team>();
		_team->Init(_team_role_num, shared_from_this());
		teams[_team->team_id] = _team;

		for (auto member : _team->members) {
			auto _mem_ptr = member.second;
			if (!_mem_ptr) {
				continue;
			}

			roles[_mem_ptr->id] = member.second;
			_mem_ptr->_role_scene_handle->timetmp = _singleton_handle->_hub_handle->_timerservice->Tick;

			robots.insert(std::make_pair(member.first, std::static_pointer_cast<robot>(_mem_ptr)));
		}
	}

	_singleton_handle->_hub_handle->_timerservice->addticktimer(5000, std::bind(&battle::start, this, std::placeholders::_1));
	tick(_singleton_handle->_hub_handle->_timerservice->Tick);
	ai_work(_singleton_handle->_hub_handle->_timerservice->Tick);

    spdlog::trace("Init battle begin!");
}

void battle::start(int64_t _tick) {
	is_start = true;

	for (auto _role : roles) {
		auto _role_ptr = _role.second.lock();
		if (!_role_ptr) {
			continue;
		}

		if (!_role_ptr->is_robot) {
			_call_mng_handle->battle_client_caller->get_client(_role_ptr->uuid)->battle_start();
		}
	}

	auto _battle_handle = shared_from_this();
	poison_timer = _singleton_handle->_hub_handle->_timerservice->addticktimer(10000, [_battle_handle](int64_t _tick) {
		_battle_handle->poison_update(_tick);
	});
	refresh_item(_singleton_handle->_hub_handle->_timerservice->Tick);
	tick_buff(_singleton_handle->_hub_handle->_timerservice->Tick);
}

void battle::ai_work(int64_t tick) {
	spdlog::trace("ai_work begin!");

	if (is_end) {
		return;
	}

	for (auto robot : robots) {
		auto _robot_ptr = robot.second.lock();
		if (!_robot_ptr) {
			continue;
		}
		_robot_ptr->ai_work();
	}

	auto _battle_handle = shared_from_this();
	ai_timer = _singleton_handle->_hub_handle->_timerservice->addticktimer(800, [_battle_handle](int64_t _tick) {
		_battle_handle->ai_work(_tick);
	});

	spdlog::trace("ai_work end!");
}

void battle::end_battle(){
	spdlog::trace("end_battle begin!");

    is_end = true;

	if (poison_timer != nullptr) {
		poison_timer->is_del = true;
		poison_timer = nullptr;
	}
	if (poison_hurt_timer != nullptr) {
		poison_hurt_timer->is_del = true;
		poison_hurt_timer = nullptr;
	}
	if (refresh_item_timer != nullptr) {
		refresh_item_timer->is_del = true;
		refresh_item_timer = nullptr;
	}
	if (ai_timer != nullptr) {
		ai_timer->is_del = true;
		ai_timer = nullptr;
	}
	if (tick_timer != nullptr) {
		tick_timer->is_del = true;
		tick_timer = nullptr;
	}
	if (buff_timer != nullptr) {
		buff_timer->is_del = true;
		buff_timer = nullptr;
	}

	for (auto _role : wait_roles) {
		auto _role_ptr = _role.second.lock();
		if (!_role_ptr) {
			continue;
		}

		abelkhan::role_battle_end_info end_info;
		end_info.battle_hub_name = _singleton_handle->_hub_handle->name_info.name;
		end_info.room_id = room_id;
		end_info.score = _role_ptr->_role_battle_handle->score + _role_ptr->_kill_list.size();
		_call_mng_handle->battle_lobby_caller->get_hub(_role_ptr->lobby)->end_battle(_role_ptr->id, end_info);
		_singleton_handle->_role_mng_handle->delete_role(_role_ptr);
	}

	for (auto _robot : robots) {
		auto _robot_ptr = _robot.second.lock();
		if (!_robot_ptr) {
			continue;
		}
		_singleton_handle->_role_mng_handle->delete_role(std::static_pointer_cast<role>(_robot_ptr));
	}

	for (auto _team : teams) {
		abelkhan::team team_info;
		team_info.id = _team.second->team_id;
		for (auto member : _team.second->members) {
			if ((member.second->last_active_timetmp + 10000) < _singleton_handle->_hub_handle->_timerservice->Tick) {
				abelkhan::team_member _team_member;
				_team_member.account = member.second->account;
				_team_member.session_uuid = member.second->uuid;
				_team_member.lobby = member.second->lobby;
				_team_member.name = member.second->name;
				_team_member.id = member.second->id;
				_team_member.is_ready = false;
				_team_member._body_info = member.second->_role_body_handle->cs_info();
				_team_member._battle_base_info.title = member.second->_role_battle_handle->title;
				_team_member._battle_base_info.score = member.second->_role_battle_handle->score;
				team_info.members.push_back(_team_member);
			}
		}

		if (!team_info.members.empty()) {
			_call_mng_handle->battle_match_caller->get_hub(source_match_hub_name)->back_match(team_info)->callBack([](std::string match_hub_name, abelkhan::match_team team_info) {
				std::vector<std::string> team_member_uuid;
				for (auto back_match_member : team_info.members) {
					team_member_uuid.push_back(back_match_member.session_uuid);
				}
				_call_mng_handle->battle_client_caller->get_multicast(team_member_uuid)->back_match(match_hub_name, team_info);

			}, [](int32_t err) {
				spdlog::error("end_battle back_match err:{0}!", err);
			})->timeout(5000, []() {
				spdlog::error("end_battle back_match timeout!");
			});
		}
	}

    _singleton_handle->_battle_mng_handle->end_battle(room_id);

	spdlog::trace("end_battle end!");
}

void battle::register_poison() {
	if (json_config::_json_config_mng->json_configs["poison"]->has_key(std::to_string(next_poison_round))) {
		auto poison_config = json_config::_json_config_mng->json_configs["poison"]->get_value_dict(std::to_string(next_poison_round));
		auto tick_time = poison_config->get_value_int("time");
		auto _battle_handle = shared_from_this();
		poison_timer = _singleton_handle->_hub_handle->_timerservice->addticktimer(tick_time, [_battle_handle](int64_t _tick) {
			_battle_handle->poison_update(_tick);
		});
	}
}

void battle::poison_update(int64_t tick) {
	spdlog::trace("poison_update begin!");

	if (!is_start || is_end) {
		spdlog::trace("battle::poison_hurt battle is not start or end!");
		return;
	}

	poison_round = next_poison_round;
	if (!json_config::_json_config_mng->json_configs["poison"]->has_key(std::to_string(poison_round))) {
		poison_left = 0;
		poison_right = _map_handle->_map_width;
	}	
	else {
		poison_left = next_poison_left;
		poison_right = next_poison_right;

		if (poison_round == 1)
		{
			auto poison_config = json_config::_json_config_mng->json_configs["poison"]->get_value_dict(std::to_string(poison_round));
			auto tick = poison_config->get_value_int("tick");
			auto _battle_handle = shared_from_this();
			poison_hurt_timer = _singleton_handle->_hub_handle->_timerservice->addticktimer(tick, [_battle_handle](int64_t _tick) {
				_battle_handle->poison_hurt(_tick);
			});
		}
	}

	auto _tmp_poison_round = next_poison_round + 1;
	if (json_config::_json_config_mng->json_configs["poison"]->has_key(std::to_string(_tmp_poison_round))) {
		next_poison_round = _tmp_poison_round;

		auto poison_config = json_config::_json_config_mng->json_configs["poison"]->get_value_dict(std::to_string(next_poison_round));
		auto diam = poison_config->get_value_int("diam");
		auto left_max = poison_right - diam;

		auto left = utils::random((int32_t)left_max);

		next_poison_left += left;
		next_poison_right = (int32_t)(next_poison_left + diam);
		next_poison_right = next_poison_right > _map_handle->_map_width ? _map_handle->_map_width : next_poison_right;

		_call_mng_handle->battle_client_caller->get_multicast(battle_field_uudis())->refresh_poison(poison_left, poison_right, next_poison_left, next_poison_right);

		register_poison();
	}

	spdlog::trace("poison_update end!");
}

void battle::poison_hurt(int64_t _tick) {
	spdlog::trace("battle::poison_hurt begin!");

	if (!is_start || is_end) {
		spdlog::trace("battle::poison_hurt battle is not start or end!");
		return;
	}

	if (json_config::_json_config_mng->json_configs["poison"]->has_key(std::to_string(poison_round))) {
		auto poison_config = json_config::_json_config_mng->json_configs["poison"]->get_value_dict(std::to_string(poison_round));
		auto hurt = (int32_t)poison_config->get_value_int("hurt");
		auto tick = poison_config->get_value_int("tick");

		for (auto it : roles) {
			auto it_role_ptr = it.second.lock();
			if (!it_role_ptr) {
				continue;
			}

			auto pos_x = it_role_ptr->_role_scene_handle->get_scene_x();
			if (pos_x < poison_left || pos_x > poison_right) {
				it_role_ptr->_role_battle_handle->hurt(hurt, nullptr);
			}
		}

		if (!check_battle_end()) {
			if (!is_end) {
				auto _battle_handle = shared_from_this();
				poison_hurt_timer = _singleton_handle->_hub_handle->_timerservice->addticktimer(tick, [_battle_handle](int64_t _tick) {
					_battle_handle->poison_hurt(_tick);
				});
			}
		}
	}

	spdlog::trace("battle::poison_hurt end!");
}

void battle::register_refresh_item() {
	if (json_config::_json_config_mng->json_configs["drop_time"]->has_key(std::to_string(refresh_item_round))) {
		auto refresh_item_config = json_config::_json_config_mng->json_configs["drop_time"]->get_value_dict(std::to_string(refresh_item_round));
		auto tick_time = refresh_item_config->get_value_int("time");
		auto _battle_handle = shared_from_this();
		refresh_item_timer = _singleton_handle->_hub_handle->_timerservice->addticktimer(tick_time, [_battle_handle](int64_t _tick) {
			_battle_handle->refresh_item(_tick);
		});
	}
}

void battle::refresh_item(int64_t tick) {
	spdlog::trace("refresh_item begin!");

	if (!is_start || is_end) {
		spdlog::trace("battle::poison_hurt battle is not start or end!");
		return;
	}

	if (json_config::_json_config_mng->json_configs["drop_time"]->has_key(std::to_string(refresh_item_round))) {
		auto refresh_item_config = json_config::_json_config_mng->json_configs["drop_time"]->get_value_dict(std::to_string(refresh_item_round));
		auto drop_lv = (int32_t)refresh_item_config->get_value_int("lv");
		auto drop_num = refresh_item_config->get_value_int("drop_num");
		
		std::vector<std::shared_ptr<item> > drop_item_list;
		for (auto i = 0; i < drop_num; i++) {
			auto x = utils::random(_map_handle->_map_width);
			drop_item_list.push_back(drop_item(drop_lv, x, 10));
		}

		std::vector<abelkhan::drop_item_info> _drop_item_list;
		for (auto _drop_item : drop_item_list) {
			abelkhan::drop_item_info _drop_item_info;
			_drop_item_info.uuid = _drop_item->uuid;
			_drop_item_info.desc_id = _drop_item->desc_id;
			_drop_item_info.is_in_house = _drop_item->is_in_house;
			_drop_item_info.x = _drop_item->x;
			_drop_item_info.y = _drop_item->y;
			_drop_item_list.push_back(_drop_item_info);
		}
		std::vector<std::string> role_uuids;
		for (auto _role : wait_roles) {
			auto _role_ptr = _role.second.lock();
			if (!_role_ptr) {
				continue;
			}
			if (!_role_ptr->check_sync()) {
				continue;
			}
			role_uuids.push_back(_role_ptr->uuid);
		}
		_call_mng_handle->battle_client_caller->get_multicast(role_uuids)->drop_item_list(_drop_item_list);

		refresh_item_round++;
		register_refresh_item();
	}

	spdlog::trace("refresh_item end!");
}

std::shared_ptr<item> battle::drop_item(int32_t drop_lv, int32_t pos_x, int32_t pos_y) {
	std::vector<std::shared_ptr<config::config> > drop_box_list;
	json_config::_json_config_mng->json_configs["drop_box"]->for_each_value([&drop_box_list, drop_lv, pos_x, pos_y, this](std::string k, std::shared_ptr<config::config> v) {
		auto lv = v->get_value_int("lv");
		if (lv == drop_lv) {
			drop_box_list.push_back(v);
		}
	});

	auto index = utils::random((int32_t)drop_box_list.size());
	auto _drop_box = drop_box_list[index];

	auto _item_list = _drop_box->get_value_string("item_list");
	bool is_in_house = _drop_box->get_value_bool("in_house");

	auto _item_weight_list = split(_item_list, "|");
	struct item_num_weight {
		int32_t item_id;
		int32_t num;
		int32_t weight;
	};
	std::vector<item_num_weight> item_num_weight_list;
	int32_t total_weight = 0;
	for (auto _item_num_weight : _item_weight_list) {
		auto _item_num_weight_list = split(_item_num_weight, "_");
		item_num_weight __item_num_weight;
		__item_num_weight.item_id = atoi(_item_num_weight_list[0].c_str());
		__item_num_weight.num = atoi(_item_num_weight_list[1].c_str());
		__item_num_weight.weight = atoi(_item_num_weight_list[2].c_str());
		item_num_weight_list.push_back(__item_num_weight);

		total_weight += __item_num_weight.weight;
	}

	auto _weight = utils::random(total_weight);
	int32_t sum_weight = 0;
	for (auto it = item_num_weight_list.begin(); it != item_num_weight_list.end(); it++) {
		sum_weight += it->weight;
		if (_weight < sum_weight) {
			auto _sub_map = _map_handle->get_sub_map(pos_x);
			auto _drop_item = create_item(it->item_id, it->num);
			auto _config = json_config::_json_config_mng->json_configs["item"]->get_value_dict(std::to_string(_drop_item->desc_id));
			
			auto x_box = (int32_t)(pos_x / 16);
			auto y_box = (int32_t)(pos_y / 16);
			auto house_box = _map_handle->get_house_box(x_box, y_box);
			if (house_box->map_elem->_property == em_map_element_property::em_map_empty) {
				is_in_house = false;
			}

			_map_handle->check_and_init(is_in_house, pos_x, pos_y);
			
			_drop_item->x = pos_x;
			_drop_item->y = pos_y;

			x_box = (int32_t)(pos_x / 16);
    		y_box = (int32_t)(pos_y / 16);
			house_box = _map_handle->get_house_box(x_box, y_box);
			if (is_in_house && house_box->map_elem->_property != em_map_element_property::em_map_empty) {
				_drop_item->is_in_house = true;
			}

			_sub_map->item_box_list.push_back(_drop_item);
			return _drop_item;
		}
	}

	return nullptr;
}	

void battle::role_into_battle(std::string id){
    auto _role = wait_roles[id].lock();
    if (!_role) {
        spdlog::error("role id:{0} not in wait list", id);
        return;
    }
	//wait_roles.erase(id);

    roles[_role->id] = _role;
    _role->_role_scene_handle->timetmp = _singleton_handle->_hub_handle->_timerservice->Tick;
}

void battle::del_check_team_rank(std::string team_id) {
	if (teams.find(team_id) != teams.end()) {
		auto rank = (int32_t)teams.size();
		teams[team_id]->rank = rank;
		faild_teams.push_back(teams[team_id]);
		teams.erase(team_id);
	}
}

bool battle::check_battle_end() {
	if (teams.size() == 1) {
		auto _team = teams.begin()->second;
		_team->rank = 1;
		if (!_team->is_robot_team) {
			_team->balance();
		}
		end_battle();
		return true;
	}
	else {
		int role_team = 0;
		std::shared_ptr<team> _live_role_team = nullptr;
		for (auto i : teams) {
			if (!i.second->is_robot_team) {
				_live_role_team = i.second;
				role_team++;
			}
		}
		if (role_team <= 0) {
			end_battle();
			return true;
		}
	}
	return false;
}

std::vector<abelkhan::role_info> battle::battle_field_info() {
	std::vector<abelkhan::role_info> field;
    for (auto it : roles) {
		auto it_role_ptr = it.second.lock();
		if (!it_role_ptr) {
			continue;
		}
        field.push_back(it_role_ptr->cs_info());
    }
    return field;
}

std::vector<std::string> battle::battle_field_uudis() {
    std::vector<std::string> field_uudis;
    for (auto it : roles) {
		auto it_role_ptr = it.second.lock();
		if (!it_role_ptr) {
			continue;
		}

		if (!it_role_ptr->check_sync()) {
			continue;
		}

        field_uudis.push_back(it_role_ptr->uuid);
    }
    return field_uudis;
}

void battle::tick_buff(int64_t tick) {
	spdlog::trace("tick_buff begin!");
	
	if (is_end) {
		return;
	}

	for (auto it : roles) {
		auto it_role_ptr = it.second.lock();
		if (!it_role_ptr) {
			continue;
		}

		if (it_role_ptr->is_live) {
			it_role_ptr->tick_buff();
		}
	}

	if (!check_battle_end()) {
		auto _battle_handle = shared_from_this();
		buff_timer = _singleton_handle->_hub_handle->_timerservice->addticktimer(100, [_battle_handle](int64_t _tick) {
			_battle_handle->tick_buff(_tick);
		});
	}

	spdlog::trace("tick_buff end!");
}

void battle::tick(int64_t tick) {
	spdlog::trace("tick begin!");

    if (is_end) {
        return;
    }

    for (auto it : roles) {
		auto it_role_ptr = it.second.lock();
		if (!it_role_ptr) {
			continue;
		}

        if (it_role_ptr->is_live) {
			it_role_ptr->_role_scene_handle->check_and_move();
        }
		it_role_ptr->_role_battle_handle->bullet_tick();
		if (it_role_ptr->is_robot) {
			std::static_pointer_cast<robot>(it_role_ptr)->check_shoot();
		}
    }

	if (!check_battle_end()) {
		auto _battle_handle = shared_from_this();
		tick_timer = _singleton_handle->_hub_handle->_timerservice->addticktimer(100, [_battle_handle](int64_t _tick) {
			_battle_handle->tick(_tick);
		});
	}

	spdlog::trace("tick end!");
}

}