#include <etb.h>

#include "EditorApp.h"
#include "AssetsEditor.h"

#include "MaterialAssetInspector.h"
#include "MeshAssetInspector.h"

REGISTER_EDITOR(AssetsEditor);

AssetsEditor::AssetsEditor() {
	title = "Assets Editor";

	inspectors[".mat"] = new MaterialAssetInspector();
	inspectors[".obj"] = new MeshAssetInspector();
}

void AssetsEditor::GUI() {
	if (currentInspector != NULL) {
		currentInspector->GUI();
	}
}

void AssetsEditor::OpenByPath(std::filesystem::path path) {
	std::string ext = path.extension().string();
	
	if (inspectors.count(ext) != 0) {
		currentInspector = inspectors[ext];

		currentInspector->resourcePath = path;

		currentInspector->Start();
		ImGui::SetWindowFocus(title.c_str());
	}
	else {
		currentInspector = NULL;
	}
}
