#pragma once

#include <iostream>
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

		static void LoadAsset(const std::string& path);
		static void LoadMeta(const std::string& path);

		static std::unordered_map<std::string, Asset*> assets;
	};

}