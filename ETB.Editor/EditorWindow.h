#pragma once

#include <etb.h>

namespace Editor {

	class EditorWindow {
	public:
		bool isOpen;
		std::string title;

		EditorWindow();

		virtual void Start();
		virtual void GUI();
	};

}