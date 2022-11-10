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
				std::filesystem::create_directories(path.string() + "/New Folder");
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
			ImGui::EndPopup();
			return;
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
		xtb::AssetDatabase::Rename(path, path.parent_path().string() + "/" + buffer + ext);
	}
}

void listFiles_impl(const std::string& path) {
	static ImGuiTreeNodeFlags dirFlags = ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick | 
		ImGuiTreeNodeFlags_SpanFullWidth;
	
	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
		const std::filesystem::path _path = entry.path();

		const std::string filename = _path.filename().string();
		
		if (_path.extension().string() == ".meta") {
			continue;
		}

		if (entry.is_directory()) {
			if (_path.compare(renamePath) == 0) {
				renameFileOrFolder_impl(_path);
			}
			else {
				const bool open = ImGui::TreeNodeEx(filename.c_str(), dirFlags);

				contextMenu_helper(_path);

				if (open) {
					listFiles_impl(path + filename + "/");
					ImGui::TreePop();
				}
			}
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
	}
}

void FilesExplorer::GUI() {
	std::string assetsPath = "Built-In/";
	
	listFiles_impl(assetsPath);
}

void FilesExplorer::OpenFile(const std::filesystem::directory_entry& entry) {
	std::filesystem::path path = entry.path();

	if (path.has_extension()) {
		AssetsEditor* assetsEditor = Editor::EditorWindow::GetEditor<AssetsEditor>();
		assetsEditor->isOpen = true;
		assetsEditor->OpenByPath(path);
	}
}
