#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "etbdefs.h"
#include "Uniform.h"
#include "Shader.h"
#include "Asset.h"

namespace xtb {

	class Material : public xtb::Asset {
	public:
		Shader* shader;

		DECLSPEC Material();

		DECLSPEC void LoadFromFile(const std::string& path);

		DECLSPEC inline UniformInfo* Get(const std::string& key) { return uniforms[key]; }
		
		DECLSPEC void Use();

		// Types of uniforms\
		
		DECLSPEC void SetTexture(const std::string& name, xtb::Texture* texture);

		DECLSPEC void SetFloat(const std::string& name, float value);

		DECLSPEC void SetInt(const std::string& name, int value);

		DECLSPEC void SetVector2(const std::string& name, const glm::vec2& value);
		
		DECLSPEC void SetVector3(const std::string& name, const glm::vec3& value);

		DECLSPEC void SetVector4(const std::string& name, const glm::vec4& value);

		DECLSPEC void SetMatrix4(const std::string& name, const glm::mat4& value);
		
		DECLSPEC void SetBool(const std::string& name, bool value);

		// Inherited via Asset

		DECLSPEC nlohmann::json Serialize() override;
		
		DECLSPEC std::string GetTypeName() override;
		
		DECLSPEC void LoadAsset() override;

		DECLSPEC void SaveAsset() override;

		DECLSPEC static Asset* Create();
		
	private:
		std::map<std::string, UniformInfo*> uniforms;

		inline void SetUniform(const std::string& name, UniformInfo* info) { uniforms[name] = info; }
		
		inline void DeleteUniform(const std::string& name) { delete uniforms[name]; }
	};

}