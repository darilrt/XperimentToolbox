#define IMGUI_DEFINE_MATH_OPERATORS

#include <imgui.h>
#include <imgui_internal.h>

#include "etb.h"
#include "EditorGUI.h"
#include "EditorCamera.h"

class ModelViewActor : public xtb::Actor {
public:
	xtb::Material* material;
	xtb::Mesh* mesh;

	void Start() {
		mesh = &xtb::Primitives::sphere;
	}

	void Render() {
		using namespace xtb;

		Graphics::DrawMesh(*mesh, transform.GetMatrix(), *material);
	}
} *modelViewActor;

void EditorGUI::InteractivePreview(xtb::Mesh* pMesh, xtb::Material& material) {
	using namespace xtb;

	static uint8_t model = 0;
	// Create Scene
	static Scene* scene = NULL;
	static EditorCamera* edCam = NULL;

	if (scene == NULL) {
		scene = new Scene();

		edCam = scene->Instance<EditorCamera>();
		edCam->cam.transform.position = { 0, 0, 5 };

		modelViewActor = scene->Instance<ModelViewActor>();
		modelViewActor->name = "Test";

		scene->Start();
	}

	if (pMesh != NULL) {
		modelViewActor->mesh = pMesh;
	}
	else {
		switch (model) {
		case 0: modelViewActor->mesh = &Primitives::sphere; break;
		case 1: modelViewActor->mesh = &Primitives::cube; break;
		case 2: modelViewActor->mesh = &Primitives::quad; break;
		default: break;
		}
	}

	modelViewActor->material = &material;

	bool ignoreGui = false;
	glm::vec2 cursorScreenPos = ImGui::GetCursorScreenPos();
	glm::vec2 cursorPos = ImGui::GetCursorPos();

	// Preview
	{
		glm::vec2 size = ImGui::GetContentRegionAvail();
		size.y -= 4;

		scene->Update();
		edCam->SetSize(size.x, size.y);
		scene->Render(edCam->cam);

		EditorGUI::Image(edCam->cam.renderTexture.color, size, { 0, 1 }, { 1, 0 });
		
		glm::vec2 rectMax = cursorScreenPos + size;
		ImRect area(cursorScreenPos, rectMax);
		
		ignoreGui = area.Contains(ImGui::GetMousePos());
	}
	
	// Tools
	if (pMesh == NULL) {
		cursorPos += glm::vec2(8.0f, 8.0f);

		ImGui::SetCursorPos(cursorPos);

		if (ImGui::Button("T", ImVec2(30, 30))) {
			model += 1;

			if (model >= 3) model = 0;
		}
		ignoreGui = ignoreGui && !ImGui::IsItemHovered();
	}

	EventSystem::IgnoreGui(ignoreGui);
}

bool EditorGUI::InputAsset(const std::string& label, std::string& uuid) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImGuiStyle& style = g.Style;
	
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
				ImGui::SetDragDropPayload("XTB_INPUT_ASSET", asset, sizeof(xtb::Asset), ImGuiCond_Once);
				ImGui::Text("%s", assetName.c_str());

				ImGui::EndDragDropSource();
			}
		}
	}
	else {
		draw_window->DrawList->AddText(g.Font, g.FontSize, draw_pos, ImGui::GetColorU32(ImGuiCol_TextDisabled), "None", NULL, 0.0f, &clip_rect);
	}

	if (ImGui::BeginDragDropTarget()) {
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("XTB_INPUT_ASSET")) {

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