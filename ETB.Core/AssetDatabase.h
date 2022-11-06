#pragma once

#include <iostream>
#include <filesystem>
#include <unordered_map>

#include "Asset.h"

namespace xtb {
	
	class AssetDatabase {
	public:
		DECLSPEC static std::string assetPath;

		DECLSPEC static void LoadAssets();
		DECLSPEC static Asset* GetAssetByUUID(const std::string& uuid);

		DECLSPEC static std::string GetUUIDByPath(const std::string& path);

		template<class T>
		static inline T* GetAssetByUUID(const std::string& uuid) {
			return dynamic_cast<T*>(GetAssetByUUID(uuid));
		}

	private:
		AssetDatabase();

		static void LoadAsset(const std::filesystem::directory_entry& path);
		static void LoadMeta(Asset* asset, const std::filesystem::directory_entry& path);
		static void SaveMeta(Asset* asset, const std::filesystem::directory_entry& path);

		static std::unordered_map<std::string, Asset*> assets;
	};

}