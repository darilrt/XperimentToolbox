#pragma once

#include <chrono>

#include "etbdefs.h"

namespace ETB {

	class  Time {
	public:
		static DECLSPEC float deltaTime;
		static DECLSPEC float playTime;

		static DECLSPEC void Start();
		static DECLSPEC void Tick();

	private:
		static std::chrono::time_point<std::chrono::high_resolution_clock> start;
	};

}
