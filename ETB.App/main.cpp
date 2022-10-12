#include <etb.h>

#include "EditorCamera.h"

using namespace ETB;

class App : public Application {
public:
	Transform t;

	App() : Application("Hello, World", 1140, 620) {
		window.SetVSync(Core::VSyncMode::On);
	}

	void Start() {
	}
	
	void Update() {
	}

	void Render() {
	}

	void GUI() {
	}
};

ETB_ENTRY(App);