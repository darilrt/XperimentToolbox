#pragma once

#include <etb.h>

#include "MeshRenderer.h"

class CubeActor : public xtb::Actor {
public:
	xtb::Material* material;

	CubeActor();

	void Start();
	void Render();

private:
	xtb::MeshRenderer* meshRenderer;
};
