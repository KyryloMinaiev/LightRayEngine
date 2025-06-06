#pragma once

namespace JsonLibrary{
    class JsonObject;

    class JsonSerialized
    {
    public:
        virtual ~JsonSerialized() = default;
        virtual void FromJson(JsonObject& jsonObject) = 0;
        virtual void ToJson(JsonObject& jsonObject) = 0;
    };
}