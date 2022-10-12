#include "CubeActor.h"

#include <etb.h>

using namespace ETB;

void CubeActor::Start() {
}

void CubeActor::Render() {
	Graphics::DrawMesh(Primitives::sphere, transform.GetMatrix(), material);
}

void CubeActor::GUI() {
}
