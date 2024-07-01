#pragma once

#include "JsonLibraryException.h"

namespace JsonLibrary {
    class FileNotExistsException : public JsonLibraryException {
    public:
        explicit FileNotExistsException(const std::string &filePath) : JsonLibraryException(
                std::string("File does not exists at path: " + filePath)) {
        }

    private:
    };
}
