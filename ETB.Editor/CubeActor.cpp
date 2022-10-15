#include "CubeActor.h"

#include <etb.h>

using namespace ETB;

static Mesh sph;
static Material mat;

void CubeActor::Start() {
	sph = OBJLoader::FromFile("Built-In/Models/sphere_inverse_normals.obj");
	sph.Setup();

	mat.LoadFromFile("Built-In/Materials/skyBox.mat");
	material.LoadFromFile("Built-In/Materials/test.mat");
}

void CubeActor::Render() {
	transform.scale = { 50.0f, 50.0f, 50.0f };
	//Graphics::DrawMesh(sph, transform.GetMatrix(), mat);

	transform.scale = { 1.0, 1.0f, 1.0f };
	Graphics::DrawMesh(Primitives::cube, transform.GetMatrix(), material);
}

void CubeActor::GUI() {
}
