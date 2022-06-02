#pragma once

#include "etbdefs.h"
#include "Window.h"

#include <string>
#include <SDL.h>

namespace ETB {
	namespace Core {

		class DECLSPEC Window {
		public:
			Window(const std::string& title, int32_t width, int32_t height);
			~Window();

			void Swap();

			void SetResizable(bool resizable);

		private:
			SDL_Window* sdlWindow;
			SDL_GLContext sdlGLContext;
		};
	}
}