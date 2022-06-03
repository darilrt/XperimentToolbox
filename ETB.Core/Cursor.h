#pragma once

#include "etbdefs.h"
#include <SDL.h>

namespace ETB {

	class Cursor {
	public:

		static inline void Grab(bool toggle) { SDL_SetRelativeMouseMode((SDL_bool)toggle); }
		static inline void Show(bool toggle) { SDL_ShowCursor((SDL_bool)toggle); }

	};

}