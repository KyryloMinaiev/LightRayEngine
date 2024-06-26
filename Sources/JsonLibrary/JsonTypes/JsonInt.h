#pragma once

#include <string>

#include "IJsonType.h"

class JsonInt : public IJsonType
{
public:
    JsonInt(int value) : _value(value) { }
    JsonInt(const JsonInt& value) : _value(value._value) {}
    JsonInt() : _value(0) {}
    bool TryDecodeJsonType(const std::string& json, int startIndex, int& endIndex) override;
    std::string EncodeJsonType() const override;

    operator int() const;
    operator float() const;
private:
    static bool TryDecodeIntFromString(const std::string& intString, int& result);
    int _value;
};
