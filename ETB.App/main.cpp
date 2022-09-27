#include <etb.h>

using namespace ETB;

class App : public Application {
public:
	Texture t;
	Camera cam;
	Transform transform;

	App() : Application("Hello, World", 1240, 720), t("Built-In/Textures/color.png") {
		window.SetVSync(Core::VSyncMode::On);

		ShaderLoader::Add("Built-In/Shaders/Test.glsl");
		ShaderLoader::Add("Built-In/Shaders/TestInstanced.glsl");
	}

	void Start() {
		glm::ivec2 size = Screen::GetSize();
		cam.SetViewport(0, 0, size.x, size.y);

		cam.SetPerspective(45.0f, (float)size.x / size.y, 0.1f, 100.0f);
		cam.transform.position = glm::vec3(0, 0, 10);
	}
	
	void Update() {
		transform.Rotate(glm::vec3(0.5f, 1.0f, 1.5f) * Time::deltaTime);
	}

	void Render() {
		cam.Use();
		cam.renderTexture.BindFramebuffer();
		Graphics::Clear();

		Shader& sh = ShaderLoader::Get("Built-In/Shaders/Test.glsl");
		sh.Use();
		// Graphics::DrawMeshInstanced(Primitives::cube);

		sh = ShaderLoader::Get("Built-In/Shaders/Test.glsl");
		sh.Use();
		sh.SetMatrix("ETB_MATRIX_VP", cam.GetMatrix());
		sh.SetMatrix("ETB_MATRIX_M", transform.GetMatrix());
		sh.SetSampler2D("albedo", t);
		Graphics::DrawMesh(Primitives::cube);

		cam.renderTexture.UnbindFramebuffer();

		Present(cam.renderTexture.color);
	}

	void GUI() {
	}
};

int main(int argc, char* argv[]) {
	App* app = new App();
	app->Run();

	return 0;
}