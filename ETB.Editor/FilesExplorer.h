#pragma once

#include <filesystem>

#include "EditorWindow.h"

class FilesExplorer : public Editor::EditorWindow {
public:
	static FilesExplorer filesExplorer;

	FilesExplorer();

	void GUI() override;

	static void OpenFile(const std::filesystem::directory_entry &entry);
};
