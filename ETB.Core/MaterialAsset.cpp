#include <fstream>
#include <nlohmann/json.hpp>

#include "MaterialAsset.h"
#include "AssetDatabase.h"
#include "ShaderAsset.h"
#include "Shader.h"

namespace xtb {
	REGISTER_ASSET(MaterialAsset, ".mat");

	Asset* MaterialAsset::Create() {
		return new MaterialAsset();
	}

	void MaterialAsset::LoadAsset() {
		std::ifstream file(path);
		nlohmann::json json;
		file >> json;
		
		shaderUUID = json["shader"];
		ShaderAsset* shaderAsset = xtb::AssetDatabase::GetAssetByUUID<ShaderAsset>(shaderUUID);
		
		material = new Material();
		
		if (shaderAsset == NULL) {
			shaderUUID = "";
		}
		else {
			material->shader = shaderAsset->GetShader();
		}
	}

	void MaterialAsset::SaveAsset() {
		nlohmann::json json;

		json["shader"] = shaderUUID;
		
		json["references"] = nlohmann::json::array();
		
		std::ofstream file(path);
		file << json.dump(4);
	}

	std::string MaterialAsset::GetTypeName() {
		return typeid(xtb::MaterialAsset).raw_name();
	}
}