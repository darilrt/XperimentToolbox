#pragma once

#include "EditorCamera.h"
#include "EditorWindow.h"

#include <etb.h>

class EditorApp : public ETB::Application {
public:
	EditorApp();
	~EditorApp();

	void Start();
	void Update();
	void Render();
	void GUI();

	static void Add(Editor::EditorWindow* editor);

	static inline void Focus(Editor::EditorWindow* window) { setFocus = window; }
	static inline ETB::Scene* GetScene() { return EditorApp::currentScene; }
	static inline void SetScene(ETB::Scene* scene) { EditorApp::currentScene = scene; }

private:
	static ETB::Scene* currentScene;
	static std::vector<Editor::EditorWindow*> editors;
	static Editor::EditorWindow* setFocus;

	ETB::Transform transform;
};

