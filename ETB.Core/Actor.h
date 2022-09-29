#pragma once

#include <string>

#include "etbdefs.h"
#include "Transform.h"

namespace ETB {

	class Actor {
	public:
		Transform transform;
		std::string name;

		DECLSPEC virtual void Start();
		DECLSPEC virtual void Update();
		DECLSPEC virtual void Render();
		DECLSPEC virtual void GUI();

		DECLSPEC virtual void OnDestroy();
	};

}