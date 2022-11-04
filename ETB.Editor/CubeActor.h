#pragma once

#include <etb.h>

class CubeActor : public xtb::Actor {
public:
	xtb::Material material;

	void Start();

	void Render();
};

