#include "Graphics.h"
#include "GUI.h"
#include "Window.h"

ETB::Core::Window* ETB::Core::Window::activeWindow;

ETB::Core::Window::Window(const std::string& title, int32_t w, int32_t h) {
	SDL_Init(SDL_INIT_EVERYTHING);

	sdlWindow = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		w, h, 
		SDL_WINDOW_OPENGL);

	 sdlGLContext = SDL_GL_CreateContext(sdlWindow);

	 Graphics::Init();

	 GUI::Init(sdlWindow, sdlGLContext);
	 GUI::SetTheme();
}

ETB::Core::Window::~Window() {
	GUI::Destroy();

	SDL_GL_DeleteContext(sdlGLContext);
	SDL_DestroyWindow(sdlWindow);
}

void ETB::Core::Window::Swap() {
	SDL_GL_SwapWindow(sdlWindow);
}

void ETB::Core::Window::SetResizable(bool resizable) {
	SDL_SetWindowResizable(sdlWindow, resizable ? SDL_TRUE : SDL_FALSE);
}

void ETB::Core::Window::Maximize() {
	SDL_MaximizeWindow(sdlWindow);
}

void ETB::Core::Window::Minimize() {
	SDL_MinimizeWindow(sdlWindow);
}

void ETB::Core::Window::GuiNewFrame() {
	GUI::NewFrame(sdlWindow);
}

void ETB::Core::Window::SetVSync(VSyncMode mode) {
	SDL_GL_SetSwapInterval((int32_t)mode);
}

void ETB::Core::Window::Warp(glm::ivec2 p) {
	SDL_WarpMouseInWindow(sdlWindow, p.x, p.y);
}

glm::ivec2 ETB::Core::Window::GetSize() {
	int32_t w, h;
	SDL_GetWindowSize(sdlWindow, &w, &h);
	return { w, h };
}
