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

		ImGui::Image((ImTextureID)edCam->cam.renderTexture.color.GetId(), size, ImVec2(0, 1), ImVec2(1, 0));
		
		glm::vec2 rectMax = cursorScreenPos + size;
		ImRect area(cursorScreenPos, rectMax);
		
		ignoreGui = area.Contains(ImGui::GetMousePos());
	}
	
	static uint8_t model = 0;
	// Tools
	if (pMesh == NULL) {
		cursorPos += glm::vec2(8.0f, 8.0f);

		ImGui::SetCursorPos(cursorPos);

		if (ImGui::Button("T", ImVec2(30, 30))) {
			model += 1;

			if (model >= 3) model = 0;

			switch (model) {
			case 0: modelViewActor->mesh = &Primitives::sphere; break;
			case 1: modelViewActor->mesh = &Primitives::cube; break;
			case 2: modelViewActor->mesh = &Primitives::quad; break;
			default: break;
			}
		}
		ignoreGui = ignoreGui && !ImGui::IsItemHovered();
	}
	else {
		modelViewActor->mesh = pMesh;
	}

	EventSystem::IgnoreGui(ignoreGui);
}

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
