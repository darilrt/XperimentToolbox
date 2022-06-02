#pragma once

#include "etbdefs.h"

#include <GL/glew.h>
#include <GL/GL.h>
#include <string>

namespace ETB {

	class DECLSPEC Texture {
	public:
		Texture(const std::string& path);
		~Texture();

		void LoadImage(const std::string& path);
		inline void BindTexture() { glBindTexture(GL_TEXTURE_2D, texture); }

		inline int32_t GetWidth() { return width; }
		inline int32_t GetHeight() { return height; }

	private:
		uint32_t texture;
		int32_t width;
		int32_t height;
	};
	
}
