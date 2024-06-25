#pragma once
#include "IJsonType.h"
#include "JsonArray.h"
#include "JsonBool.h"
#include "JsonFloat.h"
#include "JsonInt.h"
#include "JsonObject.h"
#include "JsonString.h"
#include "JsonTypes.h"
#include "../Exceptions/InvalidCastTypeException.h"

class BaseJsonType : public IJsonType
{
public:
    BaseJsonType();
    BaseJsonType(const BaseJsonType& other);
    BaseJsonType(int value);
    BaseJsonType(bool value);
    BaseJsonType(float value);
    //BaseJsonType(const std::string& value);
    BaseJsonType(std::string value);
    BaseJsonType(const JsonObject& value);
    BaseJsonType(const JsonArray& value);
    BaseJsonType(const std::vector<int>& value);
    BaseJsonType(const std::vector<JsonObject>& value);
    BaseJsonType(const std::vector<std::string>& value);
    BaseJsonType(const std::vector<float>& value);
    ~BaseJsonType() override;

    bool TryDecodeJsonType(const std::string& json, int startIndex, int& endIndex) override;
    std::string EncodeJsonType() const override;

    JsonType GetType() const;
    
    operator bool() const;
    operator int() const;
    operator float() const;
    operator std::string&();
    operator JsonObject() const;
    operator std::vector<float>() const;
    operator std::vector<int>() const;
    operator std::vector<std::string>() const;
    operator std::vector<JsonObject>() const;
    operator std::vector<bool>() const;

    void DecodeObject(JsonSerialized& json_serialized);
    template <typename Json>
    void DecodeArray(std::vector<Json>& vector);
    template <typename Json>
    void EncodeArray(std::vector<Json>& vector);
    
private:
    JsonType _jsonType = JsonType::None;
    JsonFloat _floatValue;
    JsonInt _intValue;
    JsonBool _boolValue;
    JsonString _stringValue;
    JsonObject _jsonObjectValue;
    JsonArray _jsonArrayValue;
};

template <typename Json>
void BaseJsonType::DecodeArray(std::vector<Json>& vector)
{
    static_assert(std::is_base_of<JsonSerialized, Json>::value, "Cannon decode JsonArray into non serialized class!");
    
    if(_jsonType != JsonType::JsonArray)
    {
        throw InvalidCastTypeException();
    }
    
    std::vector<JsonObject> json_objects = _jsonArrayValue;
    for (auto& json_object : json_objects)
    {
        Json json;
        json.FromJson(json_object);
        vector.push_back(json);
    }
}

template <typename Json>
void BaseJsonType::EncodeArray(std::vector<Json>& vector)
{
    static_assert(std::is_base_of<JsonSerialized, Json>::value, "Cannon encode JsonArray with non serialized class!");
    _jsonType = JsonType::JsonArray;
    std::vector<JsonObject> json_objects;
    for (auto& json_object : vector)
    {
        JsonObject obj;
        json_object.ToJson(obj);
        json_objects.push_back(obj);
    }
    
    _jsonArrayValue = JsonArray(json_objects);
}





