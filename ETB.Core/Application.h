#pragma once

#include <string>

#include "etbdefs.h"
#include "Window.h"
#include "Texture.h"

namespace ETB {

	class DECLSPEC Application {
	public:
		Core::Window window;

		Application();
		Application(const std::string& title, int32_t width, int32_t height);
		
		int Run();
		void Present(Texture& texture);

		virtual void Start();
		virtual void Update();
		virtual void Render();
		virtual void GUI();
	};

}