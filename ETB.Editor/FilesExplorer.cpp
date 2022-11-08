#include <etb.h>
#include <filesystem>

#include "FilesExplorer.h"
#include "EditorApp.h"
#include "AssetsEditor.h"

REGISTER_EDITOR(FilesExplorer);

FilesExplorer::FilesExplorer() {
	title = "Files Explorer";

	title = "Files Explorer";
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
			const bool open = ImGui::TreeNodeEx(filename.c_str(), dirFlags);

			if (ImGui::BeginPopupContextItem()) {
				if (ImGui::BeginMenu("New")) {
					if (ImGui::MenuItem("Folder")) {
						std::filesystem::create_directories(_path.string() + "/New Folder");
					}

					ImGui::EndMenu();
				}
				
				if (ImGui::MenuItem("Open Folder In Explorer")) {
					const std::string folderPath = std::filesystem::current_path().string() + "/" + _path.string();
					const std::filesystem::path c = std::filesystem::weakly_canonical(std::filesystem::path(folderPath));

					system(("explorer /separate /select,\"" + c.string() + "\"").c_str());
				}

				ImGui::EndPopup();
			}

			if (!open) continue;

			listFiles_impl(path + filename + "/");
			ImGui::TreePop();
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
