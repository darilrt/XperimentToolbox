#pragma once

#include <string>
#include <vector>

#include "etbdefs.h"
#include "Transform.h"
#include "Component.h"

namespace xtb {

	class Actor {
	public:
		Transform transform;
		std::string name;

		DECLSPEC virtual void Start();
		DECLSPEC virtual void Update();
		DECLSPEC virtual void Render();
		DECLSPEC virtual void GUI();

		DECLSPEC virtual void OnDestroy();

		template<class T>
		T* GetComponent() {
			return dynamic_cast<T>(std::find(
				std::begin(components),
				std::end(components),
				[](Component c) {return dynamic_cast<T>(c) != NULL; }
			));
		}

	private:
		std::vector<Component> components;
	};

}