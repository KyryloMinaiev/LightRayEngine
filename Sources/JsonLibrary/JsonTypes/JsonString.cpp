#include "JsonString.h"
#include "./../Utils/JsonLiteralsUtils.h"
#include <sstream>

namespace JsonLibrary {
    bool JsonString::TryDecodeJsonType(const std::string &json, int startIndex, int &endIndex) {
        if (!JsonLiteralsUtils::IsJsonLiteral(json[startIndex], JsonLiterals::String)) {
            return false;
        }

        const int stringStartIndex = startIndex + 1;
        for (int i = stringStartIndex; i < json.length(); ++i) {
            const char currentChar = json[i];
            if (JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::String)) {
                _value = json.substr(stringStartIndex, i - stringStartIndex);
                endIndex = i;
                return true;
            }
        }

        return false;
    }

    std::string JsonString::EncodeJsonType() const {
        std::stringstream buffer;
        buffer << JsonLiteralsUtils::GetLiteral(JsonLiterals::String);
        buffer << _value;
        buffer << JsonLiteralsUtils::GetLiteral(JsonLiterals::String);
        return buffer.str();
    }

    std::string &JsonString::GetStr() {
        return _value;
    }

    JsonString::operator std::string() const {
        return _value;
    }
}
