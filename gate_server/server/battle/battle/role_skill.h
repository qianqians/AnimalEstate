/*
 * role_skill.h
 *
 *  Created on: 2021-6-20
 *      Author: qianqians
 */
#ifndef _role_skill_h
#define _role_skill_h

#include <cstdint>
#include <vector>
#include <map>
#include <memory>
#include <string>

namespace battle{

class role;
class skill;
class role_skill {
public:
	role_skill(std::shared_ptr<role> _role, std::vector<std::string> skill_list);

	std::vector<std::string> cs_info();

	void do_skill(std::string skill_name);

	void set_skill_status(std::string skill_name);

	void clear_skill_status();

	void send_skill_info(std::shared_ptr<role> _role);

	void check_and_send_skill_info_to_role(std::shared_ptr<role> _self, std::shared_ptr<role> _role);

public:
	std::string skill_name = "";
	int64_t skill_time = 0;

public:
	std::map<std::string, std::shared_ptr<skill> > role_skill_list;

};

} /* namespace battle */

#endif //_role_skill_h