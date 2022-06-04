#include <etb.h>
#include <iostream>
#include <cmath>

#include "EditorCamera.h"

static constexpr int32_t WIDTH = 1240;
static constexpr int32_t HEIGHT = 720;

using namespace ETB;

class App : public Application {
public:
	EditorCamera* editorCamera;

	Mesh tree;
	Mesh sphere;

	Texture tex;
	Texture tex2;
	Texture tex3;

	Transform tr;
	Transform trPlane;
	Transform trSph;

	App() : Application("Title", WIDTH, HEIGHT), tex("Build-In/Textures/uv.png"), tex2("Build-In/Textures/color.png"), tex3("Build-In/Textures/milk_way.jpg") {
		window.SetResizable(true);

		trPlane.position = { 0, -1, 0 };
		trPlane.scale = { 10, 10, 10 };
		trPlane.SetEulerAngles({ glm::radians(-90.0f), 0, 0});
		
		trSph.scale = { 50, 50, 50 };
		
		editorCamera = ActorHandler::Instance<EditorCamera>();
	}

	void Start() {
		ShaderLoader::Add("Build-In/Shaders/Test");
		ShaderLoader::Add("Build-In/Shaders/SkyBox");
		
		tree = OBJLoader::FromFile("Build-In/Models/suzanne.obj");
		tree.SetupMesh();

		sphere = OBJLoader::FromFile("Build-In/Models/sphere_inverse_normals.obj");
		sphere.SetupMesh();
	}

	void Update() {
	}
	
	void Render() {
		Shader& sh = ShaderLoader::Get("Build-In/Shaders/Test");

		sh.Use();
		sh.SetMatrix("ETBWorldMatrix", Camera::GetActive()->GetMatrix());
		sh.SetMatrix("ETBModelMatrix", tr.GetTransformMatrix());
		sh.SetSampler2D("BaseColor", tex);
		Graphics::DrawMesh(tree);

		sh.Use();
		sh.SetMatrix("ETBWorldMatrix", Camera::GetActive()->GetMatrix());
		sh.SetMatrix("ETBModelMatrix", trPlane.GetTransformMatrix());
		sh.SetSampler2D("BaseColor", tex2);
		Graphics::DrawMesh(Primitives::quad);

		trSph.position = Camera::GetActive()->transform.position;
		Shader& sb = ShaderLoader::Get("Build-In/Shaders/SkyBox");
		sb.Use();
		sb.SetMatrix("ETB_MATRIX_VP", Camera::GetActive()->GetMatrix());
		sb.SetMatrix("ETB_MATRIX_M", trSph.GetTransformMatrix());
		sb.SetSampler2D("_BaseColor", tex3);
		Graphics::DrawMesh(sphere);
	}
	
	void GUI() {
		Debug::ShowStatus();
		Debug::TransformEditor(trSph);
		// ImGui::ShowDemoWindow();
	}
};

int main(int argc, char* argv[]) {
	App* app = new App();
	app->Run();

	delete app;
	return 0;
}