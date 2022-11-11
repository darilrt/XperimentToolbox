#include <etb.h>
#include <filesystem>
#include <imgui.h>
#include <imgui_internal.h>

#include "FilesExplorer.h"
#include "EditorApp.h"
#include "AssetsEditor.h"

REGISTER_EDITOR(FilesExplorer);

FilesExplorer::FilesExplorer() {
	title = "Files Explorer";
}

static std::filesystem::path renamePath;

void contextMenu_helper(std::filesystem::path path) {
	if (ImGui::BeginPopupContextItem()) {
		if (ImGui::BeginMenu("New")) {
			if (ImGui::MenuItem("Folder")) {
				if (std::filesystem::is_regular_file(path)) {
					path = path.parent_path();
				}

				std::filesystem::create_directory(path / "New Folder");
				renamePath = path / "New Folder";
			}

			ImGui::EndMenu();
		}
		
		if (ImGui::MenuItem("Rename")) {
			ImGui::SetItemDefaultFocus();
			renamePath = path;
			ImGui::SetKeyboardFocusHere(-1);
		}

		if (ImGui::MenuItem("Delete")) {
			std::filesystem::remove(path);
		}

		if (ImGui::MenuItem("Open Folder In Explorer")) {
			const std::string folderPath = std::filesystem::current_path().string() + "/" + path.parent_path().string();
			const std::filesystem::path c = std::filesystem::weakly_canonical(std::filesystem::path(folderPath));

			system(("explorer /separate /select,\"" + c.string() + "\"").c_str());
		}

		ImGui::EndPopup();
	}
}

void renameFileOrFolder_impl(std::filesystem::path path) {
	static std::string ext;
	static char buffer[256];
	
	if (std::filesystem::is_directory(path)) {
		strcpy_s(buffer, path.filename().string().c_str());
		ext = "";
	}
	else {
		strcpy_s(buffer, path.stem().string().c_str());
		ext = path.extension().string();
	}
	
	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
	
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(28, 0));
	
	ImGui::SetKeyboardFocusHere(0);
	
	ImGui::InputText("Hello", buffer, 256, ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	
	ImGui::PopItemWidth();
	
	if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape))) {
		renamePath = "";
	}

	if (ImGui::IsAnyMouseDown() && !ImGui::IsItemHovered()) {
		renamePath = "";
	}

	if (ImGui::IsItemDeactivatedAfterEdit()) {
		ImGui::SetActiveID(NULL, ImGui::GetCurrentWindow());
		ImGui::SetKeyboardFocusHere(-1);
		renamePath = "";

		if (!std::filesystem::exists(path.parent_path() / (std::string(buffer) + ext))) {
			xtb::AssetDatabase::Rename(path, path.parent_path().string() + "/" + buffer + ext);
		}
	}
}

void listFiles_impl(const std::string& path, bool onlyAssetFolder=false) {
	static ImGuiTreeNodeFlags dirFlags = ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick | 
		ImGuiTreeNodeFlags_SpanFullWidth;
	
	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
		const std::filesystem::path _path = entry.path();
		const std::string filename = _path.filename().string();

		if (onlyAssetFolder && filename != "Built-In" && filename != "Assets") {
			continue;
		}

		if (_path.extension().string() == ".meta") {
			continue;
		}

		if (!entry.exists()) {
			continue;
		}

		bool open = false;

		if (_path.compare(renamePath) == 0) {
			renameFileOrFolder_impl(_path);
		}
		else if (entry.is_directory()) {
			open = ImGui::TreeNodeEx(filename.c_str(), dirFlags);
		}
		else {
			ImGui::TreeNodeEx(filename.c_str(), dirFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);

			if (ImGui::IsMouseDoubleClicked(ImGuiPopupFlags_MouseButtonLeft) && ImGui::IsItemHovered()) {
				FilesExplorer::OpenFile(entry);
			}

			const std::string uuid = xtb::AssetDatabase::GetUUIDByPath(_path.string());
			
			if (uuid != "" && ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
				xtb::Asset* asset = xtb::AssetDatabase::GetAssetByUUID(uuid);
				const std::string typeName(asset->GetTypeName());
				const std::string payloadID = ("XTBASSET" + typeName);
				
				ImGui::SetDragDropPayload(payloadID.c_str(), asset, sizeof(xtb::Asset), ImGuiCond_Once);
				
				ImGui::Text(filename.c_str());
				
				ImGui::EndDragDropSource();
			}
		}
		
		contextMenu_helper(_path);

		if (entry.is_directory() && open) {
			listFiles_impl(path + filename + "/");
			ImGui::TreePop();
		}
	}
}

void FilesExplorer::GUI() {
	std::string assetsPath = "Built-In/";
	
	listFiles_impl("./", true);
}

void FilesExplorer::OpenFile(const std::filesystem::directory_entry& entry) {
	std::filesystem::path path = entry.path();

	if (path.has_extension()) {
		AssetsEditor* assetsEditor = Editor::EditorWindow::GetEditor<AssetsEditor>();
		assetsEditor->isOpen = true;
		assetsEditor->OpenByPath(path);
	}
}
