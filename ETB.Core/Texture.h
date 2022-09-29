#pragma once

#include "etbdefs.h"

#include <GL/glew.h>
#include <GL/GL.h>
#include <string>

namespace ETB {

	enum class TextureWrapMode {
		Repeat = GL_REPEAT,
		Clamp = GL_CLAMP_TO_EDGE,
		Mirror = GL_MIRRORED_REPEAT
	};

	enum class TextureFilterMode {
		Linear = GL_LINEAR,
		Nearest = GL_NEAREST,
		NearestMinmapNearest = GL_NEAREST_MIPMAP_NEAREST,
		NearestMinmapLinear = GL_NEAREST_MIPMAP_LINEAR,
		LinearMinmapNearest = GL_LINEAR_MIPMAP_NEAREST,
		LinearMinmapLinear = GL_LINEAR_MIPMAP_LINEAR
	};

	enum class TextureType {
		RGB = GL_RGB,
		RGBA = GL_RGBA,
		Depth16 = GL_DEPTH_COMPONENT16,
		Depth24 = GL_DEPTH_COMPONENT24,
		Depth32 = GL_DEPTH_COMPONENT32,
	};

	class DECLSPEC Texture {
		friend class RenderTexture;

	public:
		Texture(int32_t width, int32_t height, TextureType type);
		Texture(const std::string& path);
		~Texture();

		void LoadImage(const std::string& path);

		void SetSize(int32_t width, int32_t height);
		void SetWrapMode(TextureWrapMode wrapMode);
		void SetFilterMode(TextureFilterMode filterMode);
		
		inline void Bind() { glBindTexture(GL_TEXTURE_2D, texture); }
		inline void Unbind() { glBindTexture(GL_TEXTURE_2D, NULL); }

		inline int32_t GetWidth() { return width; }
		inline int32_t GetHeight() { return height; }

		inline uint32_t GetTextureId() { return texture; }

	private:
		void GenTextureBuffer();

		TextureType type;
		uint32_t texture = 0;
		int32_t width;
		int32_t height;
	};
	
}
