#pragma once

#include <etb.h>
#include <vector>
#include <iostream>

using namespace ETB;

class AATorretActor  : public Actor {
public:
	std::vector<Texture*> texs;
	Mesh torretMesh;
	Transform transform;

	AATorretActor() {
		texs = {
			new Texture("Assets/Models/AA/T_AA_BC.png"),
			new Texture("Assets/Models/AA/T_AA_N.png"),
			new Texture("Assets/Models/AA/T_AA_R_M_AO.png")
		};

		ShaderLoader::Add("Assets/Shaders/AATorretLit.glsl", true);
		torretMesh = OBJLoader::FromFile("Assets/Models/AA/AA.obj");
		torretMesh.SetupMesh();
	}

	void Start() {
	}

	void Update() {
		transform.rotation *= glm::quat(glm::vec3(0, glm::radians(45.0f) * Time::deltaTime, 0));
	}

	void Render() {
		Shader& sh = ShaderLoader::Get("Assets/Shaders/AATorretLit.glsl");

		sh.Use();

		sh.SetMatrix("ETB_MATRIX_VP", Camera::GetActive()->GetMatrix());
		sh.SetMatrix("ETB_MATRIX_M", transform.GetMatrix());
		sh.SetVector2("_ScreenResolution", (glm::vec2)Screen::GetSize());
		sh.SetVector3("_worldCameraPos", Camera::GetActive()->transform.position);

		sh.SetSampler2D("_BaseColor", *texs[0]);
		sh.SetSampler2D("_NormalMap", *texs[1]);
		sh.SetSampler2D("_MaskMap", *texs[2]);

		Graphics::DrawMesh(torretMesh);
	}
};
