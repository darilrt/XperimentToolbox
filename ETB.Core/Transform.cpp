#include "Transform.h"

ETB::Transform::Transform() : position(0, 0, 0), rotation(glm::vec3(0.0f, 0.0f, 0.0f)), scale(1.0f, 1.0f, 1.0f) {
}

glm::mat4 ETB::Transform::GetTransformMatrix() {
	glm::mat4 matrix;

	matrix = glm::translate(glm::mat4(1.0f), position);
	matrix *= glm::mat4_cast(rotation);
	matrix = glm::scale(matrix, scale);

	return matrix;
}
