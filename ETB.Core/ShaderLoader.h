#pragma once

#include "etbdefs.h"
#include "Shader.h"

#include <string>
#include <map>

namespace ETB {
	
	class ShaderLoader {
	public:
		static DECLSPEC void Add(const std::string& path, bool hotLoad = false);

		inline static Shader& Get(const std::string& path) { return ShaderLoader::shaders[path]; }

		inline static void Use(const std::string& path) { ShaderLoader::shaders[path].Use(); }
		
	private:
		static DECLSPEC std::map<std::string, Shader> shaders;
	};

}
