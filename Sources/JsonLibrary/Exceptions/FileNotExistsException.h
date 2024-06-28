#pragma once
#include <exception>
#include <string>

namespace JsonLibrary {
    class FileNotExistsException : public std::exception {
    public:
        FileNotExistsException(const std::string &filePath) : exception(
                std::string("File does not exists at path: " + filePath).c_str()) {
        }
    };
}
