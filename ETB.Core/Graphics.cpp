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
	glBindVertexArray(0);
}

void ETB::Graphics::DrawMeshInstanced(Mesh& mesh) {

}

void ETB::Graphics::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(45, 1, 0.1, 100);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glAlphaFunc(GL_GREATER, 0.5);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void PrintShaderLog(int32_t shader) {
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
		PrintShaderLog(vertexShader);

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
		PrintShaderLog(fragmentShader);

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