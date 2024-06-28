#pragma once

class JsonObject;

namespace JsonLibrary{
    class JsonSerialized
    {
    public:
        virtual ~JsonSerialized() = default;
        virtual void FromJson(JsonObject& jsonObject) = 0;
        virtual void ToJson(JsonObject& jsonObject) const = 0;
    };
}