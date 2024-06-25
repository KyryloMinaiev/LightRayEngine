#include "JsonLibrary.h"

#include "Utils/FileUtils.h"
#include "JsonSerialized.h"
#include "Utils/JsonDecoder.h"
#include "JsonTypes/BaseJsonType.h"

bool JsonLibrary::FromJsonFile(const std::string& path, JsonSerialized& obj)
{
    std::string json = FileUtils::ReadFile(path);
    return FromJsonString(json, obj);
}

JsonObject JsonLibrary::LoadJsonFile(const std::string& path)
{
    std::string json = FileUtils::ReadFile(path);
    json.erase(std::remove(json.begin(), json.end(), '\n'), json.end());
    JsonObject jsonObject;
    JsonDecoder::TryDecodeJson(json, jsonObject);
    return jsonObject;
}

bool JsonLibrary::FromJsonString(std::string& json, JsonSerialized& obj)
{
    json.erase(std::remove(json.begin(), json.end(), '\n'), json.end());
    JsonObject jsonObject;
    const bool result = JsonDecoder::TryDecodeJson(json, jsonObject);
    if(result)
    {
        obj.FromJson(jsonObject);
    }

    return result;
}

void JsonLibrary::FromJsonObject(JsonObject& jsonObject, JsonSerialized& obj)
{
    obj.FromJson(jsonObject);
}

void JsonLibrary::DecodeJsonObjectField(JsonObject& parentObject, const std::string& fieldName, JsonSerialized& obj)
{
    JsonObject jsonObject = parentObject[fieldName];
    FromJsonObject(jsonObject, obj);
}

std::string JsonLibrary::ToJson(const JsonSerialized& obj)
{
    JsonObject jsonObject;
    obj.ToJson(jsonObject);
    std::string result = jsonObject.EncodeJsonType();

    return result;
}

JsonObject JsonLibrary::ToJsonObject(const JsonSerialized& obj)
{
    JsonObject jsonObject;
    obj.ToJson(jsonObject);
    return jsonObject;
}

void JsonLibrary::SaveAsJson(const std::string& path, const JsonSerialized& obj)
{
    const std::string jsonString = ToJson(obj);
    FileUtils::WriteFile(path, jsonString);
}

void JsonLibrary::SaveAsJson(const std::string& path, const JsonObject& obj)
{
    const std::string jsonString = obj.EncodeJsonType();
    FileUtils::WriteFile(path, jsonString);
}