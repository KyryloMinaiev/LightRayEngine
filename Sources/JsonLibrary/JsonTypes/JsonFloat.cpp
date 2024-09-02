#include "JsonFloat.h"
#include "./../Utils/JsonLiteralsUtils.h"

namespace JsonLibrary {
    bool JsonFloat::TryDecodeJsonType(const std::string &json, int startIndex, int &endIndex) {
        bool floatStarted = false;
        int floatIntIndex = startIndex;

        for (int i = startIndex; i < json.length(); ++i) {
            const char currentChar = json[i];
            const bool isSpace = JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::Space);

            if (!floatStarted && isSpace) {
                floatIntIndex = i + 1;
                continue;
            }

            floatStarted = true;
            const bool isFloatEnded = isSpace ||
                                      JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::Comma) ||
                                      JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::ObjectEnd) ||
                                      JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::ArrayEnd);
            if (isFloatEnded) {
                endIndex = i - 1;
                const std::string floatString = json.substr(floatIntIndex, i - floatIntIndex);
                try {
                    return TryDecodeFloatFromString(floatString, _value);
                }
                catch (...) {
                    return false;
                }
            }
        }

        return false;
    }

    std::string JsonFloat::EncodeJsonType() const {
        return std::to_string(_value);
    }

    JsonFloat::operator float() const {
        return _value;
    }

    bool JsonFloat::TryDecodeFloatFromString(const std::string &floatString, float &result) {
        std::size_t characterCount;
        result = std::stof(floatString, &characterCount);
        if (floatString.size() == characterCount) {
            return true;
        }

        result = std::stoi(floatString, &characterCount);
        if (floatString.size() == characterCount) {
            return true;
        }

        return true;
    }

    JsonFloat::operator int() const {
        return _value;
    }
}
