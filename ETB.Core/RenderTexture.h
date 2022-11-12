#pragma once

#include "etbdefs.h"
#include "Texture.h"

namespace xtb {
	
	class RenderTexture {
	public:
		Texture color;
		Texture depth;

		DECLSPEC RenderTexture(int32_t width, int32_t height);
		DECLSPEC ~RenderTexture();

		DECLSPEC void SetSize(int32_t width, int32_t height);
		DECLSPEC void BindFramebuffer();
		DECLSPEC void UnbindFramebuffer();

	private:
		DECLSPEC void SetRBOSize(int32_t width, int32_t height);

		uint32_t fbo; // Frame Buffer Object
		uint32_t rbo; // Render Buffer Object
	};

}