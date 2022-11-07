#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS

#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>
#include <string>
#include <etb.h>

namespace EditorGUI {
	
	void InteractivePreview(xtb::Mesh* mesh, xtb::Material& material);

	inline void Image(xtb::Texture& texture, const glm::vec2& size, const glm::vec2& uv0 = { 0, 0 }, const glm::vec2& uv1 = { 1, 1 }) {
		ImGui::Image((ImTextureID)(intptr_t)texture.GetID(), (const ImVec2&)size, (const ImVec2&)uv0, (const ImVec2&)uv1);
	}
	
	template<class T>
	bool InputAsset(const std::string& label, std::string& uuid) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		ImGuiStyle& style = g.Style;

		const std::string typeName(typeid(T).raw_name());
		const std::string payloadSubfix("XTBASSET");
		const std::string payloadID = (payloadSubfix + typeName);

		const float button_size = ImGui::GetFrameHeight();

		const ImVec2 frame_size(ImGui::CalcItemWidth(), ImGui::GetTextLineHeight() + style.FramePadding.y * 2);
		const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + frame_size);

		ImGuiWindow* draw_window = g.CurrentWindow;
		const ImVec2 draw_pos = frame_bb.Min + style.FramePadding;
		const ImVec4 clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + frame_size.x, frame_bb.Min.y + frame_size.y);

		const ImGuiID id = window->GetID(label.c_str());

		const ImRect item_rect(
			frame_bb.Min + style.ItemInnerSpacing,
			frame_bb.Max
		);

		ImGui::ItemSize(frame_size, style.FramePadding.y);
		if (!ImGui::ItemAdd(item_rect, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(frame_bb, id, &hovered, &held);

		ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);

		bool changed_value = false;

		if (uuid != "") {
			xtb::Asset* asset = xtb::AssetDatabase::GetAssetByUUID(uuid);

			if (asset != NULL) {
				const std::string& assetName = asset->path.stem().string();
				draw_window->DrawList->AddText(g.Font, g.FontSize, draw_pos, ImGui::GetColorU32(ImGuiCol_Text), assetName.c_str(), NULL, 0.0f, &clip_rect);

				// const bool hovered = ImGui::ItemHoverable(frame_bb, id);
				// if (hovered) g.MouseCursor = ImGuiMouseCursor_Hand;

				if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
					ImGui::SetDragDropPayload(payloadID.c_str(), asset, sizeof(xtb::Asset), ImGuiCond_Once);
					ImGui::Text("%s", assetName.c_str());

					ImGui::EndDragDropSource();
				}
			}
		}
		else {
			draw_window->DrawList->AddText(g.Font, g.FontSize, draw_pos, ImGui::GetColorU32(ImGuiCol_TextDisabled), "None", NULL, 0.0f, &clip_rect);
		}

		if (ImGui::BeginDragDropTarget()) {
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(payloadID.c_str())) {

				IM_ASSERT(payload->DataSize == sizeof(xtb::Asset));

				xtb::Asset* payloadData = ((xtb::Asset*)payload->Data);
				uuid = payloadData->GetUUID();
				changed_value = true;
			}

			ImGui::EndDragDropTarget();
		}

		ImGui::RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label.c_str());

		return changed_value;
	}
}