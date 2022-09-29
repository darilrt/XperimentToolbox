#include "EditorApp.h"

#include "imgui_internal.h"
#include "vendor/ImGuizmo.h"

using namespace ETB;

Scene* EditorApp::currentScene;
std::vector<Editor::EditorWindow*> EditorApp::editors;

EditorApp::EditorApp() : Application("Editor", 1240, 720) {
	window.SetVSync(Core::VSyncMode::On);
	window.SetResizable(true);
	window.Maximize();
}

EditorApp::~EditorApp() {
}

void EditorApp::Start() {
	for (auto editor : EditorApp::editors) {
		editor->isOpen = true;
		editor->Start();
	}
}

void EditorApp::Update() {
}

void EditorApp::Render() {
}

void EditorApp::GUI() {
	ImGuizmo::BeginFrame();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

	ImGuiWindowFlags windowFlags =
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::Begin("Editor", 0, windowFlags);

	ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
	ImGuiID dockspaceID = ImGui::GetID("Editor");

	if (!ImGui::DockBuilderGetNode(dockspaceID)) {
		ImGui::DockBuilderRemoveNode(dockspaceID);
		ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_None);

		ImGuiID dock_main_id = dockspaceID;

		ImGuiID dock_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
		ImGuiID dock_right_down = ImGui::DockBuilderSplitNode(dock_right, ImGuiDir_Down, 0.7f, nullptr, &dock_right);
		
		ImGui::DockBuilderDockWindow("Scene", dock_main_id);
		ImGui::DockBuilderDockWindow("Hierarchy", dock_right);
		ImGui::DockBuilderDockWindow("Inspector", dock_right_down);

		ImGui::DockBuilderFinish(dock_main_id);
	}
	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

	for (auto editor : EditorApp::editors) {
		editor->GUI();
	}

	ImGui::Begin("Inspector"); ImGui::End();

    ImGui::End();
}

void EditorApp::Add(Editor::EditorWindow* editor) {
	EditorApp::editors.push_back(editor);
}
