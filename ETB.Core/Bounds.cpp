#include "Bounds.h"

ETB::Bounds::Bounds() {
}

ETB::Bounds::Bounds(glm::vec3 c, glm::vec3 s) {
	SetCenter(c);
	SetSize(s);
}

bool ETB::Bounds::Intersect(Bounds& b) {
	return	(min.x <= b.max.x && max.x >= b.min.x) &&
		(min.y <= b.max.y && max.y >= b.min.y) &&
		(min.z <= b.max.z && max.z >= b.min.z);
}

void ETB::Bounds::SetCenter(glm::vec3 c) {
	center = c;

	extends = size / 2.0f;
	min = center - extends;
	max = center + extends;
}

void ETB::Bounds::SetSize(glm::vec3 s) {
	size = s;

	extends = size / 2.0f;
	min = center - extends;
	max = center + extends;
}

void ETB::Bounds::SetExtends(glm::vec3 e) {
	extends = e;

	size = extends * 2.0f;
	min = center - extends;
	max = center + extends;
}
