#include <filesystem>
#include <iostream>
#include <vector>

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
		const std::string& path = entry.path().string();
		AssetDatabase::LoadAsset(path);
	}
}

void xtb::AssetDatabase::LoadAsset(const std::string& path) {
	const std::string metaPath = path + ".meta";

	if (File::Exists(metaPath)) {
		LoadMeta(metaPath);
	}
	else {
		
	}
}

void xtb::AssetDatabase::LoadMeta(const std::string& path) {
	
}