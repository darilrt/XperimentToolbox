#include "Camera.h"
#include "Graphics.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>

ETB::Camera* ETB::Camera::activeCamera;

ETB::Camera::Camera() : position(0), rotation(glm::vec3(0.0f)) {
}

void ETB::Camera::SetPerspective(float fovy, float aspect, float zNear, float zFar) {
	projectionMatrix = glm::perspective(fovy, aspect, zNear, zFar);
}

void ETB::Camera::Use() {
	Camera::activeCamera = this;

	Graphics::Clear();

	viewMatrix = glm::translate(glm::mat4(1.0), position) * glm::mat4_cast(rotation);
}

glm::mat4 ETB::Camera::GetMatrix() {
	return projectionMatrix * viewMatrix;
}

void ETB::Camera::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
	glViewport(x, y, width, height);
}