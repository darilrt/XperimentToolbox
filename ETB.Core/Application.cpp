#include "Application.h"
#include "EventSystem.h"
#include "Window.h"
#include "Timer.h"
#include "Graphics.h"

#include <string>

ETB::Application::Application() : window("ETB.App", 800, 600) {
}

ETB::Application::Application(const std::string& title, int32_t w, int32_t h) : window(title, w, h) {
}

void ETB::Application::Run() {
	EventSystem::DispatchEventType(EventType::Start);

	bool isRunning = true;
	EventSystem::AddEventListener(EventType::Quit, [&](Event& e) { isRunning = false; });

	Time::Start();
	Start();

	while (isRunning) {
		Time::Tick();

		EventSystem::DispatchEventType(EventType::Tick);
		EventSystem::DispatchEvents();

		/// Update
		Update();
		///

		/// Render
		Graphics::Clear();
		Render();
		///

		/// GUI
		GUI();
		///

		window.Swap();
	}
}

void ETB::Application::Start() {
}

void ETB::Application::Update() {
}

void ETB::Application::Render() {
}

void ETB::Application::GUI() {
}