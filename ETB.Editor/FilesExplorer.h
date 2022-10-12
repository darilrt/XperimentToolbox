#pragma once

#include <filesystem>

#include "EditorWindow.h"

class FilesExplorer : public Editor::EditorWindow {
public:
	FilesExplorer();

	void GUI() override;

	static void OpenFile(const std::filesystem::directory_entry &entry);
};