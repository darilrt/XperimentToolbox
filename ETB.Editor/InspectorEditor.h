#pragma once

#include "EditorWindow.h"
#include "HierarchyEditor.h"

#include <etb.h>

class InspectorEditor : public Editor::EditorWindow {
public:
	InspectorEditor();

	void Start();
	void GUI();
};