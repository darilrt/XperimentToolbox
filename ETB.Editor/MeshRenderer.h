#pragma once

#include <etb.h>
#include <Component.h>

namespace xtb {
	
	class MeshRenderer : public Component {
	public:
		MeshRenderer();

		DECLSPEC void Start();
		DECLSPEC void Render();
		DECLSPEC void InspectorRender();

		inline void SetMesh(Mesh* mesh) { this->mesh = mesh; }
		inline void SetMaterial(Material* material) { this->material = material; }

		inline Mesh* GetMesh() { return mesh; }
		inline Material* GetMaterial() { return material; }

	private:
		Mesh* mesh;
		Material* material;
	};

}
