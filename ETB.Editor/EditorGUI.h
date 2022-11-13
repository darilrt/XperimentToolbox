#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS

#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>
#include <string>
#include <etb.h>

namespace EditorGUI {
	
	void InteractivePreview(xtb::Mesh* mesh, xtb::Material* material);

	inline void Image(xtb::Texture& texture, const glm::vec2& size, const glm::vec2& uv0 = { 0, 0 }, const glm::vec2& uv1 = { 1, 1 }) {
		ImGui::Image((ImTextureID)(intptr_t)texture.GetID(), (const ImVec2&)size, (const ImVec2&)uv0, (const ImVec2&)uv1);
	}

	bool InputAssetEx(const char* label, std::string& uuid, const char* assetType);
	
	template<class T>
	bool InputAsset(const std::string& label, std::string& uuid) {
		return InputAssetEx(label.c_str(), uuid, T().GetTypeName().c_str());
	}
}