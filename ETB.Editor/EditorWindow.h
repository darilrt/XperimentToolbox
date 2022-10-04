#pragma once

#include <etb.h>
#include <vector>
#include <iostream>

namespace Editor {
	
	class EditorWindow;

	std::vector<Editor::EditorWindow*>& GetEditors();

	class EditorWindow {
	public:
		bool isOpen;
		std::string title;

		EditorWindow();

		EditorWindow(const std::string& title);

		virtual void Start();
		virtual void GUI();
		virtual void Style();
	};

}