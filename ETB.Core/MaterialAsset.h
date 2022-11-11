#pragma once

#include "Asset.h"
#include "Material.h"

namespace xtb {

	class MaterialAsset : public xtb::Asset {
	public:
		DECLSPEC static Asset* Create();
		
		DECLSPEC std::string GetTypeName();

		DECLSPEC void LoadAsset();

		DECLSPEC void SaveAsset();

		DECLSPEC inline Material* GetMaterial() { return material; };

	private:
		Material* material;
		std::string shaderUUID;
	};

}

