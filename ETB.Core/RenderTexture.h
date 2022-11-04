#pragma once

#include "etbdefs.h"
#include "Texture.h"

namespace xtb {
	
	class DECLSPEC RenderTexture {
	public:
		Texture color;
		Texture depth;

		RenderTexture(int32_t width, int32_t height);
		~RenderTexture();

		void SetSize(int32_t width, int32_t height);
		void BindFramebuffer();
		void UnbindFramebuffer();

	private:
		void SetRBOSize(int32_t width, int32_t height);

		uint32_t fbo; // Frame Buffer Object
		uint32_t rbo; // Render Buffer Object
	};

}