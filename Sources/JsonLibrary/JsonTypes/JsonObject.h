#pragma once

#include <string>
#include "IJsonType.h"
#include "JsonObjectData.h"

namespace JsonLibrary {
    class JsonSerialized;
    class JsonString;

    class JsonObject : public IJsonType {
    public:
        JsonObject(const JsonObject &other) : _data(other._data) {}

        JsonObject();

        std::string EncodeJsonType() const override;

        bool TryDecodeJsonType(const std::string &json, int startIndex, int &endIndex) override;

        bool Contains(const std::string &fieldName) const;

        BaseJsonType &GetField(const std::string &fieldName) const;

        BaseJsonType &operator[](const std::string &fieldName);

    private:
        bool TryDecodeJsonTypes(const std::string &json, int startIndex, int &endIndex, const JsonString &fieldName);

        JsonObjectData _data;
    };
}