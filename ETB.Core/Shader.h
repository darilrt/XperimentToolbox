#pragma once

#include <glm/glm.hpp>
#include <string>
#include <cstdint>
#include <vector>

#include "etbdefs.h"
#include "Texture.h"
#include "Uniform.h"
#include "Asset.h"

namespace xtb {

	class Shader : public Asset {
	public:
		DECLSPEC Shader();
		DECLSPEC Shader(const std::string& path);

		DECLSPEC ~Shader();

		DECLSPEC void LoadSources();
		
		DECLSPEC bool Compile();

		DECLSPEC void Reload();
		
		DECLSPEC void HotReload();

		DECLSPEC void Bind();

		inline std::vector<xtb::Uniform>& GetUniforms() { return uniforms; };
		
		inline void Unbind() { glUseProgram(NULL); }

		inline void SetFloat(const char* name, float v0) {
			glUniform1f(glGetUniformLocation(shaderId, name), v0);
		}

		inline void SetVector2(const char* name, glm::vec2 v0) {
			glUniform2f(glGetUniformLocation(shaderId, name), v0.x, v0.y);
		}

		inline void SetVector3(const char* name, glm::vec3 v0) {
			glUniform3f(glGetUniformLocation(shaderId, name), v0.x, v0.y, v0.z);
		}
		
		inline void SetVector4(const char* name, glm::vec4 v0) {
			glUniform4f(glGetUniformLocation(shaderId, name), v0.x, v0.y, v0.z, v0.w);
		}

		inline void SetMatrix(const char* name, glm::mat4 v0) {
			glUniformMatrix4fv(glGetUniformLocation(shaderId, name),
				1, GL_FALSE, &v0[0][0]
			);
		}
		
		inline void SetBool(const char* name, bool value) const {
			glUniform1i(glGetUniformLocation(shaderId, name), (int)value);
		}

		inline void SetInt(const char* name, int value) const {
			glUniform1i(glGetUniformLocation(shaderId, name), value);
		}

		inline uint32_t GetId() { return shaderId; }
		
		inline std::string GetPath() { return path.string(); }

		DECLSPEC void SetSampler2D(const char* name, Texture& texture);

		// Inherited via Asset
		
		DECLSPEC std::string GetTypeName() override;

		DECLSPEC void LoadAsset() override;

		DECLSPEC static Asset* Create();

	private:
		uint32_t CreateShader(const std::string* source);

		std::vector<xtb::Uniform> uniforms;

		uint32_t samplerCount;
		uint32_t shaderId;

		time_t srcMTime;
		std::string source;
	};

}