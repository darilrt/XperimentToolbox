#pragma once

#include "EditorWindow.h"
#include "EditorCamera.h"

#include <etb.h>

class SceneEditor : public Editor::EditorWindow {
public:
	SceneEditor();
	~SceneEditor();

	void Start();
	void GUI();

private:
	EditorCamera* editorCamera;
	ETB::Scene scene;

	static SceneEditor sceneEditor;
};

