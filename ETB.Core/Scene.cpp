#include "Scene.h"
#include "Graphics.h"

xtb::Scene::Scene() {
}

xtb::Scene::~Scene() {
}

void xtb::Scene::Destroy(Actor* a) {
	// TODO: remove from list
	a->OnDestroy();
	delete a;
}

void xtb::Scene::Start() {
	for (Actor* a : actors) {
		a->Start();
	}
}

void xtb::Scene::Update() {
	for (Actor* a : actors) {
		a->Update();
	}
}

void xtb::Scene::Render(Camera& camera) {
	camera.Use();
	camera.renderTexture.BindFramebuffer();

	xtb::Graphics::Clear();
	
	for (xtb::Actor* a : actors) {
		a->Render();
	}

	camera.renderTexture.UnbindFramebuffer();
}

void xtb::Scene::GUI() {
	for (Actor* a : actors) {
		a->GUI();
	}
}