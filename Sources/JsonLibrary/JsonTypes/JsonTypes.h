#pragma once

#include <string>

namespace JsonLibrary {
    enum class JsonType {
        JsonInt,
        JsonFloat,
        JsonBool,
        JsonString,
        JsonObject,
        JsonArray,
        None
    };

    std::string toString(JsonType jsonType){
        switch (jsonType) {
            case JsonType::JsonInt:
                return "JsonInt";
            case JsonType::JsonFloat:
                return "JsonFloat";
            case JsonType::JsonBool:
                return "JsonBool";
            case JsonType::JsonString:
                return "JsonString";
            case JsonType::JsonObject:
                return "JsonObject";
            case JsonType::JsonArray:
                return "JsonArray";
            case JsonType::None:
                return "None";
        }
    }
}
