#include "HierarchyEditor.h"
#include "EditorApp.h"

#include "CubeActor.h"

HierarchyEditor HierarchyEditor::hierarchyEditor;

HierarchyEditor::HierarchyEditor() {
	EditorApp::Add(this);

	title = "Hierarchy";
}

void HierarchyEditor::Start() {
}

void HierarchyEditor::GUI() {
	ImGui::Begin(title.c_str(), &isOpen);

	if (EditorApp::GetScene() == nullptr) {
		ImGui::End();
		return;
	}

	ETB::Scene* scene = EditorApp::GetScene();

	if (ImGui::BeginPopupContextWindow()) {
		if (ImGui::MenuItem("New Cube")) {
			CubeActor* cubeActor = scene->Instance<CubeActor>();
			cubeActor->name = "New CubeActor";

			cubeActor->Start();
		}

		ImGui::EndPopup();
	}

	int i = 0;
	for (ETB::Actor* actor : scene->GetActors()) {
		if (ImGui::TreeNodeEx(actor->name.c_str(), ImGuiTreeNodeFlags_Leaf)) {
			ImGui::TreePop();
		}
		i++;
	}

	//if (ImGui::TreeNodeEx("Entity 1", ImGuiTreeNodeFlags_Selected)) {
	//	ImGui::TreePop();
	//}

	//if (ImGui::TreeNodeEx("Entity 2", ImGuiTreeNodeFlags_Leaf)) {
	//	ImGui::TreePop();
	//}

	ImGui::End();
}
