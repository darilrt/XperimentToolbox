#include "Asset.h"

REGISTER_ASSET(MaterialAsset, ".mat");

xtb::AssetFactory* xtb::AssetFactory::instance;

xtb::AssetFactory::AssetFactory() {
}