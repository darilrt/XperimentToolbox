#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "etbdefs.h"
#include "Uniform.h"
#include "Shader.h"

namespace xtb {

	class Material {
	public:
		Shader* shader;

		DECLSPEC Material();

		DECLSPEC void LoadFromFile(const std::string& path);

	private:
	};

}