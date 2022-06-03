#include <etb.h>
#include <iostream>
#include <cmath>

using namespace ETB;

class App : public Application {
public:
	static constexpr int32_t WIDTH = 1240;
	static constexpr int32_t HEIGHT = 720;

	Mesh tree;	
	Camera cam;
	Texture tex;

	float r;

	App() : Application("Title", WIDTH, HEIGHT), r(0), tex("Build-In/Textures/uv.png") {
		window.SetResizable(true);

		EventSystem::AddEventListener(EventType::WindowResize, [&](Event& e) {
			cam.SetViewport(0, 0, e.window.width, e.window.height);
			cam.SetPerspective(45.0f, ((float)e.window.width) / e.window.height, 0.1f, 100.0f);
		});
	}

	void Start() {
		ShaderLoader::Add("Build-In/Shaders/Test", true);

		tree = OBJLoader::FromFile("Build-In/Models/suzanne.obj");
		tree.SetupMesh();

		cam.SetPerspective(45.0f, ((float)WIDTH) / HEIGHT, 0.1f, 100.0f);
		cam.position = { 0, 0, -3 };
	}

	void Update() {
		r += Time::deltaTime * glm::radians(90.0f);
	}
	
	void Render() {
		cam.Use();

		Shader& sh = ShaderLoader::Get("Build-In/Shaders/Test");

		sh.Use();
		sh.SetMatrix("ETBWorldMatrix", cam.GetMatrix());

		glm::vec3 position = glm::vec3(0.0f);
		glm::quat rotation = glm::quat(glm::vec3(0, r, 0));

		glm::mat4 modelView = glm::translate(glm::mat4(1.0f), position) * glm::mat4_cast(rotation);
		sh.SetMatrix("ETBModelMatrix", modelView);

		sh.SetSampler2D("BaseColor", tex);

		Graphics::DrawMesh(tree);
	}

	void GUI() {
		ImGui::ShowDemoWindow();
	}
};

int main(int argc, char* argv[]) {
	App* app = new App();
	app->Run();

	delete app;
	return 0;
}