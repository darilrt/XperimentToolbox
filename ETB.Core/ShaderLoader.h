#pragma once

#include "etbdefs.h"
#include "Shader.h"

#include <string>
#include <map>

namespace ETB {
	
	class ShaderLoader {
	public:
		static DECLSPEC void Add(const std::string& path, bool hotLoad = false);

		static DECLSPEC Shader& Get(const std::string& path);
		
	private:
		static DECLSPEC std::map<std::string, Shader> shaders;
	};

}
