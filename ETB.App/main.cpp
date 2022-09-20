#include <etb.h>

using namespace ETB;

class App : public Application {
public:
	App() : Application("Hello, World", 1240, 720) {
		ShaderLoader::Add("Built-In/Shaders/Test.glsl");
	}

	void Start() {
	}

	void Update() {
	}

	void Render() {
		Shader& sh = ShaderLoader::Get("Built-In/Shaders/Test.glsl");

		sh.Use();
		sh.SetMatrix("ETB_MATRIX_VP", Camera::GetActive()->GetMatrix());
		sh.SetMatrix("ETB_MATRIX_M", transform.GetTransformMatrix());

		Graphics::DrawMesh(Primitives::cube);
	}

	void GUI() {
	}
};

int main(int argc, char* argv[]) {
	App* app = new App();
	app->Run();

	return 0;
}