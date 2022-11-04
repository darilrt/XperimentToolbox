#include "Camera.h"
#include "Graphics.h"
#include "RenderTexture.h"

xtb::Camera* xtb::Camera::activeCamera = nullptr;

void xtb::Camera::SetActive(Camera* camera) {
	Camera::activeCamera = camera;
}

xtb::Camera::Camera() : transform(), renderTexture(800, 600) {
}

xtb::Camera::Camera(int32_t width, int32_t height) : transform(), renderTexture(width, height) {
}

xtb::Camera::~Camera() {
}

void xtb::Camera::SetPerspective(float fovy, float aspect, float zNear, float zFar) {
	projectionMatrix = glm::perspective(fovy, aspect, zNear, zFar);
}

void xtb::Camera::Use() {
	Camera::activeCamera = this;

	Graphics::Clear();

	viewMatrix = glm::mat4_cast(transform.rotation);
	viewMatrix = glm::translate(viewMatrix, -transform.position);
	viewMatrix = glm::scale(viewMatrix, transform.scale);
}

glm::mat4 xtb::Camera::GetMatrix() {
	return projectionMatrix * viewMatrix;
}

void xtb::Camera::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height) {
	glViewport(x, y, width, height);
	renderTexture.SetSize(width, height);
}