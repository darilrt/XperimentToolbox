#pragma once

#include "etbdefs.h"
#include "GUI.h"
#include "Window.h"

#include <string>
#include <SDL.h>

namespace ETB {
	namespace Core {

		enum class VSyncMode {
			Adaptative = -1,
			Off = 0,
			On = 1,
		};

		class DECLSPEC Window {
			friend class Application;
		public:
			Window(const std::string& title, int32_t width, int32_t height);
			~Window();

			void Swap();
			void SetResizable(bool resizable);
			void GuiNewFrame();
			void SetVSync(VSyncMode mode);

		private:
			SDL_Window* sdlWindow;
			SDL_GLContext sdlGLContext;
		};
	}
}