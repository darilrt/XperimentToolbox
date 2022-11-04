#pragma once

#include "etbdefs.h"
#include "GUI.h"
#include "Window.h"

#include <glm/glm.hpp>
#include <string>
#include <SDL.h>

namespace xtb {
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
			void Minimize();
			void Maximize();
			void SetResizable(bool resizable);
			void GuiNewFrame();
			void SetVSync(VSyncMode mode);
			void Warp(glm::ivec2 pos);

			glm::ivec2 GetSize();

			static inline void SetActive(Window* window) { Window::activeWindow = window; }
			static inline Window* GetActive() { return Window::activeWindow; }

		private:
			SDL_Window* sdlWindow;
			SDL_GLContext sdlGLContext;

			static Window* activeWindow;
		};
	}
}