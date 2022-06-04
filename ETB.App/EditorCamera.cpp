#include "EditorCamera.h"

EditorCamera::EditorCamera() : isMoving(false) {
	using namespace ETB;

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

			const glm::vec3 r = glm::vec3{ y, x, 0 } *Time::deltaTime * /* mouseSpeed */ 90.0f * TO_RADIANS;

			cam.transform.rotation = glm::rotate(cam.transform.rotation, r.x, glm::vec3{1, 0, 0} * cam.transform.rotation);
			cam.transform.rotation = glm::rotate(cam.transform.rotation, r.y, glm::vec3{ 0, 1, 0 });
		}
	});
}

void EditorCamera::Start() {
	using namespace ETB;

	glm::ivec2 size = Screen::GetSize();
	cam.SetPerspective(45.0f, ((float)size.x) / size.y, 0.1f, 100.0f);
	cam.transform.position = { 0, 0, 3 };

	Camera::SetActive(&cam);
}

void EditorCamera::Update() {
	using namespace ETB;

	if (!isMoving) { return; }

	glm::vec3 dir = glm::vec3(
		Input::KeyPressed(KeyCode::D) - Input::KeyPressed(KeyCode::A),
		Input::KeyPressed(KeyCode::E) - Input::KeyPressed(KeyCode::Q),
		Input::KeyPressed(KeyCode::S) - Input::KeyPressed(KeyCode::W)
	);

	if (glm::length(dir) > 0) {
		dir = dir * cam.transform.rotation;
		cam.transform.position += dir * Time::deltaTime * /* cameraSpeed */ 5.0f;
	}
}
