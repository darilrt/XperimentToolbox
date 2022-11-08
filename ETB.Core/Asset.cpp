#include "Asset.h"

REGISTER_ASSET(MaterialAsset, ".mat");

xtb::AssetFactory* xtb::AssetFactory::instance;

xtb::AssetFactory::AssetFactory() {
}

nlohmann::json xtb::Asset::Serialize() {
	nlohmann::json obj;

	obj["uuid"] = uuid;

	return obj;
}

std::string xtb::Asset::GetTypeName() {
	return std::string(typeid(xtb::Asset).raw_name());
}
