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
			if (!ImGui::TreeNodeEx(filename.c_str(), dirFlags)) continue;

			listFiles_impl(path + filename + "/");
			ImGui::TreePop();
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
