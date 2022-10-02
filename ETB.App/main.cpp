#include <etb.h>

#include "EditorCamera.h"

using namespace ETB;

class CubeActor : public Actor {
public:
	Texture t;

	CubeActor() : t("Built-In/Textures/color.png") {
	}
	
	void Start() {
		ShaderLoader::Add("Built-In/Shaders/Test.gl");
	}

	void Render() {
		Shader& sh = ShaderLoader::Get("Built-In/Shaders/Test.gl");

		sh.Bind();
		sh.SetMatrix("ETB_MATRIX_VP", Camera::GetActive()->GetMatrix());
		sh.SetMatrix("ETB_MATRIX_M", transform.GetMatrix());
		sh.SetSampler2D("albedo", t);

		Graphics::DrawMesh(Primitives::cube);

		sh.Unbind();
	}
};

void MaterialPreview(Shader& shader) {
	std::vector<Uniform> uniforms = shader.GetUniforms();

	if (ImGui::Begin("Shader viewer")) {

		static glm::vec3 val;

		for (Uniform u : uniforms) {
			ImGui::InputFloat3(u.name.c_str(), &val[0]);
		}

		if (ImGui::Button("Reload")) {
			shader.LoadSources();
			shader.Compile();
		}

		ImGui::End();
	}
}

class App : public Application {
public:
	Scene scene;
	
	EditorCamera* editorCamera;
	CubeActor* cubeActor;

	App() : Application("Hello, World", 1140, 620) {
		window.SetVSync(Core::VSyncMode::On);
		
		editorCamera = scene.Instance<EditorCamera>();
		cubeActor = scene.Instance<CubeActor>();

		ShaderLoader::Add("Built-In/Shaders/Test.gl");
	}

	void Start() {
		scene.Start();

		editorCamera->camera.transform.position = glm::vec3(0, 0, 10);
	}
	
	void Update() {
		scene.Update();
	}

	void Render() {
		scene.Render(editorCamera->camera);

		Present(editorCamera->camera.renderTexture.color);
	}

	void GUI() {
		ImGui::ShowDemoWindow();

		if (ImGui::Begin("File Explorer")) {
			ImGui::End();
		}
	}
};

ETB_ENTRY(App);