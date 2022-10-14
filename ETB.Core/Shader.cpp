#include <string>
#include <vector>

#include "Debug.h"
#include "File.h"
#include "Shader.h"
#include "Uniform.h"
#include "Camera.h"
#include "EventSystem.h"

ETB::Shader::Shader() {
	shaderId = NULL;
}

ETB::Shader::Shader(const std::string& _path) {
	shaderId = NULL;

	path = _path;

	LoadSources();
}

ETB::Shader::~Shader() {
	glDeleteProgram(shaderId);
}

void ETB::Shader::Bind() {
	glUseProgram(shaderId);
	samplerCount = 0;
}

std::vector<ETB::Uniform> ETB::Shader::GetUniforms() {
	std::vector<Uniform> uniforms;
	
	if (shaderId == NULL) {
		Debug::Print("Trying to get uniforms on an uncompiled shader");
		return uniforms;
	}

	// Get count of uniforms in the shader
	GLint count;
	glGetProgramiv(shaderId, GL_ACTIVE_UNIFORMS, &count);

	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 32; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length
	Uniform::Type ctype = Uniform::Unknow;

	for (int32_t i = 0; i < count; i++) {
		glGetActiveUniform(shaderId, (GLuint)i, bufSize, &length, &size, &type, name);
		
		switch (type) {
		case GL_INT: ctype = Uniform::Int; break;
		case GL_FLOAT: ctype = Uniform::Float; break;
		case GL_FLOAT_VEC2: ctype = Uniform::Vector2; break;
		case GL_FLOAT_VEC3: ctype = Uniform::Vector3; break;
		case GL_FLOAT_VEC4: ctype = Uniform::Vector4; break;
		case GL_FLOAT_MAT4: ctype = Uniform::Matrix4; break;
		case GL_SAMPLER_2D: ctype = Uniform::Sampler2D; break;
		default: break;
		}

		uniforms.push_back(Uniform(std::string(name), ctype));
	}

	return uniforms;
}

void ETB::Shader::LoadSources() {
	if (!File::Exists(path)) {
		Debug::Print("Shader \"" + path + "\" does not exists");
		return;
	}
	
	source = File::ReadAll(path);
}

bool ETB::Shader::Compile() {
	shaderId = CreateShader(&source);
	source.clear();
	return shaderId != 0;
}

void ETB::Shader::Reload() {
	struct stat fileInfo;
	stat(path.c_str(), &fileInfo);

	if (srcMTime != fileInfo.st_mtime) {
		srcMTime = fileInfo.st_mtime;

		Debug::Print("--------------------------------------");
		Debug::Print("Shader hot reload \"" + path + "\"");

		Debug::Print("Loading sources");
		LoadSources();

		Debug::Print("Compiling");

		if (Compile()) {
			Debug::Print("Shader successful reloaded");
		}
	}
}

void ETB::Shader::HotReload() {
	EventSystem::AddEventListener(EventType::Tick, [&](Event& e) {
		struct stat fileInfo;
		stat(path.c_str(), &fileInfo);

		if (srcMTime != fileInfo.st_mtime) {
			srcMTime = fileInfo.st_mtime;

			Debug::Print("--------------------------------------");
			Debug::Print("Shader hot reload \"" + path + "\"");

			Debug::Print("Loading sources");
			LoadSources();

			Debug::Print("Compiling");

			if (Compile()) {
				Debug::Print("Shader successful reloaded");
			}
		}
	});
}

void ETB::Shader::SetSampler2D(const char* name, Texture& texture) {
	glActiveTexture(GL_TEXTURE0 + samplerCount);

	texture.Bind();

	glBindSampler(samplerCount, glGetUniformLocation(shaderId, name));
	glUniform1i(glGetUniformLocation(shaderId, name), samplerCount);

	samplerCount++;
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

uint32_t ETB::Shader::CreateShader(const std::string* source) {
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
