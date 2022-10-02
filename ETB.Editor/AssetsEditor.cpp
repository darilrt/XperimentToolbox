#include "EditorApp.h"
#include "AssetsEditor.h"

AssetsEditor AssetsEditor::assetsEditor;

AssetsEditor::AssetsEditor() {
	EditorApp::Add(this);

	title = "Assets Editor";
}
