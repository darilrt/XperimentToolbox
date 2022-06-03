#pragma once

#include "etbdefs.h"
#include "GUI.h"
#include "Window.h"

#include <string>
#include <SDL.h>

namespace ETB {
	namespace Core {

		class DECLSPEC Window {
			friend class Application;
		public:
			Window(const std::string& title, int32_t width, int32_t height);
			~Window();

			void Swap();

			void SetResizable(bool resizable);

			void GuiNewFrame();

		private:
			SDL_Window* sdlWindow;
			SDL_GLContext sdlGLContext;
		};
	}
}