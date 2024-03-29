#pragma once

#include "etbdefs.h"
#include "Transform.h"
#include "RenderTexture.h"

#include <glm/glm.hpp>

namespace xtb {

	class Camera {
	public:
		Transform transform;
		RenderTexture renderTexture;
		
		DECLSPEC Camera();
		DECLSPEC Camera(int32_t width, int32_t height);
		DECLSPEC ~Camera();
		DECLSPEC void SetPerspective(float fovy, float aspect, float zNear, float zFar);

		DECLSPEC void Use();

		inline glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
		inline glm::mat4 GetViewMatrix() { return viewMatrix; }

		DECLSPEC glm::mat4 GetMatrix();

		DECLSPEC void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);
		
		static DECLSPEC void SetActive(Camera* camera);
		static inline Camera* GetActive() { return Camera::activeCamera; }

	private:
		static DECLSPEC Camera* activeCamera;

		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
	};

}
