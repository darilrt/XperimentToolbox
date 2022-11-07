#pragma once

#include <string>
#include <etb.h>

class Resource {

};

namespace EditorGUI {
	
	void InteractivePreview(xtb::Mesh* mesh, xtb::Material& material);

	bool InputAsset(const std::string& label, std::string& uuid);
	
	inline void Image(xtb::Texture& texture, const glm::vec2& size, const glm::vec2& uv0 = { 0, 0 }, const glm::vec2& uv1 = { 1, 1 }) {
		ImGui::Image((ImTextureID)(intptr_t)texture.GetID(), (const ImVec2&)size, (const ImVec2&)uv0, (const ImVec2&)uv1);
	}
}