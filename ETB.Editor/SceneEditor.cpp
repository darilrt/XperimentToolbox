#include <etb.h>
#include <imgui_internal.h>
#include <glm/gtc/type_ptr.hpp>

#include "SceneEditor.h"
#include "EditorApp.h"
#include "CubeActor.h"

#include "vendor/ImGuizmo.h"
#include "HierarchyEditor.h"

REGISTER_EDITOR(SceneEditor);

using namespace xtb;

SceneEditor::SceneEditor() {
	title = "Scene";
}

SceneEditor::~SceneEditor() {
	delete editorCamera;
}

void SceneEditor::Start() {
	EditorApp::SetScene(&scene);

	editorCamera = new EditorCamera();
	editorCamera->cam.transform.position = glm::vec3(5.0f, 5.0f, 5.0f);
	editorCamera->cam.transform.LookAt(editorCamera->target.position);

	editorCamera->Start();
	scene.Start();
}

void SceneEditor::GUI() {
	ImGuizmo::SetDrawlist();

	ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 offset = ImGui::GetWindowContentRegionMin();
	ImVec2 size = ImGui::GetContentRegionAvail();
	ImVec2 p = ImGui::GetCursorScreenPos();

	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	const float buttonCount = 4;
	const float buttonSize = 30;
	const float buttonPadding = 8;
	const float headerWidth = buttonCount * buttonSize + buttonCount * buttonPadding + buttonPadding;
	
	bool ignoreGui = false;

	// Scene preview
	{
		editorCamera->Update();
		editorCamera->SetSize((int32_t)size.x, (int32_t)size.y);
		
		ignoreGui = ImGui::IsWindowHovered();
		
		scene.Render(editorCamera->cam);

		ImGui::Image((void*)(intptr_t)editorCamera->cam.renderTexture.color.GetID(), size, ImVec2(0, 1), ImVec2(1, 0));
	}

	static ImGuizmo::MODE gizmoMode(ImGuizmo::LOCAL);
	static ImGuizmo::OPERATION gizmoOperation(ImGuizmo::TRANSLATE);
	static bool showGrid = true;
	float* view = (float*)glm::value_ptr(editorCamera->cam.GetViewMatrix());
	float* projection = (float*)glm::value_ptr(editorCamera->cam.GetProjectionMatrix());
	
	ImGuizmo::SetRect(p.x, p.y, size.x, size.y);

	// Selection Gizmos
	if (HierarchyEditor::selectedActor != NULL) {
		Actor& actor = *HierarchyEditor::selectedActor;

		float* matrix = (float*)glm::value_ptr(actor.transform.GetMatrix());

		const bool res = ImGuizmo::Manipulate(view, projection, gizmoOperation, gizmoMode, matrix);

		ignoreGui &= !ImGuizmo::IsOver();

		glm::vec3 matrixRotation;
		ImGuizmo::DecomposeMatrixToComponents(
			matrix,
			glm::value_ptr(actor.transform.position),
			glm::value_ptr(matrixRotation),
			glm::value_ptr(actor.transform.scale)
		);

		actor.transform.rotation = glm::quat(glm::radians(matrixRotation));
	}

	// Tools
	{
		static auto ident = glm::mat4(1.0f);
		if (showGrid) ImGuizmo::DrawGrid(view, projection, (float*)glm::value_ptr(ident), 100.0f);
		
		offset.x += 8;
		offset.y += 8;
		ImGui::SetCursorPos(offset);

		if (Input::KeyDown(KeyCode::C)) gizmoMode = gizmoMode == ImGuizmo::WORLD ? ImGuizmo::LOCAL : ImGuizmo::WORLD;

		if (ImGui::Button("T", ImVec2(30, 30)) || Input::KeyDown(KeyCode::Q)) gizmoOperation = ImGuizmo::TRANSLATE;
		ignoreGui &= !ImGui::IsItemHovered();

		ImGui::SameLine();
 		if (ImGui::Button("R", ImVec2(30, 30)) || Input::KeyDown(KeyCode::W)) gizmoOperation = ImGuizmo::ROTATE;
		
		ImGui::SameLine();
		if (ImGui::Button("S", ImVec2(30, 30)) || Input::KeyDown(KeyCode::E)) gizmoOperation = ImGuizmo::SCALE;

		ImGui::SameLine();
		if (ImGui::Button("G", ImVec2(30, 30))) showGrid = !showGrid;
	}

	EventSystem::IgnoreGui(ignoreGui);
}
