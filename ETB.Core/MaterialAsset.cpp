#include "MaterialAsset.h"

namespace xtb {
	REGISTER_ASSET(MaterialAsset, ".mat");

	Asset* MaterialAsset::Create() {
		return new MaterialAsset();
	}

	void MaterialAsset::LoadAsset() {

	}

	std::string MaterialAsset::GetTypeName() {
		return typeid(xtb::MaterialAsset).raw_name();
	}
}