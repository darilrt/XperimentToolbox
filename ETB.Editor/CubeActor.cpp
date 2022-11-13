#include <etb.h>

#include "CubeActor.h"
#include "MeshRenderer.h"

using namespace xtb;

CubeActor::CubeActor() {
	name = "CubeActor";

	meshRenderer = AddComponent<xtb::MeshRenderer>();
}

void CubeActor::Start() {
}

void CubeActor::Render() {
}