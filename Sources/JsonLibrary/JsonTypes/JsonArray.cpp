#include "JsonArray.h"

#include <sstream>
#include "BaseJsonType.h"
#include "./../Exceptions/InvalidCastTypeException.h"
#include "./../Utils/JsonLiteralsUtils.h"

namespace JsonLibrary {
    JsonArray::~JsonArray() = default;

    JsonArray::JsonArray() = default;

    JsonArray::JsonArray(const std::vector<int> &array) : _vectorType(JsonType::JsonFloat) {
        _array = {array.begin(), array.end()};
    }

    JsonArray::JsonArray(const std::vector<float> &array) : _vectorType(JsonType::JsonFloat) {
        _array = {array.begin(), array.end()};
    }

    JsonArray::JsonArray(const std::vector<bool> &array) : _vectorType(JsonType::JsonBool) {
        _array = {array.begin(), array.end()};
    }

    JsonArray::JsonArray(const std::vector<std::string> &array) : _vectorType(JsonType::JsonString) {
        _array = {array.begin(), array.end()};
    }

    JsonArray::JsonArray(const std::vector<JsonObject> &array) : _vectorType(JsonType::JsonObject) {
        _array = {array.begin(), array.end()};
    }

    JsonArray::JsonArray(const JsonArray &other) : _vectorType(other._vectorType) {
        _array = {other._array.begin(), other._array.end()};
    }

    JsonArray::operator std::vector<int>() {
        return GetJsonType<int>(JsonType::JsonFloat);
    }

    JsonArray::operator std::vector<float>() {
        return GetJsonType<float>(JsonType::JsonFloat);
    }

    JsonArray::operator std::vector<std::string>() {
        return GetJsonType<std::string>(JsonType::JsonString);
    }

    JsonArray::operator std::vector<bool>() {
        return GetJsonType<bool>(JsonType::JsonBool);
    }

    JsonArray::operator std::vector<JsonObject>() {
        return GetJsonType<JsonObject>(JsonType::JsonObject);
    }

    BaseJsonType &JsonArray::operator[](const int &index) {
        return _array[index];
    }

    bool JsonArray::TryDecodeJsonType(const std::string &json, int startIndex, int &endIndex) {
        if (!JsonLiteralsUtils::IsJsonLiteral(json[startIndex], JsonLiterals::ArrayStart)) {
            return false;
        }

        bool foundFirstValue = false;
        bool waitingNextValue = false;
        int index = 0;

        for (int i = startIndex + 1; i < json.length(); ++i) {
            const char currentChar = json[i];
            endIndex = i;

            //1. Don't take into account any spaces
            if (JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::Space)) {
                continue;
            }

            if (JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::ArrayEnd)) {
                return true;
            }

            //2. Try to find first value:
            BaseJsonType base_json;
            if (!foundFirstValue && base_json.TryDecodeJsonType(json, i, index)) {
                i = index;
                foundFirstValue = true;
                _vectorType = base_json.GetType();
                _array.push_back(base_json);
                continue;
            }

            //3. Wait for a comma or a bracket as a sign that the field ended
            if (!waitingNextValue && foundFirstValue &&
                JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::Comma)) {
                waitingNextValue = true;
                continue;
            }

            //4. Checking if there are other values of the same type
            if (waitingNextValue && foundFirstValue && base_json.TryDecodeJsonType(json, i, index)) {
                i = index;
                waitingNextValue = false;
                if (_vectorType != base_json.GetType()) {
                    return false;
                }

                _array.push_back(base_json);
                continue;
            }

            if (!waitingNextValue && JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::ArrayEnd)) {
                return true;
            }
        }

        return false;
    }

    std::string JsonArray::EncodeJsonType() const {
        std::stringstream buffer;
        buffer << JsonLiteralsUtils::GetLiteral(JsonLiterals::ArrayStart);
        buffer << JsonLiteralsUtils::GetLiteral(JsonLiterals::NewLine);

        for (auto it = _array.begin(); it < _array.end(); ++it) {
            buffer << it->EncodeJsonType();
            if (it != _array.end() - 1) {
                buffer << JsonLiteralsUtils::GetLiteral(JsonLiterals::Comma);
            }

            buffer << JsonLiteralsUtils::GetLiteral(JsonLiterals::NewLine);
        }

        buffer << JsonLiteralsUtils::GetLiteral(JsonLiterals::ArrayEnd);
        return buffer.str();
    }

    template<typename T>
    std::vector<T> JsonArray::GetJsonType(JsonType jsonType) {
        if (_array.empty()) {
            return {};
        }

        if (_vectorType != jsonType) {
            throw InvalidCastTypeException(jsonType, _vectorType);
        }

        std::vector<T> returnVector;
        returnVector.reserve(_array.size());
        for (auto& base_json: _array) {
            returnVector.push_back(static_cast<T>(base_json));
        }

        return returnVector;
    }
}
