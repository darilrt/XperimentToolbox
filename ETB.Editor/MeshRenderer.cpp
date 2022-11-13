#include "MeshRenderer.h"
#include "EditorGUI.h"

xtb::MeshRenderer::MeshRenderer() {
	name = "MeshRenderer";
}

void xtb::MeshRenderer::Start() {
}

void xtb::MeshRenderer::Render() {
	if (material != NULL) {
		Graphics::DrawMesh(Primitives::cube, GetActor()->transform.GetMatrix(), *material);
	}
}

void xtb::MeshRenderer::InspectorRender() {
	static std::string materialUUID;
	materialUUID = material ? material->GetUUID() : "";

	bool changed = EditorGUI::InputAsset<Material>("Material", materialUUID);
	
	if (changed) {
		material = Asset::GetAsset<Material>(materialUUID);
	}
}
