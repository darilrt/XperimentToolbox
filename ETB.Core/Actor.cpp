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

void DrawComponent_impl(xtb::Component* c) {
	ImGui::PushID(c);

	if (ImGui::CollapsingHeader(c->GetName().c_str())) {
		c->InspectorRender();
	}
	
	ImGui::PopID();
}

void xtb::Actor::InspectorRender() {
	ImGui::Text("Name: %s", name.c_str());

	ImGui::Text("Transform");
	ImGui::DragFloat3("Position", &transform.position.x, 0.1f);
	
	for (int i = 0; i < components.size(); i++) {
		DrawComponent_impl(components[i]);
	}
}

void xtb::Actor::OnDestroy() {
}

void xtb::Actor::AddComponent(Component* component) {
	component->SetActor(this);
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
