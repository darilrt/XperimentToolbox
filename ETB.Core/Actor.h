#pragma once

#include "etbdefs.h"

namespace ETB {

	class Actor {
	public:
		virtual DECLSPEC void Start();
		virtual DECLSPEC void Update();
		virtual DECLSPEC void Render();
		virtual DECLSPEC void GUI();

		virtual DECLSPEC void OnDestroy();
	};

}