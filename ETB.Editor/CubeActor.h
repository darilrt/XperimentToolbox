#pragma once

#include <etb.h>

class CubeActor : public ETB::Actor {
public:
	ETB::Material material;

	void Start();

	void Render();

	void GUI();
};

