#include "FileUtils.h"

#include "../Exceptions/FileNotExistsException.h"

namespace JsonLibrary {
    std::string FileUtils::ReadFile(const std::string &path) {
        std::string result;
        std::ifstream fileStream(path);
        if (fileStream.is_open()) {
            std::stringstream buffer;
            buffer << fileStream.rdbuf();
            result = buffer.str();
            buffer.clear();
        } else {
            throw FileNotExistsException(path);
        }

        fileStream.close();
        return result;
    }

    void FileUtils::WriteFile(const std::string &path, const std::string &content) {
        std::ofstream fileStream(path);
        long size = content.size();
        fileStream.write(content.c_str(), size);
        fileStream.close();
    }
}
