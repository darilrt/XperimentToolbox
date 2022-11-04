#pragma once

#include "etbdefs.h"

#include <fstream>

namespace xtb {

	class File {
	public:
		DECLSPEC File(const std::string& path);
		DECLSPEC ~File();

		std::string DECLSPEC ReadLine();

		inline bool DECLSPEC Eof() { return file.eof(); }
		void DECLSPEC Close();

		static bool DECLSPEC Exists(const std::string& path);
		static std::string DECLSPEC ReadAll(const std::string& path);

	private:
		std::ifstream file;
	};

}
