#pragma once

#include "etbdefs.h"

#include <glm/glm.hpp>
#include <vector>

namespace ETB {
	
	class Mesh {
	public:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uv;
		std::vector<glm::u32vec3> elements;
		
		DECLSPEC Mesh();
		DECLSPEC ~Mesh();

		DECLSPEC void Setup();

		DECLSPEC void Bind();
		DECLSPEC void Unbind();

	private:
		uint32_t vao; // Vertex Array
		uint32_t vbo; // Vertex Buffer
		uint32_t nbo; // Normal Buffer
		uint32_t tbo; // Texture Buffer
		uint32_t ebo; // Element Buffer
	};

}
