#pragma once

#include <string>

#include "etbdefs.h"
#include "Transform.h"

namespace xtb {
	namespace Debug {
		
		void DECLSPEC Print(const std::string& message);

		void DECLSPEC TransformEditor(Transform& transform);

		void DECLSPEC ShowStatus();

	}
}
