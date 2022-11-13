#include <string>
#include <vector>

#include "Debug.h"
#include "File.h"
#include "Shader.h"
#include "Uniform.h"
#include "Camera.h"
#include "EventSystem.h"

namespace xtb {
	REGISTER_ASSET(Shader, ".gl");
}

xtb::Shader::Shader() {
	shaderId = NULL;
}

xtb::Shader::Shader(const std::string& _path) {
	shaderId = NULL;

	path = _path;

	LoadSources();
}

xtb::Shader::~Shader() {
	glDeleteProgram(shaderId);
}

void xtb::Shader::Bind() {
	glUseProgram(shaderId);
	samplerCount = 0;
}

std::vector<xtb::Uniform> GetUniforms_impl(uint32_t shaderId) {
	std::vector<xtb::Uniform> uniforms;
	
	if (shaderId == NULL) {
		xtb::Debug::Print("Trying to get uniforms on an uncompiled shader");
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
	xtb::Uniform::Type ctype = xtb::Uniform::Unknow;

	for (int32_t i = 0; i < count; i++) {
		glGetActiveUniform(shaderId, (GLuint)i, bufSize, &length, &size, &type, name);
		
		switch (type) {
		case GL_BOOL: ctype = xtb::Uniform::Bool; break;
		case GL_INT: ctype = xtb::Uniform::Int; break;
		case GL_FLOAT: ctype = xtb::Uniform::Float; break;
		case GL_FLOAT_VEC2: ctype = xtb::Uniform::Vector2; break;
		case GL_FLOAT_VEC3: ctype = xtb::Uniform::Vector3; break;
		case GL_FLOAT_VEC4: ctype = xtb::Uniform::Vector4; break;
		case GL_FLOAT_MAT4: ctype = xtb::Uniform::Matrix4; break;
		case GL_SAMPLER_2D: ctype = xtb::Uniform::Sampler2D; break;
		default: break;
		}

		uniforms.push_back(xtb::Uniform(std::string(name), ctype));
	}

	return uniforms;
}

void xtb::Shader::LoadSources() {
	if (!File::Exists(path.string())) {
		Debug::Print("Shader \"" + path.string() + "\" does not exists");
		return;
	}
	
	source = File::ReadAll(path.string());
}

bool xtb::Shader::Compile() {
	if (source.size() == 0) return true;

	shaderId = CreateShader(&source);
	source.clear();
	return shaderId != 0;
}

void xtb::Shader::Reload() {
	struct stat fileInfo;
	stat(path.string().c_str(), &fileInfo);

	if (srcMTime != fileInfo.st_mtime) {
		srcMTime = fileInfo.st_mtime;

		Debug::Print("--------------------------------------");
		Debug::Print("Shader hot reload \"" + path.string() + "\"");

		Debug::Print("Loading sources");
		LoadSources();

		Debug::Print("Compiling");

		if (Compile()) {
			Debug::Print("Shader successful reloaded");

			uniforms = GetUniforms_impl(shaderId);
		}
	}
}

void xtb::Shader::HotReload() {
	EventSystem::AddEventListener(EventType::Tick, [&](Event& e) {
		struct stat fileInfo;
		stat(path.string().c_str(), &fileInfo);

		if (srcMTime != fileInfo.st_mtime) {
			srcMTime = fileInfo.st_mtime;

			Debug::Print("--------------------------------------");
			Debug::Print("Shader hot reload \"" + path.string() + "\"");

			Debug::Print("Loading sources");
			LoadSources();

			Debug::Print("Compiling");

			if (Compile()) {
				Debug::Print("Shader successful reloaded");
			}
		}
	});
}

void xtb::Shader::SetSampler2D(const char* name, Texture* texture) {
	
	if (texture) {
		glActiveTexture(GL_TEXTURE0 + samplerCount);

		texture->Bind();
		
		glBindSampler(samplerCount, glGetUniformLocation(shaderId, name));
		glUniform1i(glGetUniformLocation(shaderId, name), samplerCount);

		samplerCount++;
	}
	
	std::string isSetName = "xtb_" + std::string(name) + "_isSet";
	glUniform1i(glGetUniformLocation(shaderId, isSetName.c_str()), texture != NULL);
}

std::string xtb::Shader::GetTypeName() {
	return "Shader";
}

void xtb::Shader::LoadAsset() {
	LoadSources();
	Compile();
}

xtb::Asset* xtb::Shader::Create() {
	return new Shader();
}

void PrintShaderLog_impl(int32_t shader) {
	if (glIsShader(shader)) {
		int32_t infoLogLength = 0;
		int32_t maxLength = infoLogLength;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		char* infoLog = new char[maxLength];

		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);

		if (infoLogLength > 0) {
			xtb::Debug::Print(infoLog);
		}

		delete[] infoLog;
	}
	else {
		std::string _log = "Name ";
		_log += std::to_string(shader);
		_log += " is not a shader";
		xtb::Debug::Print(_log);
	}
}

uint32_t xtb::Shader::CreateShader(const std::string* source) {
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
