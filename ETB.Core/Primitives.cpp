#include "Primitives.h"
#include "EventSystem.h"
#include "OBJLoader.h"

ETB::Mesh ETB::Primitives::quad;
ETB::Mesh ETB::Primitives::cube;

ETB::Primitives ETB::Primitives::instance;

ETB::Primitives::Primitives() {
	EventSystem::AddEventListener(EventType::Start, [&](Event& e) {
		Primitives::GeneratePrimitives();
	});
}

void ETB::Primitives::GeneratePrimitives() {
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
		{0, 1},
		{0, 0},
		{1, 1},
		{1, 0},
	};
	Primitives::quad.elements = {
		{1, 0, 2},
		{1, 2, 3}
	};

	Primitives::quad.SetupMesh();

	// Cube
	Primitives::cube = OBJLoader::FromFile("Build-In/Models/Cube.obj");
	Primitives::cube.SetupMesh();
}
