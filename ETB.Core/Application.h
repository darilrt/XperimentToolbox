#pragma once

#include <string>

#include "etbdefs.h"
#include "Window.h"
#include "Texture.h"

namespace xtb {

	class DECLSPEC Application {
	public:
		static bool isRunning;
		Core::Window window;

		Application();
		Application(const std::string& title, int32_t width, int32_t height);
		
		int Run();
		void Present(Texture& texture);

		virtual void Start();
		virtual void Update();
		virtual void Render();
		virtual void GUI();

		static void Quit();
	};

}