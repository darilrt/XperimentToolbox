#pragma once

#include <filesystem>
#include <iostream>

#include "AssetInspector.h"
#include "EditorWindow.h"

class AssetsEditor : public Editor::EditorWindow {
public:
	AssetsEditor();

	void GUI();

	void OpenByPath(std::filesystem::path path);
	
private:
	std::map<std::string, AssetInspector*> inspectors;
	AssetInspector* currentInspector;
};