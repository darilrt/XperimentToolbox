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
		DECLSPEC void SetEulerAngles(glm::vec3 rotation);
		
		void Rotate(glm::vec3 rot) { rotation *= glm::quat(rot); }

		DECLSPEC void SetForward(glm::vec3 direction);
		inline glm::vec3 GetForward() { return glm::vec3(0, 0, -1) * rotation; }
	};

}
