#include "BaseJsonType.h"

#include <utility>
#include "../JsonSerialized.h"
#include "../Exceptions/EmptyTypeException.h"

namespace JsonLibrary {
    BaseJsonType::BaseJsonType() = default;

    BaseJsonType::BaseJsonType(const BaseJsonType &other) : _jsonType(other._jsonType), _floatValue(other._floatValue),
                                                            _stringValue(other._stringValue),
                                                            _jsonObjectValue(other._jsonObjectValue),
                                                            _jsonArrayValue(other._jsonArrayValue) {
    }

    BaseJsonType::BaseJsonType(int value) : _jsonType(JsonType::JsonFloat), _floatValue(value) {
    }

    BaseJsonType::BaseJsonType(bool value) : _jsonType(JsonType::JsonBool), _boolValue(value) {
    }

    BaseJsonType::BaseJsonType(float value) : _jsonType(JsonType::JsonFloat), _floatValue(value) {
    }

    BaseJsonType::BaseJsonType(std::string value) : _jsonType(JsonType::JsonString), _stringValue(std::move(value)) {
    }

    BaseJsonType::BaseJsonType(const JsonObject &value) : _jsonType(JsonType::JsonObject), _jsonObjectValue(value) {
    }


    BaseJsonType::BaseJsonType(const JsonArray &value) : _jsonType(JsonType::JsonArray), _jsonArrayValue(value) {
    }

    BaseJsonType::BaseJsonType(const std::vector<int> &value) : _jsonType(JsonType::JsonArray), _jsonArrayValue(value) {
    }

    BaseJsonType::BaseJsonType(const std::vector<JsonObject> &value) : _jsonType(JsonType::JsonArray),
                                                                       _jsonArrayValue(value) {
    }

    BaseJsonType::BaseJsonType(const std::vector<std::string> &value) : _jsonType(JsonType::JsonArray),
                                                                        _jsonArrayValue(value) {
    }

    BaseJsonType::BaseJsonType(const std::vector<float> &value) : _jsonType(JsonType::JsonArray),
                                                                  _jsonArrayValue(value) {
    }

    BaseJsonType::~BaseJsonType() = default;

    bool BaseJsonType::TryDecodeJsonType(const std::string &json, int startIndex, int &endIndex) {
        if (_jsonObjectValue.TryDecodeJsonType(json, startIndex, endIndex)) {
            _jsonType = JsonType::JsonObject;
            return true;
        }

        if (_jsonArrayValue.TryDecodeJsonType(json, startIndex, endIndex)) {
            _jsonType = JsonType::JsonArray;
            return true;
        }

        if (_boolValue.TryDecodeJsonType(json, startIndex, endIndex)) {
            _jsonType = JsonType::JsonBool;
            return true;
        }

        if (_floatValue.TryDecodeJsonType(json, startIndex, endIndex)) {
            _jsonType = JsonType::JsonFloat;
            return true;
        }

        if (_stringValue.TryDecodeJsonType(json, startIndex, endIndex)) {
            _jsonType = JsonType::JsonString;
            return true;
        }

        return false;
    }

    std::string BaseJsonType::EncodeJsonType() const {
        switch (_jsonType) {
            case JsonType::JsonBool:
                return _boolValue.EncodeJsonType();
            case JsonType::JsonFloat:
                return _floatValue.EncodeJsonType();
            case JsonType::JsonString:
                return _stringValue.EncodeJsonType();
            case JsonType::JsonObject:
                return _jsonObjectValue.EncodeJsonType();
            case JsonType::JsonArray:
                return _jsonArrayValue.EncodeJsonType();
            case JsonType::None:
                throw EmptyTypeException();
        }

        return {};
    }

    JsonType BaseJsonType::GetType() const {
        return _jsonType;
    }

    BaseJsonType::operator bool() {
        return GetJsonType<bool, JsonBool>(JsonType::JsonBool, _boolValue);
    }

    BaseJsonType::operator int() {
        return GetJsonType<int, JsonFloat>(JsonType::JsonFloat, _floatValue);
    }

    BaseJsonType::operator float() {
        return GetJsonType<float, JsonFloat>(JsonType::JsonFloat, _floatValue);
    }

    BaseJsonType::operator std::string() {
        return GetJsonType<std::string, JsonString>(JsonType::JsonString, _stringValue);
    }

    BaseJsonType::operator std::vector<bool>() {
        return GetJsonType<std::vector<bool>, JsonArray>(JsonType::JsonArray, _jsonArrayValue);
    }

    void BaseJsonType::DecodeObject(JsonSerialized &json_serialized) {
        if (_jsonType != JsonType::JsonObject) {
            throw InvalidCastTypeException(JsonType::JsonObject, _jsonType);
        }

        json_serialized.FromJson(_jsonObjectValue);
    }

    BaseJsonType::operator JsonObject() {
        return GetJsonType<JsonObject, JsonObject>(JsonType::JsonObject, _jsonObjectValue);
    }

    BaseJsonType::operator std::vector<float>() {
        return GetJsonType<std::vector<float>, JsonArray>(JsonType::JsonArray, _jsonArrayValue);
    }

    BaseJsonType::operator std::vector<int>() {
        return GetJsonType<std::vector<int>, JsonArray>(JsonType::JsonArray, _jsonArrayValue);
    }

    BaseJsonType::operator std::vector<std::string>() {
        return GetJsonType<std::vector<std::string>, JsonArray>(JsonType::JsonArray, _jsonArrayValue);
    }

    BaseJsonType::operator std::vector<JsonObject>() {
        return GetJsonType<std::vector<JsonObject>, JsonArray>(JsonType::JsonArray, _jsonArrayValue);
    }

    bool BaseJsonType::TypeCheck(JsonType jsonType) {
        return jsonType == _jsonType;
    }
}
