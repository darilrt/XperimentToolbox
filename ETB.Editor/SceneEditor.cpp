#include <etb.h>
#include <imgui_internal.h>
#include <glm/gtc/type_ptr.hpp>

#include "SceneEditor.h"
#include "EditorApp.h"
#include "CubeActor.h"

#include "vendor/ImGuizmo.h"

REGISTER_EDITOR(SceneEditor);

using namespace ETB;

SceneEditor::SceneEditor() {
	title = "Scene";
}

SceneEditor::~SceneEditor() {
	delete editorCamera;
}

void SceneEditor::Start() {
	EditorApp::SetScene(&scene);

	editorCamera = new EditorCamera();

	cubeActor = scene.Instance<CubeActor>();
	cubeActor->name = "My Cube";
	cubeActor->Start();

	editorCamera->Start();
	scene.Start();
}

void SceneEditor::Style() {
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
}

void SceneEditor::GUI() {
	editorCamera->Update();

	ImGuizmo::SetDrawlist();

	EventSystem::ignoreGui = ImGui::IsWindowHovered();

	ImVec2 offset = ImGui::GetWindowContentRegionMin();
	ImVec2 size = ImGui::GetContentRegionAvail();

	editorCamera->SetSize((int32_t)size.x, (int32_t)size.y);
	editorCamera->screenCenter = glm::vec2(offset.x, offset.y) + glm::vec2(size.x, size.y) / 2.0f;

	scene.Render(editorCamera->cam);

	ImGui::Image((void*)(intptr_t)editorCamera->cam.renderTexture.color.GetTextureId(), size, ImVec2(0, 1), ImVec2(1, 0));

	// Toolbar

	// Selection Gizmos

	ImVec2 windowPos = ImGui::GetWindowPos();
	ImGuizmo::SetRect(windowPos.x, windowPos.y + offset.y, size.x, size.y);
	
	Actor& actor = *cubeActor;

	float* view = (float*)glm::value_ptr(editorCamera->cam.GetViewMatrix());
	float* projection = (float*)glm::value_ptr(editorCamera->cam.GetProjectionMatrix());
	float* matrix = (float*)glm::value_ptr(actor.transform.GetMatrix());

	static ImGuizmo::MODE gizmoMode(ImGuizmo::LOCAL);
	static ImGuizmo::OPERATION gizmoOperation(ImGuizmo::TRANSLATE);

	if (Input::KeyDown(KeyCode::Num1)) gizmoOperation = ImGuizmo::TRANSLATE;
	if (Input::KeyDown(KeyCode::Num2)) gizmoOperation = ImGuizmo::ROTATE;
	if (Input::KeyDown(KeyCode::Num3)) gizmoOperation = ImGuizmo::SCALE;
	
	if (Input::KeyDown(KeyCode::C)) gizmoMode = gizmoMode == ImGuizmo::WORLD ? ImGuizmo::LOCAL : ImGuizmo::WORLD;
	
	static auto ident = glm::mat4(1.0f);
	// ImGuizmo::DrawGrid(view, projection, (float*)glm::value_ptr(ident), 100.0f);
	ImGuizmo::Manipulate(view, projection, gizmoOperation, gizmoMode, matrix);

	glm::vec3 matrixRotation;
	ImGuizmo::DecomposeMatrixToComponents(
		matrix,
		glm::value_ptr(actor.transform.position),
		glm::value_ptr(matrixRotation),
		glm::value_ptr(actor.transform.scale)
	);

	// Tools

	offset.x += 8;
	offset.y += 8;
	ImGui::SetCursorPos(offset);
	ImGui::Button("\xEF\x80\x9C", ImVec2(30, 30));
	ImGui::SameLine();
	ImGui::Button(" ", ImVec2(30, 30));

	actor.transform.rotation = glm::quat(glm::radians(matrixRotation));
}
