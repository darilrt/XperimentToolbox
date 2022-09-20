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
}

ETB::Shader::~Shader() {
	glDeleteProgram(shaderId);
}

void ETB::Shader::Use() {
	glUseProgram(shaderId);
	samplerCount = 0;
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

	texture.BindTexture();

	glBindSampler(samplerCount, glGetUniformLocation(shaderId, name));
	glUniform1i(glGetUniformLocation(shaderId, name), samplerCount);

	samplerCount++;
}