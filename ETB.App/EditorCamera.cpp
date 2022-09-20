#include "EditorCamera.h"

EditorCamera::EditorCamera() : isMoving(false) {
	using namespace ETB;

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
}

void EditorCamera::Start() {
	using namespace ETB;

	glm::ivec2 size = Screen::GetSize();
	screenCenter = glm::vec2(size) / 2.0f;

	cam.SetPerspective(45.0f, ((float)size.x) / size.y, 0.1f, 100.0f);
	cam.transform.position = { 0, 0, 3 };
	cam.SetViewport(0, 0, size.x, size.y);

	Camera::SetActive(&cam);

	oldMousePos = Input::GetMousePosition();
}

void EditorCamera::Update() {
	using namespace ETB;

	if (isMoving) {
		glm::vec2 rel = Input::GetMousePosition() - oldMousePos;
		const glm::vec3 r = glm::vec3{ rel.y, rel.x, 0 } *Time::deltaTime * glm::radians(25.0f);

		Cursor::Warp(screenCenter);

		cam.transform.rotation = glm::rotate(cam.transform.rotation, r.x, glm::vec3{ 1, 0, 0 } *cam.transform.rotation);
		cam.transform.rotation = glm::rotate(cam.transform.rotation, r.y, glm::vec3{ 0, 1, 0 });

		glm::vec3 dir = glm::vec3(
			Input::KeyPressed(KeyCode::D) - Input::KeyPressed(KeyCode::A),
			Input::KeyPressed(KeyCode::E) - Input::KeyPressed(KeyCode::Q),
			Input::KeyPressed(KeyCode::S) - Input::KeyPressed(KeyCode::W)
		);

		if (glm::length(dir) > 0) {
			dir = dir * cam.transform.rotation;
			cam.transform.position += dir * Time::deltaTime * 5.0f;
		}
	}

	oldMousePos = Input::GetMousePosition();
}

void EditorCamera::SetSize(int32_t width, int32_t height) {
	cam.SetViewport(0, 0, width, height);
	cam.SetPerspective(45.0f, ((float)width) / height, 0.1f, 100.0f);
}
