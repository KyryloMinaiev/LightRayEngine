﻿#pragma once
#include <map>
#include <memory>
#include <string>

namespace JsonLibrary {
    class BaseJsonType;
    class JsonObject;

    class JsonObjectData {
    public:
        JsonObjectData() = default;

        JsonObjectData(const JsonObjectData &other) = default;

        ~JsonObjectData() = default;

        void SetField(const std::string &fieldName, const BaseJsonType &value);

        bool ContainsField(const std::string &fieldName) const;

        BaseJsonType &GetBaseJsonTypeField(const std::string &fieldName) const;

        std::map<std::string, std::shared_ptr<BaseJsonType>> GetData() const;

    private:
        std::map<std::string, std::shared_ptr<BaseJsonType>> _jsonTypeFieldsMap;
    };
}
