#pragma once

#include <filesystem>
#include <iostream>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

#include "etbdefs.h"
#include "AssetDatabase.h"

#define REGISTER_ASSET(T, ...) \
	static bool xtb_IsRegistered_##T = xtb::AssetFactory::GetInstance()->Register({ ##__VA_ARGS__ }, T::Create)

namespace xtb {

	class Asset {
		friend class AssetDatabase;
	public:
		std::filesystem::path path;

		inline std::string GetUUID() { return uuid; }

		DECLSPEC virtual nlohmann::json Serialize();
		
		DECLSPEC virtual std::string GetTypeName();

		DECLSPEC virtual void LoadAsset() = 0;
		
		DECLSPEC virtual void SaveAsset();

		template<class T>
		inline static T* GetAsset(std::string uuid) {
			return xtb::AssetDatabase::GetAssetByUUID<T>(uuid);
		}

	private:
		std::string uuid;
		time_t mTime;
	}; 

	class AssetFactory {
	public:
		DECLSPEC static bool Register(std::vector<std::string> extensions, Asset* (*_creator)()) {
			AssetFactory* instance = AssetFactory::GetInstance();

			for (std::string extension : extensions) {
				instance->assetFactory[extension] = _creator;
			}

			return true;
		}

		DECLSPEC static Asset* CreateAssetByExtension(const std::string& ext) {
			AssetFactory* instance = AssetFactory::GetInstance();
			
			if (instance->assetFactory.count(ext) != 0) {
				return AssetFactory::GetInstance()->assetFactory[ext]();
			}

			return NULL;
		}

		DECLSPEC static AssetFactory* GetInstance() {
			return AssetFactory::instance != NULL ? AssetFactory::instance : (AssetFactory::instance = new AssetFactory);
		}

	private:
		DECLSPEC static AssetFactory* instance;
		std::map<std::string, Asset* (*)()> assetFactory;

		DECLSPEC AssetFactory();
	};

}
