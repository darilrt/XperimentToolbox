#include <etb.h>

#include "EditorCamera.h"

using namespace ETB;

class App : public Application {
public:
	Scene scene;
	EditorCamera* editorCamera;
	std::vector<Uniform> uniforms;

	App() : Application("Hello, World", 1140, 620) {
		window.SetVSync(Core::VSyncMode::On);
		
		editorCamera = scene.Instance<EditorCamera>();

		ShaderLoader::Add("Built-In/Shaders/Test.gl");
		
		uniforms = ShaderLoader::Get("Built-In/Shaders/Test.gl").GetUniforms();
	}

	void Start() {
		scene.Start();
	}
	
	void Update() {
		scene.Update();
	}

	void Render() {
		scene.Render(editorCamera->camera);

		Present(editorCamera->camera.renderTexture.color);
	}

	void GUI() {
		Shader& shader = ShaderLoader::Get("Built-In/Shaders/Test.gl");

		if (ImGui::Begin("Shader viewer")) {

			static glm::vec3 val;

			for (Uniform u : uniforms) {
				ImGui::InputFloat3(u.name.c_str(), &val[0]);
			}

			if (ImGui::Button("Reload")) {
				shader.LoadSources();
				shader.Compile();

				uniforms = shader.GetUniforms();
			}

			ImGui::End();
		}
	}
};

ETB_ENTRY(App);