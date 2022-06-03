#include "ActorHandler.h"

std::list<ETB::Actor*> ETB::ActorHandler::actors;

void ETB::ActorHandler::Start() {
	for (Actor* a : ActorHandler::actors) {
		a->Start();
	}
}

void ETB::ActorHandler::Update() {
	for (Actor* a : ActorHandler::actors) {
		a->Update();
	}
}

void ETB::ActorHandler::Render() {
	for (Actor* a : ActorHandler::actors) {
		a->Render();
	}
}

void ETB::ActorHandler::GUI() {
	for (Actor* a : ActorHandler::actors) {
		a->GUI();
	}
}

void ETB::ActorHandler::Destroy(Actor* a) {
	a->OnDestroy();
	delete a;
}
