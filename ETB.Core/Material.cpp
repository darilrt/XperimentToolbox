#include <fstream>
#include <nlohmann/json.hpp>

#include "Material.h"
#include "ShaderLoader.h"
#include "AssetDatabase.h"
#include "Texture.h"

xtb::Material::Material() {
}

void xtb::Material::LoadFromFile(const std::string& path) {
	std::ifstream f(path);
	nlohmann::json data = nlohmann::json::parse(f);

	if (data.contains("shader")) {
		shader = &ShaderLoader::Get(data["shader"].get<std::string>());
	}
}

void xtb::Material::SetTexture(const std::string& name, xtb::TextureAsset* texture) {
	TextureUniformInfo* info = NULL;

	if (uniforms.count(name) != 0) {
		info = dynamic_cast<TextureUniformInfo*>(uniforms[name]);
		
		if (info == NULL) {
			delete uniforms[name];
		}
	}

	if (info == NULL) {
		info = new TextureUniformInfo;
		uniforms[name] = info;
	}
	
	info->texture = texture;
}

void xtb::Material::Use() {
	for (auto u : uniforms) { 
		if (u.second != NULL) u.second->Set(u.first, shader);
	}
}

xtb::Material::TextureUniformInfo::~TextureUniformInfo() {
}

void xtb::Material::TextureUniformInfo::Set(const std::string& name, Shader* shader) {
	shader->SetSampler2D(name.c_str(), *texture->texture);
}

xtb::Material::UniformInfo::~UniformInfo() {
}

void xtb::Material::UniformInfo::Set(const std::string& name, Shader* shader) {
}