#include <fstream>
#include <nlohmann/json.hpp>

#include "Material.h"
#include "ShaderLoader.h"

xtb::Material::Material() {
}

void xtb::Material::LoadFromFile(const std::string& path) {
	std::ifstream f(path);
	nlohmann::json data = nlohmann::json::parse(f);

	if (data.contains("shader")) {
		shader = &ShaderLoader::Get(data["shader"]);
	}
}
