#pragma once

#include "etbdefs.h"

#include <glm/glm.hpp>

namespace xtb {

	class Bounds {
	public:
		DECLSPEC Bounds();
		DECLSPEC Bounds(glm::vec3 center, glm::vec3 size);

		bool DECLSPEC Intersect(Bounds& bounds);

		void DECLSPEC SetCenter(glm::vec3 center);
		inline glm::vec3 DECLSPEC GetCenter() { return center; }

		void DECLSPEC SetSize(glm::vec3 size);
		inline glm::vec3 DECLSPEC GetSize() { return size; }

		inline glm::vec3 DECLSPEC GetMin() { return min; }

		inline glm::vec3 DECLSPEC GetMax() { return max; }

		void DECLSPEC SetExtends(glm::vec3 extends);
		inline glm::vec3 DECLSPEC GetExtends() { return extends; }

		DECLSPEC void Expand(glm::vec3 point);

	private:
		glm::vec3 center;
		glm::vec3 size;
		glm::vec3 extends;
		glm::vec3 min;
		glm::vec3 max;
	};

}
