/*
 * skill.h
 *
 *  Created on: 2021-6-20
 *      Author: qianqians
 */
#ifndef _skill_h
#define _skill_h

#include <vector>
#include <cstdint>
#include <memory>
#include <string>

namespace battle{

class role;
class skill {
public:
	skill(std::string skill_name, std::shared_ptr<role> self);

	void set_direction(int32_t _direction);
	void do_skill();

private:
	std::string _skill_name;
	int32_t _old_direction = 0;
	int32_t target;
	int32_t range;
	uint64_t desc_cd_time;
	uint64_t cd_time = 0;
	std::vector<int32_t> buff_list;
	std::weak_ptr<role> _self;

};

} /* namespace battle */

#endif //_skill_h