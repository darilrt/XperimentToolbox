#pragma once

#include <iostream>
#include <filesystem>
#include <unordered_map>

namespace xtb {
	
	class AssetDatabase;

	class Asset {
		friend class AssetDatabase;
	public:
		std::string path;
		
		inline std::string GetUUID() { return uuid; }
		
	private:
		std::string uuid;
		time_t mTime;
	};

	class AssetDatabase {
	public:
		DECLSPEC static std::string assetPath;

		DECLSPEC static void LoadAssets();

	private:
		AssetDatabase();

		static void LoadAsset(const std::filesystem::directory_entry& path);
		static void LoadMeta(const std::filesystem::directory_entry& path);

		static std::unordered_map<std::string, Asset*> assets;
	};

}