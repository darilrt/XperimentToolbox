#pragma once

#include <etb.h>
#include <vector>
#include <iostream>

#define REGISTER_EDITOR(e) \
	Editor::EditorCreator<e> _s_##e##_EditorCreator; \
	e* Editor::Editor<e>::ptr;

namespace Editor {
	
	class EditorWindow;

	template<class T>
	class Editor {
	public:
		static T* ptr;
	};

	class EditorWindow {
	public:
		bool isOpen;
		std::string title;

		EditorWindow();

		virtual void Start();
		virtual void GUI();

		template<class T>
		static void RegistEditor() {
			GetEditors().push_back(Editor<T>::ptr);
		}

		template<class T>
		static T* GetEditor() {
			return Editor<T>::ptr;
		}

		static std::vector<EditorWindow*>& GetEditors() {
			static std::vector<EditorWindow*> editors;
			return editors;
		}

	protected:
		static EditorWindow* editorWindow;
	};

	template<class T>
	class EditorCreator {
	public:
		EditorCreator() {
			if (Editor<T>::ptr == NULL) Editor<T>::ptr = new T;
			EditorWindow::RegistEditor<T>();
		}
	};

}