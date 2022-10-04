#include <iostream>

#include "EditorWindow.h"

std::vector<Editor::EditorWindow*> editors;

std::vector<Editor::EditorWindow*>& Editor::GetEditors() {
    return editors;
}

Editor::EditorWindow::EditorWindow() : title(""), isOpen(false) {
    editors.push_back(this);
}

Editor::EditorWindow::EditorWindow(const std::string& _title) : title(_title), isOpen(false) {
    editors.push_back(this);
}

void Editor::EditorWindow::Start() {
}

void Editor::EditorWindow::GUI() {
}

void Editor::EditorWindow::Style() {
}