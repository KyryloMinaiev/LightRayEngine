#include "JsonBool.h"

#include <algorithm>

bool JsonBool::TryDecodeJsonType(const std::string& json, int startIndex, int& endIndex)
{
    std::string trueStr = json.substr(startIndex, 4);
    std::transform(trueStr.begin(), trueStr.end(), trueStr.begin(),
        [](unsigned char c){ return std::tolower(c); });
    if(trueStr == k_stringTrueValue)
    {
        _value = true;
        endIndex = startIndex + 3;
        return true;
    }

    std::string falseStr = json.substr(startIndex, 5);
    std::transform(falseStr.begin(), falseStr.end(), falseStr.begin(),
            [](unsigned char c){ return std::tolower(c); });
    if(falseStr == k_stringFalseValue)
    {
        _value = false;
        endIndex = startIndex + 4;
        return true;
    }

    return false;
}

std::string JsonBool::EncodeJsonType() const
{
    return _value ? k_stringTrueValue : k_stringFalseValue;
}

JsonBool::operator bool() const
{
    return _value;
}
