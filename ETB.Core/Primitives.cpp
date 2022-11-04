#include "Primitives.h"
#include "EventSystem.h"
#include "OBJLoader.h"

xtb::Mesh xtb::Primitives::quad;
xtb::Mesh xtb::Primitives::cube;
xtb::Mesh xtb::Primitives::sphere;

xtb::Primitives xtb::Primitives::instance;

xtb::Primitives::Primitives() {
	EventSystem::AddEventListener(EventType::Start, [&](Event& e) {
		Primitives::GeneratePrimitives();
	});
}

void xtb::Primitives::GeneratePrimitives() {
	Primitives::quad.vertices = {
		{-.5f, -.5f, 0},
		{-.5f,  .5f, 0},
		{ .5f, -.5f, 0},
		{ .5f,  .5f, 0},
	};
	Primitives::quad.normals = {
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
	};
	Primitives::quad.uv = {
		{0, 0},
		{0, 1},
		{1, 0},
		{1, 1},
	};
	Primitives::quad.elements = {
		{1, 0, 2},
		{1, 2, 3}
	};

	Primitives::quad.Setup();

	// Cube
	Primitives::cube = OBJLoader::FromFile("Built-In/Models/Cube.obj");
	Primitives::cube.Setup();

	// Sphere
	Primitives::sphere = OBJLoader::FromFile("Built-In/Models/Sphere.obj");
	Primitives::sphere.Setup();
}
