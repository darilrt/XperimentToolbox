#include <imgui.h>
#include <imgui_internal.h>

#include "EditorGUI.h"

void EditorGUI::InputResource(const std::string& label, Resource* resource) {
	const char* cLabel = &label[0];

	ImGui::Text(cLabel);
	ImGui::SameLine();
	ImGui::Button("button");
	
	static float f = 0;
	ImGui::InputFloat2("float", &f);

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->AddRectFilled(ImGui::GetItemRectMin(), ImVec2(50, 50), 0xFFFFFF);
}
