#pragma once

#include "etbdefs.h"
#include "Mesh.h"

#include <string>

namespace ETB {

	class OBJFile {
	public:
		DECLSPEC OBJFile(const std::string& path);
		DECLSPEC ~OBJFile();

		DECLSPEC Mesh GetMesh();

	private:
		std::string path;
		std::string source;
	};

	class DECLSPEC OBJLoader {
	public:
		static inline Mesh FromFile(const std::string& path) { return OBJFile(path).GetMesh(); }
	};

}