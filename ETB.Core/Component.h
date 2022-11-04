#pragma once

#include "etbdefs.h"

namespace xtb {

	class Actor;

	class Component {
	public:

		DECLSPEC virtual void Start();
		DECLSPEC virtual void Update();
		DECLSPEC virtual void Render();
		DECLSPEC virtual void GUI();

		DECLSPEC virtual void OnDestroy();
		
		inline Actor* GetActor() { return actor; }
		inline void SetActor(Actor* a) { actor = a; }

	private:
		Actor* actor;
	};

}

