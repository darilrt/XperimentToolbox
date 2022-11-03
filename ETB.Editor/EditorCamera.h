#pragma once

#include "etb.h"

class EditorCamera : public ETB::Actor {
public:
	enum {
		None,
		Fly,
		Orbit,
	} mouseMode;

	glm::vec2 screenCenter;

	ETB::Camera cam;
	bool isMoving;
	bool startMoving;

	EditorCamera();

	void Start();
	void Update();
	void Render();

	void SetSize(int32_t width, int32_t height);

	void CenterCamera(glm::vec3 position);
	void SetDistance(float newDistance);

private:
	float targetDistance;
	ETB::Transform target;
	glm::vec2 oldMousePos;
};
