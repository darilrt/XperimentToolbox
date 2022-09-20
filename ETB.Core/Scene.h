#pragma once

#include "etbdefs.h"
#include "Actor.h"
#include "Camera.h"

#include <vector>

namespace ETB {

	class Scene {
	public:
		DECLSPEC Scene();
		DECLSPEC ~Scene();

		template<typename T>
		T* Instance() {
			T* inst = new T();
			actors.push_back((Actor*)inst);
			return inst;
		}

		DECLSPEC void Destroy(Actor* a);

		DECLSPEC void Start();
		DECLSPEC void Update();
		DECLSPEC void Render(Camera& camera);
		DECLSPEC void GUI();

		inline DECLSPEC std::vector<Actor*> GetActors() { return actors; }
		
	private:
		std::vector<Actor*> actors;
	};

}
