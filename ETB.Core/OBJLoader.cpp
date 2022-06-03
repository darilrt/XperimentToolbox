#include "OBJLoader.h"

#include "Debug.h"
#include "File.h"
#include "Mesh.h"

#include <map>
#include <string>
#include <sstream>

ETB::OBJFile::OBJFile(const std::string& _path) {
    if (!File::Exists(_path)) {
        Debug::Print("Import OBJ error: Couldn't import file \"" + _path + "\"");
        return;
    }

    path = _path;
}

ETB::OBJFile::~OBJFile() {
}

ETB::Mesh ETB::OBJFile::GetMesh() {
    Mesh tmp;
    Mesh mesh;

    std::ifstream file(path, std::ios::in);
    std::string header;

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ssLine(line);

        ssLine >> header >> std::ws;

        if (header == "v") {
            glm::vec3 v;
            ssLine >> v.x >> v.y >> v.z;
            tmp.vertices.push_back({ v.x, v.y, v.z });
        }
        else if (header == "vn") {
            glm::vec3 vn;
            ssLine >> vn.x >> vn.y >> vn.z;
            tmp.normals.push_back(vn);
        }
        else if (header == "vt") {
            glm::vec3 vt;
            ssLine >> vt.x >> vt.y;
            tmp.uv.push_back(vt);
        }
        else if (header == "f") {
            int v, t, n;
            size_t size = 0;

            for (int32_t i = 0; !ssLine.eof() && ssLine.peek() != -1; i++) {
                ssLine >> v;

                if (ssLine.peek() == '/') {
                    ssLine.get();

                    if (ssLine.peek() == '/') {
                        ssLine.get();
                        ssLine >> n;

                        mesh.vertices.push_back(tmp.vertices[v - 1]);
                        mesh.uv.push_back({ 0, 0 });
                        mesh.normals.push_back(tmp.normals[n - 1]);
                    }
                    else {
                        ssLine >> t;

                        if (ssLine.peek() == '/') {
                            ssLine.get();
                            ssLine >> n;

                            mesh.vertices.push_back(tmp.vertices[v - 1]);
                            mesh.uv.push_back(tmp.uv[t - 1]);
                            mesh.normals.push_back(tmp.normals[n - 1]);
                        }
                    }
                }

                size++;
            }

            const size_t i = mesh.vertices.size();

            if (size > 3) {
                mesh.elements.push_back({ i - 4, i - 3, i - 2 });
                mesh.elements.push_back({ i - 4, i - 2, i - 1 });
            }
            else {
                mesh.elements.push_back({ i - 3, i - 2, i - 1 });
            }
        }
    }

    file.close();

    return mesh;
}
