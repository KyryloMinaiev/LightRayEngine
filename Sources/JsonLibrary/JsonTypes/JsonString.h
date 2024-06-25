#pragma once

#include <string>
#include "IJsonType.h"

class JsonString : public IJsonType
{
public:
    JsonString() = default;
    JsonString(std::string str) : _value(std::move(str)) { }
    JsonString(const JsonString& other) : _value(other._value) {}

    bool TryDecodeJsonType(const std::string& json, int startIndex, int& endIndex) override;
    std::string EncodeJsonType() const override;

    std::string& GetStr();

    operator std::string() const;
private:
    std::string _value;
};
