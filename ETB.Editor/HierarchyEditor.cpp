#include "HierarchyEditor.h"
#include "EditorApp.h"

#include "CubeActor.h"
#include "SceneEditor.h"

REGISTER_EDITOR(HierarchyEditor);

xtb::Actor* HierarchyEditor::selectedActor = NULL;

HierarchyEditor::HierarchyEditor() {
	title = "Hierarchy";
}

void HierarchyEditor::Start() {
}

void HierarchyEditor::GUI() {
	if (EditorApp::GetScene() == NULL) return;

	xtb::Scene* scene = EditorApp::GetScene();

	if (ImGui::BeginPopupContextWindow()) {
		if (ImGui::MenuItem("New Cube")) {
			CubeActor* cubeActor = scene->Instance<CubeActor>();
			cubeActor->name = "New CubeActor";

			cubeActor->Start();
		}

		ImGui::EndPopup();
	}
	
	ImGui::ShowDemoWindow();

	static ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanFullWidth;

	static int selected = -1;

	for (xtb::Actor* actor : scene->GetActors()) {
		
		ImGui::TreeNodeEx(actor->name.c_str(), nodeFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);
		
		if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered()) {
			SceneEditor* sceneEditor = Editor::EditorWindow::GetEditor<SceneEditor>();
			sceneEditor->editorCamera->CenterCamera(actor->transform.position);
		}

		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered()) {
			HierarchyEditor::selectedActor = actor;
		}
	}
}
