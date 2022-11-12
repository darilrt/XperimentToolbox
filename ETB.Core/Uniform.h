#pragma once

#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <string>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>

#include "etbdefs.h"
#include "Texture.h"

namespace xtb {
	class Shader;

	class Uniform {
	public:
		enum Type {
			Unknow,
			Bool,
			Int,		// int
			Float,		// float
			Vector2,	// vec2
			Vector3,	// vec3
			Vector4,	// vec4
			Matrix4,
			Sampler2D	// GL_SAMPLER_2D
		};

		std::string name;
		Type type;

		DECLSPEC Uniform(std::string name, Type type);
	};


	class UniformInfo {
	public:
		virtual void Set(const std::string& name, Shader* shader) = 0;

		virtual nlohmann::json Serialize() = 0;

		virtual void Deserialize(const nlohmann::json& data) = 0;

		virtual std::string GetTypeName() = 0;
	};

	// Texture uniform
	class TextureUniformInfo : public UniformInfo {
	public:
		Texture* texture;

		DECLSPEC virtual void Set(const std::string& name, Shader* shader);

		DECLSPEC virtual nlohmann::json Serialize();
		
		DECLSPEC virtual void Deserialize(const nlohmann::json& data);

		DECLSPEC virtual std::string GetTypeName();
	};

	// Float uniform
	class FloatUniformInfo : public UniformInfo {
	public:
		float value;

		DECLSPEC virtual void Set(const std::string& name, Shader* shader);

		DECLSPEC virtual nlohmann::json Serialize();
		
		DECLSPEC virtual void Deserialize(const nlohmann::json& data);

		DECLSPEC virtual std::string GetTypeName();
	};

	// Vector2 uniform
	class Vector2UniformInfo : public UniformInfo {
	public:
		glm::vec2 value;

		DECLSPEC virtual void Set(const std::string& name, Shader* shader);

		DECLSPEC virtual nlohmann::json Serialize();

		DECLSPEC virtual void Deserialize(const nlohmann::json& data);

		DECLSPEC virtual std::string GetTypeName();
	};

	// Vector3 uniform
	class Vector3UniformInfo : public UniformInfo {
	public:
		glm::vec3 value;

		DECLSPEC virtual void Set(const std::string& name, Shader* shader);

		DECLSPEC virtual nlohmann::json Serialize();

		DECLSPEC virtual void Deserialize(const nlohmann::json& data);

		DECLSPEC virtual std::string GetTypeName();
	};
	
	// Vector4 uniform
	class Vector4UniformInfo : public UniformInfo {
	public:
		glm::vec4 value;

		DECLSPEC virtual void Set(const std::string& name, Shader* shader);

		DECLSPEC virtual nlohmann::json Serialize();

		DECLSPEC virtual void Deserialize(const nlohmann::json& data);

		DECLSPEC virtual std::string GetTypeName();
	};

	// Matrix4 uniform
	class Matrix4UniformInfo : public UniformInfo {
	public:
		glm::mat4 value;

		DECLSPEC virtual void Set(const std::string& name, Shader* shader);

		DECLSPEC virtual nlohmann::json Serialize();

		DECLSPEC virtual void Deserialize(const nlohmann::json& data);

		DECLSPEC virtual std::string GetTypeName();
	};
	
	// Int uniform
	class IntUniformInfo : public UniformInfo {
	public:
		int value;

		DECLSPEC virtual void Set(const std::string& name, Shader* shader);

		DECLSPEC virtual nlohmann::json Serialize();

		DECLSPEC virtual void Deserialize(const nlohmann::json& data);

		DECLSPEC virtual std::string GetTypeName();
	};

	// Bool uniform
	class BoolUniformInfo : public UniformInfo {
	public:
		bool value;

		DECLSPEC virtual void Set(const std::string& name, Shader* shader);

		DECLSPEC virtual nlohmann::json Serialize();

		DECLSPEC virtual void Deserialize(const nlohmann::json& data);

		DECLSPEC virtual std::string GetTypeName();
	};
}
