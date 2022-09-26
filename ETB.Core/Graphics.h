#pragma once

#include <windows.h>

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cstdint>
#include <string>

#include "etbdefs.h"
#include "Mesh.h"

namespace ETB {
	namespace Graphics {
		void Init();

		DECLSPEC void DrawMesh(Mesh& mesh);

		DECLSPEC void DrawMeshInstanced(Mesh& mesh);

		DECLSPEC void Clear();
		
		DECLSPEC uint32_t CreateShader(const std::string* source);
		
	}
}
