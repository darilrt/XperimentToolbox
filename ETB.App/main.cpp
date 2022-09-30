#include <etb.h>

#include "EditorCamera.h"

using namespace ETB;

class App : public Application {
public:
	Scene scene;
	EditorCamera* editorCamera;

	App() : Application("Hello, World", 1240, 720) {
		window.SetVSync(Core::VSyncMode::On);
		
		editorCamera = scene.Instance<EditorCamera>();
	}

	void Start() {
		scene.Start();
	}
	
	void Update() {
		scene.Update();
	}

	void Render() {
		scene.Render(editorCamera->camera);

		//Shader& sh = ShaderLoader::Get("Built-In/Shaders/Test.glsl");
		//sh.Bind();
		//sh.SetMatrix("ETB_MATRIX_VP", cam.GetMatrix());
		//sh.SetMatrix("ETB_MATRIX_M", transform.GetMatrix());
		//sh.SetSampler2D("albedo", t);
		//Graphics::DrawMesh(Primitives::cube);

		//sh.SetMatrix("ETB_MATRIX_M", transform2.GetMatrix());
		//Graphics::DrawMesh(Primitives::cube);

		Present(editorCamera->camera.renderTexture.color);
	}

	void GUI() {
	}
};

ETB_ENTRY(App);