#include "Graphics.h"
#include "Window.h"

ETB::Core::Window::Window(const std::string& title, int32_t w, int32_t h) {
	SDL_Init(SDL_INIT_EVERYTHING);

	sdlWindow = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		w, h, 
		SDL_WINDOW_OPENGL);

	 sdlGLContext = SDL_GL_CreateContext(sdlWindow);

	 Graphics::Init();
}

ETB::Core::Window::~Window() {
	SDL_DestroyWindow(sdlWindow);
}

void ETB::Core::Window::Swap() {
	SDL_GL_SwapWindow(sdlWindow);
}

void ETB::Core::Window::SetResizable(bool resizable) {
	SDL_SetWindowResizable(sdlWindow, resizable ? SDL_TRUE : SDL_FALSE);
}
