#pragma once

#include <string>

#include "IJsonType.h"

namespace JsonLibrary {
    class JsonFloat : public IJsonType {
    public:
        JsonFloat(const JsonFloat &other) : _value(other._value) {}

        JsonFloat() : _value(0) {}

        JsonFloat(float value) : _value(value) {}

        bool TryDecodeJsonType(const std::string &json, int startIndex, int &endIndex) override;

        std::string EncodeJsonType() const override;

        operator float() const;

    private:
        static bool TryDecodeFloatFromString(const std::string &floatString, float &result);

        float _value;
    };
}
