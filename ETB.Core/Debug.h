#pragma once

#include "etbdefs.h"
#include "Transform.h"

#include <string>

namespace ETB {
	namespace Debug {
		
		void DECLSPEC Print(const std::string& message);

		void DECLSPEC TransformEditor(Transform& transform);

		void DECLSPEC ShowStatus();

	}
}
