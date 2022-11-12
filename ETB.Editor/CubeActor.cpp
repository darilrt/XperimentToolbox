#include "CubeActor.h"

#include <etb.h>

using namespace xtb;

CubeActor::CubeActor() {
	name = "CubeActor";
}

void CubeActor::Start() {
	const std::string uuid = xtb::AssetDatabase::GetUUIDByPath("Built-In/Materials/test.mat");
	material = xtb::AssetDatabase::GetAssetByUUID<xtb::Material>(uuid);
}

void CubeActor::Render() {
	Graphics::DrawMesh(Primitives::cube, transform.GetMatrix(), *material);
}