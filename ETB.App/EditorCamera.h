#pragma once

#include "etb.h"

class EditorCamera : public ETB::Actor {
public:
	ETB::Camera cam;
	bool isMoving;

	EditorCamera();

	void Start();
	void Update();
};
