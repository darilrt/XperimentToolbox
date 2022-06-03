#pragma once

#include "etbdefs.h"
#include "Actor.h"

#include <list>

namespace ETB {

	class ActorHandler {
	public:
		static DECLSPEC void Start();
		static DECLSPEC void Update();
		static DECLSPEC void Render();
		static DECLSPEC void GUI();

		static DECLSPEC void Destroy(Actor* a);

		template<typename T>
		static T* Instance() {
			T* inst = new T;
			ActorHandler::actors.push_back((Actor*)inst);
			return inst;
		}

	private:
		static DECLSPEC std::list<Actor*> actors;
	};

}