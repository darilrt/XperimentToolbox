#include <etb.h>
#include <imgui_internal.h>

#include "SceneEditor.h"
#include "EditorApp.h"
#include "CubeActor.h"

using namespace ETB;

SceneEditor sceneEditor;

SceneEditor::SceneEditor() {
	EditorApp::Add(this);

	title = "Scene";
}

SceneEditor::~SceneEditor() {
	delete editorCamera;
}

void SceneEditor::Start() {
	EditorApp::SetScene(&scene);

	editorCamera = new EditorCamera();

	editorCamera->Start();
	scene.Start();
}

void SceneEditor::GUI() {
	editorCamera->Update();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	ImGui::Begin(title.c_str(), &isOpen);
	
	EventSystem::ignoreGui = ImGui::IsWindowHovered();

	ImVec2 offset = ImGui::GetWindowContentRegionMin();
	ImVec2 size = ImGui::GetContentRegionAvail();

	editorCamera->SetSize((int32_t)size.x, (int32_t)size.y);
	editorCamera->screenCenter = glm::vec2(offset.x, offset.y) + glm::vec2(size.x, size.y) / 2.0f;

	scene.Render(editorCamera->cam);

	ImGui::Image((void*)(intptr_t)editorCamera->cam.renderTexture.color.GetTextureId(), size, ImVec2(0, 1), ImVec2(1, 0));
	
	ImGui::End();
	ImGui::PopStyleVar();
}
