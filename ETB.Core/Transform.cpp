#include "Transform.h"
#include "glm/gtx/quaternion.hpp"

ETB::Transform::Transform() : position(0, 0, 0), rotation(glm::vec3(0.0f, 0.0f, 0.0f)), scale(1.0f, 1.0f, 1.0f) {
}

glm::mat4 ETB::Transform::GetMatrix() {
	glm::mat4 matrix;

	matrix = glm::translate(glm::mat4(1.0f), position);
	matrix *= glm::mat4_cast(rotation);
	matrix = glm::scale(matrix, scale);

	return matrix;
}

void ETB::Transform::SetEulerAngles(glm::vec3 r) {
	glm::quat rotX = glm::quat(glm::vec3(r.x, 0.0f, 0.0f));
	glm::quat rotY = glm::quat(glm::vec3(0.0f, r.y, 0.0f));
	glm::quat rotZ = glm::quat(glm::vec3(0.0f, 0.0f, r.z));

	rotation = rotX;
	rotation *= rotY;
	rotation *= rotZ;
}

void ETB::Transform::SetForward(glm::vec3 target) {
	rotation = glm::conjugate(glm::toQuat(glm::lookAt(position, target, glm::vec3(0, 0, 0))));
}

void ETB::Transform::LookAt(glm::vec3& targetPosition, glm::vec3 upVector) {
	rotation = glm::lookAt(position, targetPosition, upVector);
}
