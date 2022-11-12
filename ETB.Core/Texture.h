#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <string>

#include "etbdefs.h"
#include "Asset.h"

namespace xtb {

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

	class Texture : public Asset {
		friend class RenderTexture;

	public:
		DECLSPEC Texture();
		DECLSPEC Texture(int32_t width, int32_t height, TextureType type);
		DECLSPEC Texture(const std::string& path);
		DECLSPEC ~Texture();

		DECLSPEC void LoadImage(const std::string& path);

		DECLSPEC void SetSize(int32_t width, int32_t height);
		
		DECLSPEC void SetWrapMode(TextureWrapMode wrapMode);
		
		DECLSPEC void SetFilterMode(TextureFilterMode filterMode);
		
		inline void Bind() { glBindTexture(GL_TEXTURE_2D, texture); }
		
		inline void Unbind() { glBindTexture(GL_TEXTURE_2D, NULL); }

		inline int32_t GetWidth() { return width; }
		
		inline int32_t GetHeight() { return height; }
		
		inline uint32_t GetID() { return texture; }

		inline TextureType GetType() { return type; }

		// inline TextureWrapMode GetWrapMode() { return wrapMode; }

		// inline TextureFilterMode GetFilterMode() { return filterMode; }

		// Asset overrides
		
		DECLSPEC std::string GetTypeName();

		DECLSPEC void LoadAsset();

		DECLSPEC void SaveAsset();

		DECLSPEC static Asset* Create();

	private:
		DECLSPEC void GenTextureBuffer();

		uint32_t texture = 0;
		TextureType type;
		int32_t width;
		int32_t height;
	};
	
}
