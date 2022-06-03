#pragma once

#include "etbdefs.h"
#include "Transform.h"

#include <glm/glm.hpp>

namespace ETB {

	class Camera {
	public:
		static DECLSPEC Camera* activeCamera;

		static DECLSPEC void SetActive(Camera* camera);

		Transform transform;

		DECLSPEC Camera();
		DECLSPEC void SetPerspective(float fovy, float aspect, float zNear, float zFar);

		DECLSPEC void Use();

		DECLSPEC glm::mat4 GetMatrix();

		DECLSPEC void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);

	private:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
	};

}
