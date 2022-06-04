#include "Debug.h"
#include "etb.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <string>

void DECLSPEC ETB::Debug::Print(const std::string& message) {
	std::cout << message << "\n";
}

void ETB::Debug::TransformEditor(Transform& transform) {
	ImGui::Begin("Transform Editor");

	ImGui::InputFloat3("Position", &transform.position[0]);
	
	static glm::vec3 euler;
	euler = glm::eulerAngles(transform.rotation) * TO_DEGREES;
	ImGui::InputFloat3("Rotation X", &euler[0]);
	transform.rotation = glm::quat(euler * TO_RADIANS);

	ImGui::InputFloat3("Scale", &transform.scale[0]);

	ImGui::End();
}

void ETB::Debug::ShowStatus() {
	ImGui::Begin("Status");

	int32_t fps = (int32_t)(1.0f / Time::deltaTime);
	ImGui::Text(("FPS " + std::to_string(fps)).c_str());

	ImGui::Text(("Delta Time " + std::to_string(Time::deltaTime)).c_str());

	ImGui::End();
}
