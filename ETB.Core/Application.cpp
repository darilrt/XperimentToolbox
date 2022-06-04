#include "Application.h"

#include "EventSystem.h"
#include "Window.h"
#include "Timer.h"
#include "Graphics.h"
#include "GUI.h"
#include "ActorHandler.h"
#include "Camera.h"
#include "Debug.h"

#include <string>

ETB::Application::Application() : window("ETB.App", 800, 600) {
}

ETB::Application::Application(const std::string& title, int32_t w, int32_t h) : window(title, w, h) {
}

void ETB::Application::Run() {
	Core::Window::SetActive(&window);

	bool isRunning = true;
	EventSystem::AddEventListener(EventType::WindowQuit, [&](Event& e) { isRunning = false; });

	EventSystem::DispatchEventType(EventType::Start);
	Time::Start();
	Start();
	ActorHandler::Start();

	int32_t elapsedMs;
	int32_t frameMs = 1000 / 240;

	while (isRunning) {
		elapsedMs = Time::GetTicks();

		Time::Tick();

		EventSystem::DispatchEventType(EventType::Tick);
		EventSystem::DispatchEvents();

		/// Update
		EventSystem::DispatchEventType(EventType::Update);
		Update();
		ActorHandler::Update();
		///

		/// Render
		Graphics::Clear();
		if (Camera::GetActive()) Camera::GetActive()->Use();
		EventSystem::DispatchEventType(EventType::Render);
		Render();
		ActorHandler::Render();
		///

		/// GUI
		window.GuiNewFrame();
		EventSystem::DispatchEventType(EventType::GUI);
		GUI();
		ActorHandler::GUI();
		ETB::GUI::Draw();
		///

		elapsedMs = Time::GetTicks() - elapsedMs;
		if (elapsedMs < frameMs) {
			SDL_Delay(frameMs - elapsedMs);
		}

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