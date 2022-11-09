#pragma once

#include "Asset.h"

namespace xtb {

	class MaterialAsset : public xtb::Asset {
	public:
		DECLSPEC static Asset* Create();
		DECLSPEC std::string GetTypeName();
		DECLSPEC void LoadAsset();
	};

}

