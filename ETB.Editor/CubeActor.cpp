#include "CubeActor.h"

#include <etb.h>

using namespace ETB;

void CubeActor::Start() {
	ShaderLoader::Add("Built-In/Shaders/Test.glsl");
}

void CubeActor::Render() {
	Shader& sh = ShaderLoader::Get("Built-In/Shaders/Test.glsl");

	sh.Use();
	sh.SetMatrix("ETB_MATRIX_VP", Camera::GetActive()->GetMatrix());
	sh.SetMatrix("ETB_MATRIX_M", transform.GetTransformMatrix());

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();

	Graphics::DrawMesh(Primitives::cube);
}
