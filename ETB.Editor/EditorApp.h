#pragma once

#include <etb.h>

#include "EditorCamera.h"
#include "EditorWindow.h"

class EditorApp : public ETB::Application {
public:
	EditorApp();
	~EditorApp();

	void Start();
	void Update();
	void Render();
	void GUI();

	static inline ETB::Scene* GetScene() { return EditorApp::currentScene; }
	static inline void SetScene(ETB::Scene* scene) { EditorApp::currentScene = scene; }

private:
	static ETB::Scene* currentScene;

	ETB::Transform transform;
};

