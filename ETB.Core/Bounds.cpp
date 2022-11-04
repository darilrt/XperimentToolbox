#include "Bounds.h"

xtb::Bounds::Bounds() {
}

xtb::Bounds::Bounds(glm::vec3 c, glm::vec3 s) {
	SetCenter(c);
	SetSize(s);
}

bool xtb::Bounds::Intersect(Bounds& b) {
	return	(min.x <= b.max.x && max.x >= b.min.x) &&
		(min.y <= b.max.y && max.y >= b.min.y) &&
		(min.z <= b.max.z && max.z >= b.min.z);
}

void xtb::Bounds::SetCenter(glm::vec3 c) {
	center = c;

	extends = size / 2.0f;
	min = center - extends;
	max = center + extends;
}

void xtb::Bounds::SetSize(glm::vec3 s) {
	size = s;

	extends = size / 2.0f;
	min = center - extends;
	max = center + extends;
}

void xtb::Bounds::SetExtends(glm::vec3 e) {
	extends = e;

	size = extends * 2.0f;
	min = center - extends;
	max = center + extends;
}

void xtb::Bounds::Expand(glm::vec3 p) {
	min.x = min.x > p.x ? p.x : min.x;
	min.y = min.y > p.y ? p.y : min.y;
	min.z = min.z > p.z ? p.z : min.z;

	max.x = max.x > p.x ? p.x : max.x;
	max.y = max.y > p.y ? p.y : max.y;
	max.z = max.z > p.z ? p.z : max.z;

	center = (min + max) / 2.0f;
	size = max - min;
	extends = size / 2.0f;
}
