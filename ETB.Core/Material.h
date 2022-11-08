#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "etbdefs.h"
#include "Uniform.h"
#include "Shader.h"
#include "TextureAsset.h"

namespace xtb {

	class Material {
	public:
		class UniformInfo {
		public:
			DECLSPEC virtual ~UniformInfo();
			DECLSPEC virtual void Set(const std::string& name, Shader* shader);
		};

		class TextureUniformInfo : public UniformInfo {
		public:
			TextureAsset* texture;

			DECLSPEC virtual ~TextureUniformInfo();
			DECLSPEC virtual void Set(const std::string& name, Shader* shader);
		};

		Shader* shader;

		DECLSPEC Material();

		DECLSPEC void LoadFromFile(const std::string& path);

		DECLSPEC inline UniformInfo* Get(const std::string& key) { return uniforms[key]; }
		
		DECLSPEC void SetTexture(const std::string& name, xtb::TextureAsset* texture);

		DECLSPEC void Use();
		
	private:
		std::map<std::string, UniformInfo*> uniforms;
	};

}