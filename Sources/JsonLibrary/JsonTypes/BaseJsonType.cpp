#include "BaseJsonType.h"

#include <utility>
#include "../JsonSerialized.h"
#include "../Exceptions/EmptyTypeException.h"


BaseJsonType::BaseJsonType() = default;

BaseJsonType::BaseJsonType(const BaseJsonType& other) : _jsonType(other._jsonType), _floatValue(other._floatValue),
                                          _intValue(other._intValue), _stringValue(other._stringValue),
                                          _jsonObjectValue(other._jsonObjectValue), _jsonArrayValue(other._jsonArrayValue)
{
}

BaseJsonType::BaseJsonType(int value) : _jsonType(JsonType::JsonInt), _intValue(value)
{
}

BaseJsonType::BaseJsonType(bool value) : _jsonType(JsonType::JsonBool), _boolValue(value)
{
}

BaseJsonType::BaseJsonType(float value) : _jsonType(JsonType::JsonFloat), _floatValue(value)
{
}

// BaseJsonType::BaseJsonType(const std::string& value) : _jsonType(JsonType::JsonString), _stringValue(value)
// {
// }

BaseJsonType::BaseJsonType(std::string value) : _jsonType(JsonType::JsonString), _stringValue(std::move(value))
{
}

BaseJsonType::BaseJsonType(const JsonObject& value) : _jsonType(JsonType::JsonObject), _jsonObjectValue(value)
{
}


BaseJsonType::BaseJsonType(const JsonArray& value) : _jsonType(JsonType::JsonArray), _jsonArrayValue(value)
{
}

BaseJsonType::BaseJsonType(const std::vector<int>& value) : _jsonType(JsonType::JsonArray), _jsonArrayValue(value)
{
}

BaseJsonType::BaseJsonType(const std::vector<JsonObject>& value) : _jsonType(JsonType::JsonArray), _jsonArrayValue(value)
{
}

BaseJsonType::BaseJsonType(const std::vector<std::string>& value) : _jsonType(JsonType::JsonArray), _jsonArrayValue(value)
{
}

BaseJsonType::BaseJsonType(const std::vector<float>& value) : _jsonType(JsonType::JsonArray), _jsonArrayValue(value)
{
}

BaseJsonType::~BaseJsonType() = default;

bool BaseJsonType::TryDecodeJsonType(const std::string& json, int startIndex, int& endIndex)
{
    if(_jsonObjectValue.TryDecodeJsonType(json, startIndex, endIndex))
    {
        _jsonType = JsonType::JsonObject;
        return true;
    }

    if(_jsonArrayValue.TryDecodeJsonType(json, startIndex, endIndex))
    {
        _jsonType = JsonType::JsonArray;
        return true;
    }

    if(_boolValue.TryDecodeJsonType(json, startIndex, endIndex))
    {
        _jsonType = JsonType::JsonBool;
        return true;
    }
    
    if(_intValue.TryDecodeJsonType(json, startIndex, endIndex))
    {
        _jsonType = JsonType::JsonInt;
        return true;
    }

    if(_floatValue.TryDecodeJsonType(json, startIndex, endIndex))
    {
        _jsonType = JsonType::JsonFloat;
        return true;
    }

    if(_stringValue.TryDecodeJsonType(json, startIndex, endIndex))
    {
        _jsonType = JsonType::JsonString;
        return true;
    }

    return false;
}

std::string BaseJsonType::EncodeJsonType() const
{
    switch (_jsonType)
    {
        case JsonType::JsonInt:
            return _intValue.EncodeJsonType();
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

JsonType BaseJsonType::GetType() const
{
    return _jsonType;
}

BaseJsonType::operator bool() const
{
    if(_jsonType == JsonType::JsonBool)
    {
        return _boolValue;
    }

    throw InvalidCastTypeException();
}

BaseJsonType::operator int() const
{
    if(_jsonType == JsonType::JsonInt)
    {
        return _intValue;
    }

    throw InvalidCastTypeException();
}

BaseJsonType::operator float() const
{
    if(_jsonType == JsonType::JsonFloat)
    {
        return _floatValue;
    }
    
    if(_jsonType == JsonType::JsonInt)
    {
        return _intValue;
    }

    throw InvalidCastTypeException();
}

BaseJsonType::operator std::string&()
{
    if(_jsonType == JsonType::JsonString)
    {
        return _stringValue.GetStr();
    }

    throw InvalidCastTypeException();
}

BaseJsonType::operator std::vector<bool>() const
{
    if(_jsonType == JsonType::JsonArray)
    {
        return _jsonArrayValue;
    }

    throw InvalidCastTypeException();
}

void BaseJsonType::DecodeObject(JsonSerialized& json_serialized)
{
    if(_jsonType != JsonType::JsonObject)
    {
        throw InvalidCastTypeException();
    }

    json_serialized.FromJson(_jsonObjectValue);
}

BaseJsonType::operator JsonObject() const
{
    if(_jsonType == JsonType::JsonObject)
    {
        return _jsonObjectValue;
    }

    throw InvalidCastTypeException();
}

BaseJsonType::operator std::vector<float>() const
{
    if(_jsonType == JsonType::JsonArray)
    {
        return _jsonArrayValue;
    }

    throw InvalidCastTypeException();
}

BaseJsonType::operator std::vector<int>() const
{
    if(_jsonType == JsonType::JsonArray)
    {
        return _jsonArrayValue;
    }

    throw InvalidCastTypeException();
}

BaseJsonType::operator std::vector<std::string>() const
{
    if(_jsonType == JsonType::JsonArray)
    {
        return _jsonArrayValue;
    }

    throw InvalidCastTypeException();
}

BaseJsonType::operator std::vector<JsonObject>() const
{
    if(_jsonType == JsonType::JsonArray)
    {
        return _jsonArrayValue;
    }

    throw InvalidCastTypeException();
}
