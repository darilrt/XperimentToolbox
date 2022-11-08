#pragma once

#include "etbdefs.h"
#include "Asset.h"
#include "Debug.h"
#include "Texture.h"

namespace xtb {

	class TextureAsset : public xtb::Asset {
	public:
		xtb::Texture* texture;
		
		void LoadAsset();

		DECLSPEC std::string GetTypeName();

		DECLSPEC static Asset* Create() {
			return new TextureAsset();
		}
	};

}