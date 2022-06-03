#include <etb.h>
#include <iostream>
#include <cmath>

static constexpr int32_t WIDTH = 1240;
static constexpr int32_t HEIGHT = 720;

using namespace ETB;

class EditorCamera : public Actor {
public:
	Camera cam;

	bool isMoving;

	EditorCamera() : isMoving(false) {
		EventSystem::AddEventListener(EventType::WindowResize, [&](Event& e) {
			cam.SetViewport(0, 0, e.window.width, e.window.height);
			cam.SetPerspective(45.0f, ((float)e.window.width) / e.window.height, 0.1f, 100.0f);
		});

		EventSystem::AddEventListener(EventType::MouseButtonDown, [&](Event& e) {
			if (e.mouse.button == 3) {
				isMoving = true;
				Cursor::Grab(true);
			}
		});

		EventSystem::AddEventListener(EventType::MouseButtonUp, [&](Event& e) {
			if (e.mouse.button == 3) {
				isMoving = false;
				Cursor::Grab(false);
			}
		});

		EventSystem::AddEventListener(EventType::MouseMotion, [&](Event& e) {
			if (isMoving) {
				const float x = e.mouse.rel.x;
				const float y = e.mouse.rel.y;

				const glm::vec3 r = glm::vec3{ y, x, 0 } * Time::deltaTime * /* mouseSpeed */ 90.0f * TO_RADIANS;

				cam.transform.rotation = glm::rotate(cam.transform.rotation, r.x, glm::vec3{ 1, 0, 0 } * cam.transform.rotation);
				cam.transform.rotation = glm::rotate(cam.transform.rotation, r.y, glm::vec3{ 0, 1, 0 });
			}
		});
	}

	void Start() {
		cam.SetPerspective(45.0f, ((float)WIDTH) / HEIGHT, 0.1f, 100.0f);
		cam.transform.position = { 0, 0, -3 };

		Camera::SetActive(&cam);
	}

	void Update() {
		if (!isMoving) { return; }

		glm::vec3 dir = glm::vec3(
			Input::KeyPressed(KeyCode::A) - Input::KeyPressed(KeyCode::D),
			Input::KeyPressed(KeyCode::Q) - Input::KeyPressed(KeyCode::E),
			Input::KeyPressed(KeyCode::W) - Input::KeyPressed(KeyCode::S)
		);

		if (glm::length(dir) > 0) {
			dir = dir * cam.transform.rotation;
			cam.transform.position += dir * Time::deltaTime * /* cameraSpeed */ 5.0f;
		}
	}
};

class App : public Application {
public:
	EditorCamera* editorCamera;

	Mesh tree;

	Texture tex;
	Texture tex2;
	Transform tr;
	Transform trPlane;

	App() : Application("Title", WIDTH, HEIGHT), tex("Build-In/Textures/uv.png"), tex2("Build-In/Textures/color.png") {
		window.SetResizable(true);

		trPlane.scale = { 10, 10, 10 };
		trPlane.position = { 0, -1, 0 };
		trPlane.SetEulerAngles({ glm::radians(-90.0f), 0, 0});

		editorCamera = ActorHandler::Instance<EditorCamera>();
	}

	void Start() {
		ShaderLoader::Add("Build-In/Shaders/Test");
		
		tree = OBJLoader::FromFile("Build-In/Models/suzanne.obj");
		tree.SetupMesh();
	}

	void Update() {
	}
	
	void Render() {
		Shader& sh = ShaderLoader::Get("Build-In/Shaders/Test");

		sh.Use();
		sh.SetMatrix("ETBWorldMatrix", Camera::activeCamera->GetMatrix());
		sh.SetMatrix("ETBModelMatrix", tr.GetTransformMatrix());
		sh.SetSampler2D("BaseColor", tex);
		Graphics::DrawMesh(tree);

		sh.Use();
		sh.SetMatrix("ETBWorldMatrix", Camera::activeCamera->GetMatrix());
		sh.SetMatrix("ETBModelMatrix", trPlane.GetTransformMatrix());
		sh.SetSampler2D("BaseColor", tex2);
		Graphics::DrawMesh(Primitives::quad);
	}
	
	void GUI() {
		Debug::ShowStatus();
		// Debug::TransformEditor(Camera::activeCamera->transform);
		// ImGui::ShowDemoWindow();
	}
};

int main(int argc, char* argv[]) {
	App* app = new App();
	app->Run();

	delete app;
	return 0;
}