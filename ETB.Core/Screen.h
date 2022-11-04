#pragma once

#include "etbdefs.h"
#include "Window.h"

#include <glm/glm.hpp>
#include <cstdint>

namespace xtb {

	class Screen {
	public:
		static inline glm::ivec2 GetSize() { return Core::Window::GetActive()->GetSize(); }
	};

}