#include "Debug.h"
#include "File.h"
#include "Shader.h"
#include "Graphics.h"
#include "Camera.h"
#include "EventSystem.h"

ETB::Shader::Shader() {
}

ETB::Shader::Shader(const std::string& _path) {
	path = _path;

	LoadSources();
	Compile();
}

ETB::Shader::~Shader() {
	glDeleteProgram(shaderId);
}

void ETB::Shader::Use() {
	glUseProgram(shaderId);
	samplerCount = 0;
}

void ETB::Shader::LoadSources() {
	std::string fragPath = path + ".frag";
	std::string vertPath = path + ".vert";

	if (!File::Exists(fragPath)) {
		Debug::Print("Fragment shader \"" + fragPath + "\" does not exists");
		return;
	}

	if (!File::Exists(vertPath)) {
		Debug::Print("Vertex shader \"" + vertPath + "\" does not exists");
		return;
	}

	fragSource = File::ReadAll(fragPath);
	vertSource = File::ReadAll(vertPath);
}

bool ETB::Shader::Compile() {
	shaderId = Graphics::CreateShader(&vertSource, &fragSource);
	return shaderId != 0;
}

void ETB::Shader::HotReload() {
	EventSystem::AddEventListener(EventType::Tick, [&](Event& e) {
		std::string fragPath = path + ".frag";
		std::string vertPath = path + ".vert";

		bool reload = false;
		struct stat fileInfo;

		stat(fragPath.c_str(), &fileInfo);

		if (fragMTime != fileInfo.st_mtime) {
			reload = true;
			fragMTime = fileInfo.st_mtime;
		}

		stat(vertPath.c_str(), &fileInfo);

		if (vertMTime != fileInfo.st_mtime) {
			reload = true;
			vertMTime = fileInfo.st_mtime;
		}

		if (reload) {
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

	texture.BindTexture();

	glUniform1i(glGetUniformLocation(shaderId, name), samplerCount);

	samplerCount++;
}