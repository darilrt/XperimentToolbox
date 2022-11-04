#pragma once

#include <etb.h>

#include "EditorCamera.h"
#include "EditorWindow.h"

class EditorApp : public xtb::Application {
public:
	EditorApp();
	~EditorApp();

	void Start();
	void Update();
	void Render();
	void GUI();

	static inline void Focus(Editor::EditorWindow* window) { setFocus = window; }
	static inline xtb::Scene* GetScene() { return EditorApp::currentScene; }
	static inline void SetScene(xtb::Scene* scene) { EditorApp::currentScene = scene; }

private:
	static xtb::Scene* currentScene;
	static std::vector<Editor::EditorWindow*> editors;
	static Editor::EditorWindow* setFocus;

	xtb::Transform transform;
};

