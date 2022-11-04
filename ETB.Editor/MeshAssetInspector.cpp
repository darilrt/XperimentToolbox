#include <etb.h>

#include "MeshAssetInspector.h"
#include "EditorGUI.h"

static xtb::Mesh* mesh;
static xtb::Material mat;

void MeshAssetInspector::Start() {
	auto m = xtb::OBJLoader::FromFile(resourcePath.string());

	mesh = &m;
	mesh->Setup();
}

void MeshAssetInspector::GUI() {
	EditorGUI::InteractivePreview(mesh, mat);
}
