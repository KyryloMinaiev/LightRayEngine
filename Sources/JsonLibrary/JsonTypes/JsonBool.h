#pragma once
#include "IJsonType.h"

namespace JsonLibrary {
    class JsonBool : IJsonType {
    public:
        JsonBool() : _value(false) {}

        JsonBool(bool value) : _value(value) {}

        JsonBool(const JsonBool &other) : _value(other._value) {}

        bool TryDecodeJsonType(const std::string &json, int startIndex, int &endIndex) override;

        std::string EncodeJsonType() const override;

        operator bool() const;

    private:
        static constexpr auto k_stringTrueValue = "true";
        static constexpr auto k_stringFalseValue = "false";

        bool _value;
    };
}
