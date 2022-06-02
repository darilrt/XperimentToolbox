#pragma once

#include "etbdefs.h"

#include <glm/glm.hpp>

namespace ETB {
	
	class DECLSPEC Input {
	public:
		inline static bool KeyUp(KeyCode keyCode) {
			return instance.keyUpState[(uint8_t)keyCode];
		};

		inline static bool KeyDown(KeyCode keyCode) {
			return instance.keyDownState[(uint8_t)keyCode];
		};

		inline static bool KeyPressed(KeyCode keyCode) {
			return instance.keyPressState[(uint8_t)keyCode];
		};
		
		static glm::vec2 GetMousePosition();

	private:
		bool* keyDownState;
		bool* keyUpState;
		bool* keyPressState;
		
		static Input instance;

		Input();
	};

}
