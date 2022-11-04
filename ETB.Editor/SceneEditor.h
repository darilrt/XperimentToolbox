#pragma once

#include "EditorWindow.h"
#include "EditorCamera.h"
#include "CubeActor.h"

#include <etb.h>

class SceneEditor : public Editor::EditorWindow {
public:
	EditorCamera* editorCamera;

	SceneEditor();
	~SceneEditor();

	void Start();
	void GUI();

private:
	CubeActor* cubeActor;
	ETB::Scene scene;
};