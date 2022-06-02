#pragma once

#include "etbdefs.h"
#include "Mesh.h"

namespace ETB {

	class Primitives {
	public:
		static DECLSPEC Mesh quad;
		// static DECLSPEC etb::Mesh Plane;
		static DECLSPEC Mesh cube;
		// static DECLSPEC etb::Mesh Sphere;
		// static DECLSPEC etb::Mesh Capsule;

		static void DECLSPEC GeneratePrimitives();

	private:
		static Primitives instance;

		Primitives();
	};

}