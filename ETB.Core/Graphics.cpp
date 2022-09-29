#include "Graphics.h"
#include "Debug.h"

void ETB::Graphics::Init() {
	if (glewInit() != GLEW_OK) {
		Debug::Print("Glew Init Error");
	}

	glEnable(GL_MULTISAMPLE);
}

void ETB::Graphics::DrawMesh(Mesh& mesh) {
	mesh.Bind();
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh.elements.size() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(NULL);
}

void ETB::Graphics::DrawMeshInstanced(Mesh& mesh) {
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

void ETB::Graphics::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glAlphaFunc(GL_GREATER, 0.5);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void PrintShaderLog_impl(int32_t shader) {
	if (glIsShader(shader)) {
		int32_t infoLogLength = 0;
		int32_t maxLength = infoLogLength;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		char* infoLog = new char[maxLength];

		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);

		if (infoLogLength > 0) {
			ETB::Debug::Print(infoLog);
		}

		delete[] infoLog;
	}
	else {
		std::string _log = "Name ";
		_log += std::to_string(shader);
		_log += " is not a shader";
		ETB::Debug::Print(_log);
	}
}

uint32_t ETB::Graphics::CreateShader(const std::string* source) {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* vertexShaderSource[] = { 
		"#version 330 core\n#define ETB_VERTEX_SHADER\n", 
		source->c_str()
	};

	glShaderSource(vertexShader, 2, vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);

	if (vShaderCompiled != GL_TRUE) {
		Debug::Print("Unable to compile vertex shader ");
		PrintShaderLog_impl(vertexShader);

		glDeleteShader(vertexShader);
		return 0;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* fragmentShaderSource[] = {
		"#version 330 core\n#define ETB_FRAGMENT_SHADER\n",
		source->c_str()
	};

	glShaderSource(fragmentShader, 2, fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);

	if (fShaderCompiled != GL_TRUE) {
		Debug::Print("Unable to compile fragment shader ");
		PrintShaderLog_impl(fragmentShader);

		glDeleteShader(fragmentShader);
		return 0;
	}

	uint32_t program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}