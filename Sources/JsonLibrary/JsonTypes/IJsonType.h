#pragma once

#include <string>

namespace JsonLibrary {
    class IJsonType {
    public:
        virtual ~IJsonType() = default;

        virtual bool TryDecodeJsonType(const std::string &json, int startIndex, int &endIndex) = 0;

        [[nodiscard]] virtual std::string EncodeJsonType() const = 0;
    };
}
