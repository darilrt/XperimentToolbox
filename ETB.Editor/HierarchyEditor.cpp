#include <imgui.h>
#include <imgui_internal.h>

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


// customised list of actors without childrens
// background color defined if its active or not
// with icons
void ActorNode(xtb::Actor* actor) {
	ImGui::PushID(actor);
	
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImDrawList* drawList = window->DrawList;
	
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 max = ImVec2(pos.x + ImGui::GetContentRegionAvail().x, pos.y + ImGui::GetTextLineHeight());
	ImRect frame_bb(pos, max);

	const ImColor col = ImGui::GetStyleColorVec4(ImGuiCol_Header);
	const ImColor col_hovered = ImGui::GetStyleColorVec4(ImGuiCol_HeaderHovered);
	const ImColor col_active = ImGui::GetStyleColorVec4(ImGuiCol_HeaderActive);
	const ImColor text_col = ImGui::GetStyleColorVec4(ImGuiCol_Text);
	ImColor color = col;
	
	ImGui::ItemSize(frame_bb, ImGui::GetStyle().FramePadding.y);
	ImGui::ItemAdd(frame_bb, ImGui::GetID(actor->name.c_str()));

	// Pop style if the node is selected
	if (HierarchyEditor::selectedActor == actor) {
		color = col_active;
	}
	
	if (ImGui::IsItemHovered()) {
		color = col_hovered;
	}
	
	drawList->AddRectFilled(pos, max, color);
	drawList->AddText(pos, text_col, actor->name.c_str());
	
	if (ImGui::IsItemClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered()) {
		HierarchyEditor::selectedActor = actor;
	}

	if (ImGui::IsItemClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
		SceneEditor* sceneEditor = Editor::EditorWindow::GetEditor<SceneEditor>();
		sceneEditor->editorCamera->CenterCamera(actor->transform.position);
	}
	
	ImGui::PopID();
}

// list every actor in the scene
// and if the actor is selected then show the properties in the inspector
// when double click it should center the camera on the actor
void HierarchyEditor::GUI() {
	if (EditorApp::GetScene() == NULL) return;

	xtb::Scene* scene = EditorApp::GetScene();
	
	if (ImGui::BeginPopupContextWindow()) {
		if (ImGui::MenuItem("New Cube")) {
			CubeActor* cubeActor = scene->Instance<CubeActor>();
			cubeActor->Start();
		}
		ImGui::EndPopup();
	}
	
	ImGui::ShowDemoWindow();

	static ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanFullWidth;
	
	for (xtb::Actor* actor : scene->GetActors()) {
		ActorNode(actor);
	}
}
