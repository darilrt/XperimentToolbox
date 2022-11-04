#include "EventSystem.h"
#include "Input.h"

#include <SDL.h>

xtb::Input xtb::Input::instance;

glm::vec2 xtb::Input::GetMousePosition() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return glm::vec2(x, y);
}

xtb::Input::Input() {
	keyDownState = new bool[322];
	keyUpState = new bool[322];
	keyPressState = new bool[322];

    std::fill(keyPressState, keyPressState + 322 * sizeof(bool), false);
    
    EventSystem::AddEventListener(EventType::Tick, [&](Event& e) {
        std::fill(keyDownState, keyDownState + 322 * sizeof(bool), false);
        std::fill(keyUpState, keyUpState + 322 * sizeof(bool), false);
    });

    EventSystem::AddEventListener(EventType::KeyDown, [&](Event& e) {
        keyDownState[(uint32_t)e.keyCode] = true;
        keyPressState[(uint32_t)e.keyCode] = true;
    });

    EventSystem::AddEventListener(EventType::KeyUp, [&](Event& e) {
        keyPressState[(uint32_t)e.keyCode] = false;
        keyUpState[(uint32_t)e.keyCode] = true;
    });
}
