#include "Application.h"

#include "EventSystem.h"
#include "Window.h"
#include "Timer.h"
#include "Graphics.h"
#include "GUI.h"
#include "ActorHandler.h"
#include "Camera.h"
#include "Debug.h"
#include "Primitives.h"
#include "Shader.h"
#include "ShaderLoader.h"
#include "Screen.h"
#include "Texture.h"

#include <string>

ETB::Application::Application() : window("ETB.App", 800, 600) {
}

ETB::Application::Application(const std::string& title, int32_t w, int32_t h) : window(title, w, h) {
}

int ETB::Application::Run() {
	Core::Window::SetActive(&window);

	bool isRunning = true;
	EventSystem::AddEventListener(EventType::WindowQuit, [&](Event& e) { isRunning = false; });

	EventSystem::DispatchEventType(EventType::Start);
	Time::Start();
	Start();
	// ActorHandler::Start();

	int32_t elapsedMs;
	int32_t frameMs = 1000 / 240;

	ShaderLoader::Add("Built-In/Shaders/Present.glsl");

	while (isRunning) {
		elapsedMs = Time::GetTicks();

		Time::Tick();

		EventSystem::DispatchEventType(EventType::Tick);
		EventSystem::DispatchEvents();

		/// Update
		EventSystem::DispatchEventType(EventType::Update);
		Update();
		///

		/// Render
		Graphics::Clear();
		EventSystem::DispatchEventType(EventType::Render);
		Render();
		///

		/// GUI
		window.GuiNewFrame();
		EventSystem::DispatchEventType(EventType::GUI);
		GUI();
		// ActorHandler::GUI();
		ETB::GUI::Draw();
		///

		elapsedMs = Time::GetTicks() - elapsedMs;
		if (elapsedMs < frameMs) {
			SDL_Delay(frameMs - elapsedMs);
		}

		window.Swap();
	}

	return 0;
}

void ETB::Application::Present(Texture& texture) {
	Graphics::Clear();
	Shader& sh = ShaderLoader::Get("Built-In/Shaders/Present.glsl");
	sh.Bind();
	sh.SetSampler2D("texture", texture);
	Graphics::DrawMesh(Primitives::quad);
}

void ETB::Application::Start() {
}

void ETB::Application::Update() {
}

void ETB::Application::Render() {
}

void ETB::Application::GUI() {
}