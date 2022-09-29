#include "CubeActor.h"

#include <etb.h>

using namespace ETB;

void CubeActor::Start() {
	ShaderLoader::Add("Built-In/Shaders/Test.glsl");
}

void CubeActor::Render() {
	Shader& sh = ShaderLoader::Get("Built-In/Shaders/Test.glsl");

	sh.Bind();
	sh.SetMatrix("ETB_MATRIX_VP", Camera::GetActive()->GetMatrix());
	sh.SetMatrix("ETB_MATRIX_M", transform.GetMatrix());

	Graphics::DrawMesh(Primitives::cube);

	sh.Unbind();
}

void CubeActor::GUI() {

}
