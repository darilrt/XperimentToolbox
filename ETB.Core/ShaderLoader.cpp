#include "ShaderLoader.h"
#include "Debug.h"

std::map<std::string, ETB::Shader> ETB::ShaderLoader::shaders;

void ETB::ShaderLoader::Add(const std::string& path, bool hotLoad) {
	if (ShaderLoader::shaders.count(path) != 0) {
		Debug::Print("Shader \"" + path + "\" already exists");
	}

	ShaderLoader::shaders[path] = Shader(path);
	
	if (hotLoad) ShaderLoader::shaders[path].HotReload();
}
