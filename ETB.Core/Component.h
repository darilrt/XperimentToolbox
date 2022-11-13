#pragma once

#include <iostream>

#include "etbdefs.h"
#include "Transform.h"

namespace xtb {
	class Actor;
	
	class Component {
	public:
		DECLSPEC virtual void Start();
		DECLSPEC virtual void Update();
		DECLSPEC virtual void Render();

		DECLSPEC virtual void InspectorRender();

		DECLSPEC virtual void OnDestroy();
		
		inline Actor* GetActor() { return actor; }
		inline void SetActor(Actor* a) { actor = a; }
		
		inline Actor* GetParent() { return actor; }
		inline std::string GetName() { return name; }

	protected:
		std::string name;
		
	private:
		Actor* actor;
	};

}

