#include "Debug.h"
#include "Asset.h"
#include "TextureAsset.h"

namespace xtb {
	REGISTER_ASSET(TextureAsset, ".png", ".jpg");

	void TextureAsset::LoadAsset() {
		Debug::Print(path.string() + " " + GetUUID());

		if (texture != NULL) {
			delete texture;
		}

		texture = new Texture(path.string());
	}

}