#pragma once

#include "etbdefs.h"

#include <string>

namespace ETB {

	class Actor {
	public:
		std::string name;

		DECLSPEC virtual void Start();
		DECLSPEC virtual void Update();
		DECLSPEC virtual void Render();
		DECLSPEC virtual void GUI();

		DECLSPEC virtual void OnDestroy();
	};

}