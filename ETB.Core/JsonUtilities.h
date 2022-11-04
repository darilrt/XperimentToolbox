#pragma once

#include <nlohmann/json.hpp>

namespace xtb {

	class JsonUtilities {
	public:
		static void Parse();
		static void Dump();
		static void FromFile(const std::string& path);
	};

}