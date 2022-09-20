#pragma once

#include <etb.h>

class CubeActor : public ETB::Actor {
public:
	ETB::Transform transform;

	void Start();

	void Render();
};

