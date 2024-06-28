#include "JsonInt.h"
#include "./../Utils/JsonLiteralsUtils.h"

namespace JsonLibrary {
    bool JsonInt::TryDecodeJsonType(const std::string &json, int startIndex, int &endIndex) {
        bool intStarted = false;
        int startIntIndex = startIndex;

        for (int i = startIndex; i < json.length(); ++i) {
            const char currentChar = json[i];
            //Skip all spaces until found something else
            if (!intStarted && JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::Space)) {
                continue;
            }

            if (!intStarted) {
                intStarted = true;
                startIntIndex = i;
            }

            //It means that it's a float
            if (JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::Dot)) {
                return false;
            }

            //Possible endings for the field are comma or space
            const bool isIntEnded = JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::Space) ||
                                    JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::Comma) ||
                                    JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::ObjectEnd) ||
                                    JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::ArrayEnd);
            if (isIntEnded) {
                endIndex = i - 1;
                const std::string intString = json.substr(startIntIndex, i - startIntIndex);
                try {
                    return TryDecodeIntFromString(intString, _value);
                }
                catch (...) {
                    return false;
                }
            }
        }

        return false;
    }

    std::string JsonInt::EncodeJsonType() const {
        return std::to_string(_value);
    }

    JsonInt::operator int() const {
        return _value;
    }

    JsonInt::operator float() const {
        return static_cast<float>(_value);
    }

    bool JsonInt::TryDecodeIntFromString(const std::string &intString, int &result) {
        std::size_t characterCount;
        result = std::stoi(intString, &characterCount);
        if (intString.size() != characterCount) {
            return false;
        }

        return true;
    }
}
