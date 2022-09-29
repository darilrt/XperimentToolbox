#include "RenderTexture.h"
#include "Screen.h"
#include "Debug.h"

ETB::RenderTexture::RenderTexture(int32_t width, int32_t height) : 
	color(width, height, TextureType::RGB), 
	depth(width, height, TextureType::Depth24) {

	glGenFramebuffers(1, &fbo);
	BindFramebuffer();

	glGenRenderbuffers(1, &rbo);
	SetRBOSize(width, height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth.texture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color.texture, 0);

	UnbindFramebuffer();
}

ETB::RenderTexture::~RenderTexture() {
	glDeleteFramebuffers(1, &fbo);
}

void ETB::RenderTexture::SetSize(int32_t width, int32_t height) {
	SetRBOSize(width, height);

	BindFramebuffer();
	color.SetSize(width, height);
//	depth.SetSize(width, height);

	depth.Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	depth.Unbind();

	UnbindFramebuffer();
}

void ETB::RenderTexture::BindFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	GLenum DrawBuffers[2] = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT };
	glDrawBuffers(1, DrawBuffers);
}

void ETB::RenderTexture::UnbindFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
}

void ETB::RenderTexture::SetRBOSize(int32_t width, int32_t height) {
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
