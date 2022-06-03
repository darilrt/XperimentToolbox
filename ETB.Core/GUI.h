#pragma once

#include "etbdefs.h"
#include "imgui.h"

#include <SDL.h>

namespace ETB {
	namespace GUI {

		DECLSPEC void Init(SDL_Window* sdlWindow, SDL_GLContext sdlGLContext);

		DECLSPEC void Destroy();

		DECLSPEC void NewFrame(SDL_Window* sdlWindow);

		DECLSPEC void Draw();

		DECLSPEC void ProcesssEvent(SDL_Event* event);

		DECLSPEC void SetTheme();

		inline DECLSPEC bool UseKeyboard() { return ImGui::GetIO().WantCaptureKeyboard; }

		inline DECLSPEC bool UseMouse() { return ImGui::GetIO().WantCaptureMouse; }
		
	}
}
