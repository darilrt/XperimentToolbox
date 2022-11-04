#include <filesystem>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>

#include "etb.h"
#include "AssetDatabase.h"

using namespace std::filesystem;

std::unordered_map<std::string, xtb::Asset*> xtb::AssetDatabase::assets;
std::string xtb::AssetDatabase::assetPath = "";

xtb::AssetDatabase::AssetDatabase() {
}

void ListRecursiveAssets(const std::string& path, std::vector<directory_entry>& list) {
	for (const directory_entry& entry : directory_iterator(path)) {
		list.push_back(entry);

		if (entry.is_directory()) {
			ListRecursiveAssets(entry.path().string(), list);
		}
	}
}

void xtb::AssetDatabase::LoadAssets() {
	std::vector<directory_entry> assetList;
	ListRecursiveAssets(assetPath, assetList);

	for (directory_entry& entry : assetList) {
		// AssetDatabase::LoadAsset(entry);
		xtb::Debug::Print(entry.path().string());
	}
}

void xtb::AssetDatabase::LoadAsset(const directory_entry& entry) {
	const std::string metaPath = entry.path().string() + ".meta";

	if (File::Exists(metaPath)) {
		LoadMeta(entry);
	}
	else {
		
	}
}

void xtb::AssetDatabase::LoadMeta(const directory_entry& entry) {
	using json = nlohmann::json;
	const std::string metaPath = entry.path().string() + ".meta";

	std::ifstream f(metaPath);
	json data = json::parse(f);

	Asset asset;

	if (data.contains("uuid")) {
		asset.uuid = data["uuid"].get<std::string>();

		xtb::Debug::Print(data["uuid"].get<std::string>());
	}
	else {
		data["uuid"] = xtb::GetUUID();
	}
}