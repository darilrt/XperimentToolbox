#pragma once

#include "etbdefs.h"
#include "Window.h"

#include <SDL.h>
#include <glm/glm.hpp>

namespace xtb {

	class Cursor {
	public:
		
		static inline void Warp(glm::ivec2 p) { xtb::Core::Window::GetActive()->Warp(p); }
		static inline void Grab(bool toggle) { SDL_SetRelativeMouseMode(toggle ? SDL_TRUE : SDL_FALSE); }
		static inline void Show(bool toggle) { SDL_ShowCursor((SDL_bool)toggle); }

	};

}