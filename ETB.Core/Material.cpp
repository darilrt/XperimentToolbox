#include <fstream>
#include <nlohmann/json.hpp>

#include "Material.h"
#include "ShaderLoader.h"
#include "AssetDatabase.h"
#include "Texture.h"
#include "Asset.h"
#include "Debug.h"

namespace xtb {
	REGISTER_ASSET(Material, ".mat");
}

xtb::Material::Material() : shader() {
}

void xtb::Material::LoadFromFile(const std::string& path) {
	std::ifstream file(path);
	
	nlohmann::json json;
	
	// catch parsing error
	
	try {
		file >> json;
	}
	catch (nlohmann::json::parse_error& e) {
		xtb::Debug::Print("Error parsing material file: " + path);
		return;
	}
	
	if (json.contains("shader")) {
		const std::string shaderUUID = json["shader"].get<std::string>();
		shader = AssetDatabase::GetAssetByUUID<Shader>(shaderUUID);
	}

	if (json.contains("uniforms")) {
		for (auto& u : json["uniforms"].items()) {
			std::string name;
			
			if (u.value().contains("name")) {
				name = u.value()["name"].get<std::string>();
			}
			else {
				continue;
			}

			const nlohmann::json& data = u.value();

			if (data.contains("type")) {
				const std::string type = data["type"].get<std::string>();

				if (type == "texture" && data.contains("value") && data["value"].is_string()) {
					Texture* texture = Asset::GetAsset<Texture>(data["value"].get<std::string>());
					SetTexture(name, texture);
				}
				else if (type == "float" && data.contains("value") && data["value"].is_number()) {
					const float value = data["value"].get<float>();

					SetFloat(name, value);
				}
				else if (type == "vec2" && data.contains("value") && data["value"].is_array() && data["value"].size() == 2) {
					const glm::vec2 value = glm::vec2(
						data["value"][0].get<float>(),
						data["value"][1].get<float>());

					SetVector2(name, value);
				}
				else if (type == "vec3" && data.contains("value") && data["value"].is_array() && data["value"].size() == 3) {
					const glm::vec3 value = glm::vec3(
						data["value"][0].get<float>(),
						data["value"][1].get<float>(),
						data["value"][2].get<float>());

					SetVector3(name, value);
				}
				else if (type == "vec4" && data.contains("value") && data["value"].is_array() && data["value"].size() == 4) {
					const glm::vec4 value = glm::vec4(
						data["value"][0].get<float>(),
						data["value"][1].get<float>(),
						data["value"][2].get<float>(),
						data["value"][3].get<float>());

					SetVector4(name, value);
				}
				else if (type == "int" && data.contains("value")) {
					const int value = data["value"].get<int>();

					SetInt(name, value);
				}
				else if (type == "bool" && data.contains("value") && data["value"].is_boolean()) {
					const bool value = data["value"].get<bool>();

					SetBool(name, value);
				}
			}
		}
	}
}

void xtb::Material::SetTexture(const std::string& name, xtb::Texture* texture) {
	TextureUniformInfo* info = NULL;

	if (texture == NULL) {
		info = dynamic_cast<TextureUniformInfo*>(uniforms[name]);
		
		if (info != NULL) {
			info->texture = NULL;
		}
		else {
			info = new TextureUniformInfo();
			info->texture = NULL;
			uniforms[name] = info;
		}
		
		return;
	}

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

void xtb::Material::SetFloat(const std::string& name, float value) {
	FloatUniformInfo* info = NULL;

	if (uniforms.count(name) != 0) {
		info = dynamic_cast<FloatUniformInfo*>(uniforms[name]);

		if (info == NULL) {
			delete uniforms[name];
		}
	}

	if (info == NULL) {
		info = new FloatUniformInfo;
		uniforms[name] = info;
	}

	info->value = value;
}

void xtb::Material::SetVector2(const std::string& name, const glm::vec2& value) {
	Vector2UniformInfo* info = NULL;

	if (uniforms.count(name) != 0) {
		info = dynamic_cast<Vector2UniformInfo*>(uniforms[name]);

		if (info == NULL) {
			delete uniforms[name];
		}
	}

	if (info == NULL) {
		info = new Vector2UniformInfo;
		uniforms[name] = info;
	}

	info->value = value;
}

void xtb::Material::SetVector3(const std::string& name, const glm::vec3& value) {
	Vector3UniformInfo* info = NULL;

	if (uniforms.count(name) != 0) {
		info = dynamic_cast<Vector3UniformInfo*>(uniforms[name]);

		if (info == NULL) {
			delete uniforms[name];
		}
	}

	if (info == NULL) {
		info = new Vector3UniformInfo;
		uniforms[name] = info;
	}

	info->value = value;
}

void xtb::Material::SetVector4(const std::string& name, const glm::vec4& value) {
	Vector4UniformInfo* info = NULL;

	if (uniforms.count(name) != 0) {
		info = dynamic_cast<Vector4UniformInfo*>(uniforms[name]);

		if (info == NULL) {
			delete uniforms[name];
		}
	}

	if (info == NULL) {
		info = new Vector4UniformInfo;
		uniforms[name] = info;
	}

	info->value = value;
}

void xtb::Material::SetInt(const std::string& name, int value) {
	IntUniformInfo* info = NULL;

	if (uniforms.count(name) != 0) {
		info = dynamic_cast<IntUniformInfo*>(uniforms[name]);

		if (info == NULL) {
			delete uniforms[name];
		}
	}

	if (info == NULL) {
		info = new IntUniformInfo;
		uniforms[name] = info;
	}

	info->value = value;
}

void xtb::Material::SetBool(const std::string& name, bool value) {
	BoolUniformInfo* info = NULL;

	if (uniforms.count(name) != 0) {
		info = dynamic_cast<BoolUniformInfo*>(uniforms[name]);

		if (info == NULL) {
			delete uniforms[name];
		}
	}

	if (info == NULL) {
		info = new BoolUniformInfo;
		uniforms[name] = info;
	}

	info->value = value;
}

void xtb::Material::SetMatrix4(const std::string& name, const glm::mat4& value) {
	Matrix4UniformInfo* info = NULL;

	if (uniforms.count(name) != 0) {
		info = dynamic_cast<Matrix4UniformInfo*>(uniforms[name]);

		if (info == NULL) {
			delete uniforms[name];
		}
	}

	if (info == NULL) {
		info = new Matrix4UniformInfo;
		uniforms[name] = info;
	}

	info->value = value;
}

void xtb::Material::Use() {
	for (auto& u : uniforms) { 
		if (u.second) u.second->Set(u.first, shader);
	}
}

nlohmann::json xtb::Material::Serialize() {
	nlohmann::json obj = xtb::Asset::Serialize();

	obj["shader"] = shader->GetUUID();

	return obj;
}

std::string xtb::Material::GetTypeName() {
	return "Material";
}

void xtb::Material::LoadAsset() {
	xtb::Material::LoadFromFile(path.string());
}

void xtb::Material::SaveAsset() {
	std::ofstream file(path);

	nlohmann::json json;
	json["shader"] = shader->GetUUID();

	json["uniforms"] = nlohmann::json::array();
	
	for (auto& u : uniforms) {
		nlohmann::json uniform;
		
		if (u.second) {
			uniform = u.second->Serialize();
		}

		uniform["name"] = u.first;
		
		json["uniforms"].push_back(uniform);
	}
	
	file << std::setw(4) << json;
	file.close();
}

xtb::Asset* xtb::Material::Create() {
	return new Material();
}