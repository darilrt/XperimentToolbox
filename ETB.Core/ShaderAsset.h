#pragma once

#include "Asset.h"
#include "Shader.h"

namespace xtb {

	// ShaderAsset class
	class ShaderAsset : public Asset {
	public:
		DECLSPEC virtual nlohmann::json Serialize();

		DECLSPEC virtual std::string GetTypeName();

		DECLSPEC virtual void LoadAsset();
		
		DECLSPEC static Asset* Create();

		DECLSPEC inline Shader* GetShader() { return shader; };
		
	private:
		Shader* shader;
	};
	
}