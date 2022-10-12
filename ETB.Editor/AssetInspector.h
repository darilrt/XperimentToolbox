#pragma once

#include <filesystem>

class AssetInspector {
public:
	std::filesystem::path resourcePath;

	virtual void Start() = 0;
	virtual void GUI() = 0;
};

