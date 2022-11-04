#include "CubeActor.h"

#include <etb.h>

using namespace xtb;

void CubeActor::Start() {
	material.LoadFromFile("Built-In/Materials/test.mat");
}

void CubeActor::Render() {
	Graphics::DrawMesh(Primitives::cube, transform.GetMatrix(), material);
}