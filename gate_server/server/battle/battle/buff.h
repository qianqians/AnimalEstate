/*
 * buff.h
 *
 *  Created on: 2021-6-7
 *      Author: qianqians
 */
#ifndef _buff_h
#define _buff_h

#include <cstdint>
#include <memory>

#include <concurrent/signals.h>

namespace battle{

class role;
class buff {
public:
	buff(int32_t buff_id, std::shared_ptr<role> self, std::shared_ptr<role> caster);

	void init_effect();
	bool update();
	void end_effect();
	void clear();

	concurrent::signals<void()> sig_end_buff;

public:
	bool _attack_break;

private:
	uint64_t _end_time;
	int32_t _init_effect;
	int32_t _init_effect_num;
	int32_t _continued_effect;
	int32_t _continued_effect_num;
	int32_t _end_effect;
	int32_t _end_effect_num;

	std::weak_ptr<role> _self;
	std::weak_ptr<role> _caster;

};

} /* namespace battle */

#endif //_buff_h