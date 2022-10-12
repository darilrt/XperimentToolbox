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
		std::string filename = entry.path().filename().string();
		
		if (entry.is_directory()) {
			bool open = ImGui::TreeNodeEx(filename.c_str(), dirFlags);

			if (open) {
				listFiles_impl(path + filename + "/");
				ImGui::TreePop();
			}
		}
		else {
			ImGui::TreeNodeEx(filename.c_str(), dirFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);

			if (ImGui::IsMouseDoubleClicked(ImGuiPopupFlags_MouseButtonLeft) && ImGui::IsItemHovered()) {
				FilesExplorer::OpenFile(entry);
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
