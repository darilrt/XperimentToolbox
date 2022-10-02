#pragma once

#include "EditorWindow.h"
#include "EditorCamera.h"
#include "CubeActor.h"

#include <etb.h>

class SceneEditor : public Editor::EditorWindow {
public:
	SceneEditor();
	~SceneEditor();

	void Start();
	void Style();
	void GUI();

private:
	EditorCamera* editorCamera;
	CubeActor* cubeActor;
	ETB::Scene scene;

	static SceneEditor sceneEditor;
};

