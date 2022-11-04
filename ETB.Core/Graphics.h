#pragma once

#include <windows.h>

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include <cstdint>
#include <string>

#include "etbdefs.h"
#include "Mesh.h"
#include "Material.h"

namespace xtb {
	namespace Graphics {
		void Init();

		DECLSPEC void DrawMesh(Mesh& mesh);

		DECLSPEC void DrawMesh(Mesh& mesh, glm::mat4 matrix, Material& material);

		DECLSPEC void DrawMeshInstanced(Mesh& mesh);

		DECLSPEC void Clear();
	}
}
