#pragma once

#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <string>

#include "etbdefs.h"

namespace xtb {

	class Uniform {
	public:
		enum Type {
			Unknow,
			Int,		// int
			Float,		// float
			Vector2,	// vec2
			Vector3,	// vec3
			Vector4,	// vec4
			Matrix4,
			Sampler2D	// GL_SAMPLER_2D
		};

		std::string name;
		Type type;

		DECLSPEC Uniform(std::string name, Type type);
	};

}