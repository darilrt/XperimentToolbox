#pragma once

#include "etbdefs.h"
#include "KeyCode.h"

#include <functional>
#include <vector>
#include <map>
#include <SDL.h>

namespace ETB{

	enum class EventType {
		Unknow,

		// App Events
		Start,
		Tick,
		Render,
		GUI,

		// Window Events
		WindowQuit,
		WindowResize,

		// Input Events
		KeyDown,
		KeyUp,

		MouseButtonDown,
		MouseButtonUp,
	};

	class DECLSPEC Event {
	public:
		struct {
			int32_t width;
			int32_t height;
		} window;

		KeyCode keyCode;
		uint8_t button;
	};

	class EventSystem {
	public:
		static void DECLSPEC DispatchEventType(EventType type);
		static void DECLSPEC DispatchEvents();

		static void DECLSPEC AddEventListener(EventType type, std::function<void(Event&)> fn);

	private:
		static SDL_Event sdlEvent;
		static Event event;
		static std::map<EventType, std::vector<std::function<void(Event&)>>> events;
	};

}