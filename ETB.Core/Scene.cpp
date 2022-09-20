#include "Scene.h"
#include "Graphics.h"

ETB::Scene::Scene() {
}

ETB::Scene::~Scene() {
}

void ETB::Scene::Destroy(Actor* a) {
	// TODO: remove from list
	a->OnDestroy();
	delete a;
}

void ETB::Scene::Start() {
	for (Actor* a : actors) {
		a->Start();
	}
}

void ETB::Scene::Update() {
	for (Actor* a : actors) {
		a->Update();
	}
}

void ETB::Scene::Render(Camera& camera) {
	using namespace ETB;

	camera.Use();
	camera.renderTexture.BindFramebuffer();

	Graphics::Clear();
	
	for (Actor* a : actors) {
		a->Render();
	}

	camera.renderTexture.UnbindFramebuffer();
}

void ETB::Scene::GUI() {
	for (Actor* a : actors) {
		a->GUI();
	}
}