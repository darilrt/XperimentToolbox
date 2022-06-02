#include "File.h"
#include "Debug.h"

#include <sstream>

ETB::File::File(const std::string& _path) {
    std::ifstream file(_path, std::ios::in);
}

ETB::File::~File() {
}

std::string ETB::File::ReadLine() {
    std::string line;
    std::getline(file, line);
    return line;
}

void ETB::File::Close() {
    file.close();
}

bool ETB::File::Exists(const std::string& path) {
    std::ifstream file(path);
    return file.good();
}

std::string ETB::File::ReadAll(const std::string& path) {
    std::stringstream buffer;
    std::ifstream file(path, std::ios::in);

    if (file.is_open()) {
        std::string contents = "";

        while (file.peek() != EOF)
        {
            contents += (char)file.get();
        }
        file.close();

        return contents;
    }
    file.close();

    return std::string();
}
