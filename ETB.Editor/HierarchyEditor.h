#pragma once

#include "EditorWindow.h"
#include "EditorCamera.h"

#include <etb.h>

class HierarchyEditor : public Editor::EditorWindow {
public:
	HierarchyEditor();

	void Start();
	void GUI();

	static xtb::Actor* selectedActor;
};