#pragma once

#include "etbdefs.h"

#include <chrono>
#include <SDL.h>

namespace ETB {

	class  Time {
	public:
		static DECLSPEC float deltaTime;
		static DECLSPEC float playTime;

		static DECLSPEC void Start();
		static DECLSPEC void Tick();

		static inline DECLSPEC uint32_t GetTicks() { return SDL_GetTicks(); }

	private:
		static std::chrono::time_point<std::chrono::high_resolution_clock> start;
	};

}
