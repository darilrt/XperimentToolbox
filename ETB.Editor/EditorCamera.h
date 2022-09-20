#pragma once

#include "etb.h"

class EditorCamera : public ETB::Actor {
public:
	glm::vec2 screenCenter;

	ETB::Camera cam;
	bool isMoving;

	EditorCamera();

	void Start();
	void Update();

	void SetSize(int32_t width, int32_t height);

private:
	glm::vec2 oldMousePos;
};
