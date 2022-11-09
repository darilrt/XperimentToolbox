#include "InspectorEditor.h"
#include "EditorGUI.h"

REGISTER_EDITOR(InspectorEditor);

InspectorEditor::InspectorEditor() {
	title = "Inspector";
}

void InspectorEditor::Start() {

}

void TestGUI() {
	static float v = 100;
	ImGui::InputFloat("Input Float", &v);
	ImGui::DragFloat("Drag Float", &v);
	ImGui::SliderFloat("Slider Float", &v, 0, 100, "%f", 1.0f);
}

void InspectorEditor::GUI() {
	static std::string uuid = "";
	static std::string uuid2 = "248a0259-423e-431f-ae75-cb1673b597c3";
	static std::string uuid3 = "8e4daaf5-e6c0-4311-8f8f-d2af248afa37";
	static std::string uuid4 = "";
	
	EditorGUI::InputAsset<xtb::TextureAsset>("Texture 1", uuid);
	EditorGUI::InputAsset<xtb::TextureAsset>("Texture 2", uuid2);
	EditorGUI::InputAsset<xtb::TextureAsset>("Texture 3", uuid3);
	EditorGUI::InputAsset<xtb::MaterialAsset>("Material", uuid4);
	
	auto ta = xtb::AssetDatabase::GetAssetByUUID<xtb::TextureAsset>(uuid);

	if (ta) {
		EditorGUI::Image(*ta->texture, glm::vec2(200, 200));
	}

	TestGUI();
}