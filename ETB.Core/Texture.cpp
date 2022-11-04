#include "Texture.h"

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"

#include "Debug.h"
#include "File.h"

xtb::Texture::Texture(int32_t width, int32_t height, TextureType t) {
	type = t;

	GenTextureBuffer();
	SetFilterMode(TextureFilterMode::Linear);
	SetSize(width, height);
}

xtb::Texture::Texture(const std::string& path) {
	if (!File::Exists(path)) {
		Debug::Print("Image \"" + path + "\" does not exists");
	}

	LoadImage(path);
}

xtb::Texture::~Texture() {
	if (texture) glDeleteTextures(1, &texture);
}

void xtb::Texture::LoadImage(const std::string& path) {
	uint32_t format = 0;

	int32_t w, h, n;
	uint8_t* image = stbi_load(path.c_str(), &w, &h, &n, 0);

	if (image == nullptr) {
		Debug::Print("Image \"" + path + "\" error on load (stbi_load)");
	}

	switch (n) {
	case 1: /* format = GL_GRAY; */ break;
	case 2: /* format = GL_GRAY; */ break;
	case 3: format = GL_RGB; break;
	case 4: format = GL_RGBA; break;
	default: break;
	}

	switch (format)  {
	case GL_RGB: type = TextureType::RGB; break;
	case GL_RGBA: type = TextureType::RGBA; break;
	default: break;
	}

	GenTextureBuffer();
	Bind();

	glTexImage2D(GL_TEXTURE_2D, 0, n, w, h, 0, format, GL_UNSIGNED_BYTE, image);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLfloat)TextureWrapMode::Repeat);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLfloat)TextureWrapMode::Repeat);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)TextureFilterMode::Linear);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)TextureFilterMode::Linear);
	
	Unbind();

	delete image;

	width = w;
	height = h;
}

void xtb::Texture::SetSize(int32_t w, int32_t h) {
	width = w;
	height = h;
	
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, (GLint)type, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	Unbind();
}

void xtb::Texture::SetWrapMode(TextureWrapMode wrapMode) {
	Bind();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLfloat)wrapMode);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLfloat)wrapMode);
	Unbind();
}

void xtb::Texture::SetFilterMode(TextureFilterMode filterMode) {
	Bind();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)filterMode);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)filterMode);
	Unbind();
}

void xtb::Texture::GenTextureBuffer() {
	if (texture) glDeleteTextures(1, &texture);

	glGenTextures(1, &texture);
}
