#include <imgui.h>

#include "Actor.h"

void xtb::Actor::Start() {
}

void xtb::Actor::Update() {
}

void xtb::Actor::Render() {
}

void xtb::Actor::GUI() {
}

void xtb::Actor::InspectorRender() {
	ImGui::Text("Name: %s", name.c_str());

	// transform inspector
	ImGui::Text("Transform");
	
	ImGui::DragFloat3("Position", &transform.position.x, 0.1f);
	
	for (int i = 0; i < components.size(); i++) {
		components[i]->InspectorRender();
	}
}

void xtb::Actor::OnDestroy() {
}

void xtb::Actor::AddComponent(Component* component) {
	components.push_back(component);
}

void xtb::Actor::RemoveComponent(Component* component) {
	for (int i = 0; i < components.size(); i++) {
		if (components[i] == component) {
			components.erase(components.begin() + i);
			return;
		}
	}
}
