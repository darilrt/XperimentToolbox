#include "Graphics.h"
#include "Debug.h"
#include "Camera.h"
#include "ShaderLoader.h"

void xtb::Graphics::Init() {
	if (glewInit() != GLEW_OK) {
		Debug::Print("Glew Init Error");
	}

	glEnable(GL_MULTISAMPLE);
}

void xtb::Graphics::DrawMesh(Mesh& mesh, glm::mat4 matrix, Material& material) {
	Shader* shader;
	
	if (material.shader == NULL || material.shader->GetId() == 0) {
		shader = &ShaderLoader::Get("Built-In/Shaders/ErrorShader.gl");
	}
	else {
		shader = material.shader;
	}

	shader->Bind();
	
	shader->SetMatrix("ETB_MATRIX_M", matrix);
	shader->SetMatrix("ETB_MATRIX_VP", Camera::GetActive()->GetMatrix());

	material.Use();

	DrawMesh(mesh);
	shader->Unbind();
}

void xtb::Graphics::DrawMesh(Mesh& mesh) {
	mesh.Bind();
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh.elements.size() * 3, GL_UNSIGNED_INT, 0);
	mesh.Unbind();
}

void xtb::Graphics::DrawMeshInstanced(Mesh& mesh) {
	/*
	mesh.Bind();

	glBindBuffer(GL_ARRAY_BUFFER, VBO_containing_matrices);
	glBufferSubData(GL_ARRAY_BUFFER, 0, particle_count * sizeof(GLfloat) * 4, g_particle_data);

	glEnableVertexAttribArray(pos1);
	glEnableVertexAttribArray(pos2);
	glEnableVertexAttribArray(pos3);
	glEnableVertexAttribArray(pos4);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_containing_matrices);
	glVertexAttribPointer(pos1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(0));
	glVertexAttribPointer(pos2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 4));
	glVertexAttribPointer(pos3, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 8));
	glVertexAttribPointer(pos4, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 12));
	glVertexAttribDivisor(pos1, 1);
	glVertexAttribDivisor(pos2, 1);
	glVertexAttribDivisor(pos3, 1);
	glVertexAttribDivisor(pos4, 1);

	glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh.elements.size() * 3, GL_UNSIGNED_INT, 0, 10);
	glBindVertexArray(NULL);
	*/
}

void xtb::Graphics::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glAlphaFunc(GL_GREATER, 0.5);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
