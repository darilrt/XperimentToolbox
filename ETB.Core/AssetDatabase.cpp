#include <filesystem>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <ostream>

#include "etb.h"
#include "AssetDatabase.h"
#include "Asset.h"

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
		AssetDatabase::LoadAsset(entry);
	}

	for (auto& asset : assets) {
		asset.second->LoadAsset();
	}
}

xtb::Asset* xtb::AssetDatabase::GetAssetByUUID(const std::string& uuid) {
	if (assets.count(uuid) != 0) {
		return assets[uuid];
	}

	return NULL;
}

std::string xtb::AssetDatabase::GetUUIDByPath(std::filesystem::path p) {
	for (auto e : assets) {
		if (std::filesystem::equivalent(e.second->path, p)) {
			return e.second->uuid;
		}
	}
	
	return "";
}

void xtb::AssetDatabase::LoadAsset(const directory_entry& entry) {
	const std::string ext = entry.path().extension().string();

	if (ext == ".meta") return;

	const std::string metaPath = entry.path().string() + ".meta";

	Asset* asset = xtb::AssetFactory::CreateAssetByExtension(ext);

	if (asset != NULL) {
		asset->path = entry.path();
		
		if (File::Exists(metaPath)) {
			LoadMeta(asset, entry);
		}
		else {
			asset->uuid = xtb::GetUUID();
			SaveMeta(asset, entry);
		}
		
		assets[asset->uuid] = asset;
	}
}

void xtb::AssetDatabase::LoadMeta(Asset* asset, const directory_entry& entry) {
	const std::string metaPath = entry.path().string() + ".meta";

	std::ifstream file(metaPath);
	nlohmann::json data;
	file >> data;

	if (!data.is_null() && data.contains("uuid")) {
		asset->uuid = data["uuid"].get<std::string>();
	}
	else {
		asset->uuid = xtb::GetUUID();
		SaveMeta(asset, entry);
	}
}

void xtb::AssetDatabase::SaveMeta(Asset* asset, const std::filesystem::directory_entry& entry) {
	nlohmann::json data = asset->Serialize();

	const std::string path = entry.path().string() + ".meta";
	
	std::ofstream file(path);
	file << std::setw(4) << data << std::endl;
}

void xtb::AssetDatabase::Rename(std::filesystem::path oldPath, std::filesystem::path newPath) {
	if (std::filesystem::is_directory(oldPath)) {
		for (auto e : assets) {
			if (e.second->path.string().find(oldPath.string()) != std::string::npos) {
				std::string newPathStr = e.second->path.string();
				newPathStr.replace(0, oldPath.string().length(), newPath.string());
				e.second->path = newPathStr;
			}
		}

		std::filesystem::rename(oldPath, newPath);
	}
	else {
		xtb::Asset* asset = xtb::AssetDatabase::GetAssetByUUID(xtb::AssetDatabase::GetUUIDByPath(oldPath.string()));
		
		if (asset != NULL) {
			asset->path = newPath;
		}

		std::filesystem::rename(oldPath, newPath);
	}
}