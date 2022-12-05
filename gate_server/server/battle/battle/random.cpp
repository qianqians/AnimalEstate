/*
 * random.cpp
 *
 *  Created on: 2021-6-4
 *      Author: qianqians
 */
#include <random>
#include "random.h"
#include "../singleton.h"

namespace utils {

static std::default_random_engine e((int32_t)msec_time());

int32_t random(int32_t max) {
	return e() % max;
}


} /* namespace utils */