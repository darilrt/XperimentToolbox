#include "Uniform.h"
#include "AssetDatabase.h"
#include "Shader.h"

xtb::Uniform::Uniform(std::string _name, Type _type) : name(_name), type(_type) {
}

// Texture Uniform Methods

void xtb::TextureUniformInfo::Set(const std::string& name, Shader* shader) {
	shader->SetSampler2D(name.c_str(), texture);
}

nlohmann::json xtb::TextureUniformInfo::Serialize() {
	nlohmann::json obj;
	
	obj["type"] = GetTypeName();
	obj["value"] = texture ? texture->GetUUID() : "";
	
	return obj;
}

void xtb::TextureUniformInfo::Deserialize(const nlohmann::json& data) {
	if (data.contains("value")) {
		const std::string textureUUID = data["value"].get<std::string>();
		texture = AssetDatabase::GetAssetByUUID<Texture>(textureUUID);
	}
}

std::string xtb::TextureUniformInfo::GetTypeName() {
	return "texture";
}

// Float Uniform Methods

void xtb::FloatUniformInfo::Set(const std::string& name, Shader* shader) {
	shader->SetFloat(name.c_str(), value);
}

nlohmann::json xtb::FloatUniformInfo::Serialize() {
	nlohmann::json obj;

	obj["type"] = GetTypeName();
	obj["value"] = value;

	return obj;
}

void xtb::FloatUniformInfo::Deserialize(const nlohmann::json& data) {
	if (data.contains("value")) {
		value = data["value"].get<float>();
	}
}

std::string xtb::FloatUniformInfo::GetTypeName() {
	return "float";
}

// Vector2 Uniform Methods

void xtb::Vector2UniformInfo::Set(const std::string& name, Shader* shader) {
	shader->SetVector2(name.c_str(), value);
}

nlohmann::json xtb::Vector2UniformInfo::Serialize() {
	nlohmann::json obj;

	obj["type"] = GetTypeName();
	
	obj["value"] = {
		value.x,
		value.y
	};

	return obj;
}

void xtb::Vector2UniformInfo::Deserialize(const nlohmann::json& data) {
	if (data.contains("value")) {
		value.x = data["value"][0].get<float>();
		value.y = data["value"][1].get<float>();
	}
}

std::string xtb::Vector2UniformInfo::GetTypeName() {
	return "vec2";
}

// Vector3 Uniform Methods

void xtb::Vector3UniformInfo::Set(const std::string& name, Shader* shader) {
	shader->SetVector3(name.c_str(), value);
}

nlohmann::json xtb::Vector3UniformInfo::Serialize() {
	nlohmann::json obj;

	obj["type"] = GetTypeName();

	obj["value"] = {
		value.x,
		value.y,
		value.z
	};

	return obj;
}

void xtb::Vector3UniformInfo::Deserialize(const nlohmann::json& data) {
	if (data.contains("value")) {
		value.x = data["value"][0].get<float>();
		value.y = data["value"][1].get<float>();
		value.z = data["value"][2].get<float>();
	}
}

std::string xtb::Vector3UniformInfo::GetTypeName() {
	return "vec3";
}

// Vector4 Uniform Methods

void xtb::Vector4UniformInfo::Set(const std::string& name, Shader* shader) {
	shader->SetVector4(name.c_str(), value);
}

nlohmann::json xtb::Vector4UniformInfo::Serialize() {
	nlohmann::json obj;

	obj["type"] = GetTypeName();

	obj["value"] = {
		value.x,
		value.y,
		value.z,
		value.w
	};

	return obj;
}

void xtb::Vector4UniformInfo::Deserialize(const nlohmann::json& data) {
	if (data.contains("value")) {
		value.x = data["value"][0].get<float>();
		value.y = data["value"][1].get<float>();
		value.z = data["value"][2].get<float>();
		value.w = data["value"][3].get<float>();
	}
}

std::string xtb::Vector4UniformInfo::GetTypeName() {
	return "vec4";
}

// Matrix4 Uniform Methods

void xtb::Matrix4UniformInfo::Set(const std::string& name, Shader* shader) {
	shader->SetMatrix(name.c_str(), value);
}

nlohmann::json xtb::Matrix4UniformInfo::Serialize() {
	nlohmann::json obj;
	return obj;
}

void xtb::Matrix4UniformInfo::Deserialize(const nlohmann::json& data) {
}

std::string xtb::Matrix4UniformInfo::GetTypeName() {
	return "mat4";
}

// Int Uniform Methods

void xtb::IntUniformInfo::Set(const std::string& name, Shader* shader) {
	shader->SetInt(name.c_str(), value);
}

nlohmann::json xtb::IntUniformInfo::Serialize() {
	nlohmann::json obj;

	obj["type"] = GetTypeName();
	obj["value"] = value;

	return obj;
}

void xtb::IntUniformInfo::Deserialize(const nlohmann::json& data) {
	if (data.contains("value")) {
		value = data["value"].get<int>();
	}
}

std::string xtb::IntUniformInfo::GetTypeName() {
	return "int";
}

// Bool Uniform Methods

void xtb::BoolUniformInfo::Set(const std::string& name, Shader* shader) {
	shader->SetBool(name.c_str(), value);
}

nlohmann::json xtb::BoolUniformInfo::Serialize() {
	nlohmann::json obj;

	obj["type"] = GetTypeName();
	obj["value"] = value;

	return obj;
}

void xtb::BoolUniformInfo::Deserialize(const nlohmann::json& data) {
	if (data.contains("value")) {
		value = data["value"].get<bool>();
	}
}

std::string xtb::BoolUniformInfo::GetTypeName() {
	return "bool";
}