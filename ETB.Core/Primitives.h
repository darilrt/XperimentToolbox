#pragma once

#include "etbdefs.h"
#include "Mesh.h"

namespace ETB {

	class Primitives {
	public:
		static DECLSPEC Mesh quad;
		static DECLSPEC Mesh cube;
		static DECLSPEC Mesh sphere;

		static void DECLSPEC GeneratePrimitives();

	private:
		static Primitives instance;

		Primitives();
	};

}