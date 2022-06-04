#include "Camera.h"
#include "Graphics.h"

ETB::Camera* ETB::Camera::activeCamera = nullptr;

void ETB::Camera::SetActive(Camera* camera) {
	Camera::activeCamera = camera;
}

ETB::Camera::Camera() : transform() {
}

void ETB::Camera::SetPerspective(float fovy, float aspect, float zNear, float zFar) {
	projectionMatrix = glm::perspective(fovy, aspect, zNear, zFar);
}

void ETB::Camera::Use() {
	Camera::activeCamera = this;

	Graphics::Clear();

	viewMatrix = glm::mat4_cast(transform.rotation);
	viewMatrix = glm::translate(viewMatrix, -transform.position);
	viewMatrix = glm::scale(viewMatrix, transform.scale);
}

glm::mat4 ETB::Camera::GetMatrix() {
	return projectionMatrix * viewMatrix;
}

void ETB::Camera::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
	glViewport(x, y, width, height);
}