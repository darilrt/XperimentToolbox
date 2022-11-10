#include "CubeActor.h"

#include <etb.h>

using namespace xtb;

CubeActor::CubeActor() {
	name = "CubeActor";
}

void CubeActor::Start() {
	material.LoadFromFile("Built-In/Materials/test.mat");
}

void CubeActor::Render() {
	Graphics::DrawMesh(Primitives::cube, transform.GetMatrix(), material);
}