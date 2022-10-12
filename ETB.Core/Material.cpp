#include <fstream>
#include <nlohmann/json.hpp>

#include "Material.h"
#include "ShaderLoader.h"

ETB::Material::Material() {
}

void ETB::Material::LoadFromFile(const std::string& path) {
	std::ifstream f(path);
	nlohmann::json data = nlohmann::json::parse(f);

	if (data.contains("shader")) {
		shader = &ShaderLoader::Get(data["shader"]);
	}
}
