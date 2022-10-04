#pragma once

#include "EditorApp.h"
#include "EditorWindow.h"

class AssetsEditor : public Editor::EditorWindow {
public:
	static AssetsEditor assetsEditor;

	AssetsEditor();
	
	void Start();
	void GUI();
	void Style();
};