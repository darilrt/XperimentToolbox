#include <etb.h>

#include "EditorApp.h"

#include "imgui_internal.h"
#include "vendor/ImGuizmo.h"

using namespace xtb;

Scene* EditorApp::currentScene;

EditorApp::EditorApp() : Application("XTB v0.0.1", 1240, 720) {
	window.SetResizable(true);
	window.Maximize();
}

EditorApp::~EditorApp() {
}

void EditorApp::Start() {
	xtb::AssetDatabase::LoadAssets();
	
	for (auto editor : Editor::EditorWindow::GetEditors()) {
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
			ImGui::Separator();
			if (ImGui::MenuItem("Exit")) { Application::Quit(); }
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

		if (ImGui::BeginMenu("Windows")) {

			for (Editor::EditorWindow* editor : Editor::EditorWindow::GetEditors()) {
				if (ImGui::MenuItem(editor->title.c_str())) {
					editor->isOpen = true;
					ImGui::SetWindowFocus(editor->title.c_str());
				}
			}

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
	ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y - ImGui::GetFrameHeight()));
	
	ImGui::SetNextWindowViewport(viewport->ID);

	const ImVec4& color1 = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	const ImVec4& color2 = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	const ImVec4& color3 = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, color1);
	ImGui::Begin("Editor", 0, windowFlags);
	ImGui::PopStyleColor();

	ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_NoWindowMenuButton;
	ImGuiID dockspaceID = ImGui::GetID("Editor");

	if (!ImGui::DockBuilderGetNode(dockspaceID)) {
		ImGui::DockBuilderRemoveNode(dockspaceID);
		ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_None);

		ImGuiID dock_main_id = dockspaceID;

		ImGuiID dock_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
		ImGuiID dock_right_down = ImGui::DockBuilderSplitNode(dock_right, ImGuiDir_Down, 0.7f, nullptr, &dock_right);
		ImGuiID dock_down = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.7f, nullptr, &dock_main_id);
		
		ImGui::DockBuilderDockWindow("Scene", dock_main_id);
		ImGui::DockBuilderDockWindow("Hierarchy", dock_right);
		ImGui::DockBuilderDockWindow("Inspector", dock_right_down);

		ImGui::DockBuilderFinish(dock_main_id);
	}
	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

	for (Editor::EditorWindow* editor : Editor::EditorWindow::GetEditors()) {
		//editor->Style();

		if (editor->isOpen) {
			ImGui::Begin(editor->title.c_str(), &editor->isOpen);
			
			editor->GUI();
			ImGui::End();
		}
	}

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
	float height = ImGui::GetFrameHeight();
	
	if (ImGui::BeginViewportSideBar("##StatusBar", NULL, ImGuiDir_Down, height, window_flags)) {
		if (ImGui::BeginMenuBar()) {
			ImGui::Text("Status bar");
			ImGui::EndMenuBar();
		}
	}
	ImGui::End();

    ImGui::End();
}
