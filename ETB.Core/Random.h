#pragma once

#include <random>

#include "etbdefs.h"

namespace xtb {

	class Random {
	public:
		static int DECLSPEC Range(int32_t min, int32_t max);

	private:
		static std::random_device dev;
		static std::mt19937 rng;
	};

	DECLSPEC std::string GetUUID();

}

