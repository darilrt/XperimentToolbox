#include "Graphics.h"
#include "Mesh.h"
#include "Bounds.h"

xtb::Mesh::Mesh() {
}

xtb::Mesh::~Mesh() {
}

void xtb::Mesh::Setup() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &tbo);
	glGenBuffers(1, &nbo);

	glBindVertexArray(vao);

	// location -> buffer
	// 0 -> Vertex
	// 1 -> UV
	// 2 -> Normal
	// 3 -> Instance Position

	// Vertex Array
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	
	// UV Array
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	// Normal Array
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	// Element Array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(glm::u32vec3), &elements[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	// Calculate Bounds
	Bounds bound;
}

void xtb::Mesh::Bind() {
	glBindVertexArray(vao);
}

void xtb::Mesh::Unbind() {
	glBindVertexArray(NULL);
}