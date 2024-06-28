#pragma once

#include <iostream>
#include <string>

#include "JsonSerialized.h"
#include "JsonTypes/JsonObject.h"
#include "JsonTypes/BaseJsonType.h"

class JsonObject;

namespace JsonLibrary {
    class JsonLibrary {
    public:
        static bool FromJsonString(std::string &json, JsonSerialized &obj);

        static void FromJsonObject(JsonObject &jsonObject, JsonSerialized &obj);

        static void DecodeJsonObjectField(JsonObject &parentObject, const std::string &fieldName, JsonSerialized &obj);

        static bool FromJsonFile(const std::string &path, JsonSerialized &obj);

        static JsonObject LoadJsonFile(const std::string &path);

        static std::string ToJson(const JsonSerialized &obj);

        static JsonObject ToJsonObject(const JsonSerialized &obj);

        static void SaveAsJson(const std::string &path, const JsonSerialized &obj);

        static void SaveAsJson(const std::string &path, const JsonObject &obj);
    };
}