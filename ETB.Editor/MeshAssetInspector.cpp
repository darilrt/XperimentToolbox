#include <etb.h>

#include "MeshAssetInspector.h"
#include "EditorGUI.h"

static xtb::Mesh mesh;
static xtb::Material mat;

void MeshAssetInspector::Start() {
	mat.LoadFromFile("Built-In/Materials/lit.mat");

	mesh = xtb::OBJLoader::FromFile(resourcePath.string());
	mesh.Setup();
}

void MeshAssetInspector::GUI() {
	EditorGUI::InteractivePreview(&mesh, &mat);
}
