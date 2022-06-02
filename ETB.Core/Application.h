#pragma once

#include <string>

#include "etbdefs.h"
#include "Window.h"

namespace ETB {

	class DECLSPEC Application {
	public:
		Application();
		Application(const std::string& title, int32_t width, int32_t height);
		void Run();

		virtual void Start();
		virtual void Update();
		virtual void Render();
		virtual void GUI();

	private:
		Core::Window window;
	};

}