#pragma once

#include "etbdefs.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ETB {

	class Transform {
	public:
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DECLSPEC Transform();

		DECLSPEC glm::mat4 GetMatrix();
		
		glm::vec3 GetEulerAngles() { return glm::eulerAngles(rotation); }
		void SetEulerAngles(glm::vec3 rot) { rotation = glm::quat(rot); }
		void Rotate(glm::vec3 rot) { rotation *= glm::quat(rot); }
	};

}
