#include <etb.h>
#include <filesystem>
#include <stdlib.h>

#include "EditorCamera.h"

using namespace ETB;

class App : public Application {
public:
	Transform t;

	App() : Application("Hello, World", 1140, 620) {
		window.SetVSync(Core::VSyncMode::On);
	}

	~App() {
	}

	void Start() {
		Application::Quit();
	}
	
	void Update() {
	}

	void Render() {
	}

	void GUI() {
	}
};

ETB_ENTRY(App);