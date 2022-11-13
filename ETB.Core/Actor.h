#pragma once

#include <string>
#include <vector>

#include "etbdefs.h"
#include "Transform.h"
#include "Component.h"

namespace xtb {

	// class Actor with components system

	class Actor {
	public:
		Transform transform;
		std::string name;
		
		DECLSPEC virtual void Start();
		DECLSPEC virtual void Update();
		DECLSPEC virtual void Render();
		DECLSPEC virtual void GUI();
		
		DECLSPEC virtual void InspectorRender();

		DECLSPEC virtual void OnDestroy();

		DECLSPEC void AddComponent(Component* component);
		
		template<typename T>
		T* AddComponent() {
			T* component = new T();
			AddComponent(component);
			return component;
		}

		DECLSPEC void RemoveComponent(Component* component);
		
		template<typename T>
		T* GetComponent() {
			for (int i = 0; i < components.size(); i++) {
				T* component = dynamic_cast<T*>(components[i]);
				if (component != NULL) {
					return component;
				}
			}
			return NULL;
		}
		
		template<typename T>
		std::vector<T*> GetComponents() {
			std::vector<T*> result;
			for (int i = 0; i < components.size(); i++) {
				T* component = dynamic_cast<T*>(components[i]);
				if (component != NULL) {
					result.push_back(component);
				}
			}
			return result;
		}

		inline std::vector<Component*> GetComponents() { return components; }
		
	private:
		std::vector<Component*> components;
	};
}