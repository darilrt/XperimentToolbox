#include "EditorCamera.h"

EditorCamera::EditorCamera() : isMoving(false), startMoving(false), mouseMode(None) {
	using namespace ETB;
	name = "Editor Camera";

	EventSystem::AddEventListener(EventType::MouseButtonDown, [&](Event& e) {
		if (e.mouse.button == 3) {
			startMoving = true;
			mouseMode = Fly;
		}
		if (e.mouse.button == 1) {
			startMoving = true;
			mouseMode = Orbit;
		}
	});

	EventSystem::AddEventListener(EventType::MouseButtonUp, [&](Event& e) {
		if (e.mouse.button == 3 || e.mouse.button == 1) {
			isMoving = false;
			startMoving = false;
			mouseMode = None;
			Cursor::Grab(false);
		}
	});

	EventSystem::AddEventListener(EventType::MouseMotion, [&](Event& e) {
		if (startMoving) {
			startMoving = false;
			isMoving = true;
			Cursor::Grab(true);
		}
	});
}

void EditorCamera::Start() {
	using namespace ETB;

	glm::ivec2 size = Screen::GetSize();

	cam.SetPerspective(45.0f, ((float)size.x) / size.y, 0.1f, 100.0f);
	cam.SetViewport(0, 0, size.x, size.y);
	cam.SetPerspective(45.0f, ((float)size.x) / size.y, 0.1f, 100.0f);	
	
	Camera::SetActive(&cam);

	oldMousePos = Input::GetMousePosition();
	
	targetDistance = glm::distance(target.position, cam.transform.position);

	target.rotation = glm::lookAt(target.position, cam.transform.position, glm::vec3(0, 1, 0));

	target.scale = { 0.13f, 0.13f, 0.13f };
}

void EditorCamera::Update() {
	using namespace ETB;

	if (Input::KeyPressed(KeyCode::G)) { // Wheel up
		targetDistance = glm::distance(target.position, cam.transform.position);
		SetDistance(targetDistance * (1.0f - Time::deltaTime));
	}

	if (Input::KeyPressed(KeyCode::F)) { // Wheel down
		targetDistance = glm::distance(target.position, cam.transform.position);
		SetDistance(targetDistance * (1.0f + Time::deltaTime));
	}

	if (Input::KeyDown(KeyCode::H)) {
		CenterCamera({ 0, 0, 0 });
	}

	glm::vec2 rel = Input::GetMousePosition() - oldMousePos; // This should be Input::GetMouseRel()

	if (isMoving && mouseMode & Fly) {
		if (Input::KeyDown(KeyCode::Escape)) {
			isMoving = false;
			Cursor::Grab(false);
			return;
		}

		const glm::vec3 r = glm::vec3{ rel.y, rel.x, 0 } *Time::deltaTime * glm::radians(25.0f);

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
		
		target.position = cam.transform.position + cam.transform.GetForward() * targetDistance;
		target.LookAt(cam.transform.position);

		Cursor::Warp(screenCenter);
	}
	else if (isMoving && mouseMode & Orbit) {
		if (Input::KeyDown(KeyCode::Escape)) {
			isMoving = false;
			Cursor::Grab(false);
			return;
		}

		const glm::vec3 r = glm::vec3{ rel.y, rel.x, 0 } *Time::deltaTime * glm::radians(25.0f);

		target.rotation = glm::rotate(target.rotation, -r.x, glm::vec3{ 1, 0, 0 } * target.rotation);
		target.rotation = glm::rotate(target.rotation, r.y, glm::vec3{ 0, 1, 0 });

		targetDistance = glm::distance(target.position, cam.transform.position);

		cam.transform.position = target.position + target.GetForward() * targetDistance;
		cam.transform.LookAt(target.position);

		Cursor::Warp(screenCenter);
	}

	oldMousePos = Input::GetMousePosition();
}

void EditorCamera::Render() {
	using namespace ETB;
	static Material mat;
	Graphics::DrawMesh(Primitives::sphere, target.GetMatrix(), mat);
}

void EditorCamera::SetSize(int32_t width, int32_t height) {
	cam.SetViewport(0, 0, width, height);
	cam.SetPerspective(45.0f, ((float)width) / height, 0.1f, 100.0f);
}

void EditorCamera::CenterCamera(glm::vec3 position) {
	target.position = position;

	targetDistance = glm::distance(target.position, cam.transform.position);

	cam.transform.LookAt(target.position);
	target.LookAt(cam.transform.position);
}

void EditorCamera::SetDistance(float newDistance) {
	glm::vec3 dir = glm::normalize(cam.transform.position - target.position);
	cam.transform.position = target.position + dir * newDistance;
	targetDistance = newDistance;
}
