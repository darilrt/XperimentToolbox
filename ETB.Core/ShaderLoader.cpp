#include "ShaderLoader.h"
#include "Debug.h"

std::map<std::string, xtb::Shader> xtb::ShaderLoader::shaders;

void xtb::ShaderLoader::Add(const std::string& path, bool hotLoad) {
	if (ShaderLoader::shaders.count(path) != 0) {
		return;
	}

	ShaderLoader::shaders[path] = Shader(path);

	if (!ShaderLoader::shaders[path].Compile()) {
		Debug::Print("Unable to compile " + path + "\n");
	}
	
	if (hotLoad) ShaderLoader::shaders[path].HotReload();
}

xtb::Shader& xtb::ShaderLoader::Get(const std::string& path) {
	if (ShaderLoader::shaders.count(path) == 0) {
		Add(path);
	}

	return ShaderLoader::shaders[path];
}
