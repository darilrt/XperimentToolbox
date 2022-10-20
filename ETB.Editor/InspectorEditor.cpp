#include "InspectorEditor.h"
#include "EditorGUI.h"

REGISTER_EDITOR(InspectorEditor);

InspectorEditor::InspectorEditor() {
	title = "Inspector";
}

void InspectorEditor::Start() {

}

void InspectorEditor::GUI() {
	EditorGUI::InputResource("Label", NULL);
}