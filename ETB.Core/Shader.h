#pragma once

#include <glm/glm.hpp>
#include <string>
#include <cstdint>
#include <vector>

#include "etbdefs.h"
#include "Graphics.h"
#include "Texture.h"
#include "Uniform.h"

namespace ETB {

	class Shader {
	public:
		DECLSPEC Shader();
		DECLSPEC Shader(const std::string& path);

		DECLSPEC ~Shader();

		DECLSPEC void LoadSources();
		DECLSPEC bool Compile();

		DECLSPEC void HotReload();

		DECLSPEC void Bind();

		DECLSPEC std::vector<ETB::Uniform> GetUniforms();
		
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

		inline void SetMatrix(const char* name, glm::mat4 v0) {
			glUniformMatrix4fv(glGetUniformLocation(shaderId, name),
				1, GL_FALSE, &v0[0][0]
			);
		}

		DECLSPEC void SetSampler2D(const char* name, Texture& texture);

	private:
		uint32_t samplerCount;
		uint32_t shaderId;

		std::string path;
		time_t srcMTime;
		std::string source;
	};

}