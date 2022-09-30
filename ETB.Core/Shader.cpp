#include <string>
#include <vector>

#include "Debug.h"
#include "File.h"
#include "Shader.h"
#include "Uniform.h"
#include "Graphics.h"
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
	shaderId = Graphics::CreateShader(&source);
	source.clear();
	return shaderId != 0;
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