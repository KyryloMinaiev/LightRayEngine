#pragma once

#include <vector>

#include "IJsonType.h"
#include "JsonTypes.h"
#include "./../Exceptions/InvalidCastTypeException.h"

class JsonSerialized;
class JsonObject;
class BaseJsonType;

namespace JsonLibrary {
    class JsonArray : public IJsonType {
    public:
        JsonArray();

        JsonArray(const std::vector<int> &array);

        JsonArray(const std::vector<float> &array);

        JsonArray(const std::vector<bool> &array);

        JsonArray(const std::vector<std::string> &array);

        JsonArray(const std::vector<JsonObject> &array);

        JsonArray(const JsonArray &other);

        operator std::vector<int>() const;

        operator std::vector<float>() const;

        operator std::vector<std::string>() const;

        operator std::vector<bool>() const;

        operator std::vector<JsonObject>() const;

        BaseJsonType &operator[](const int &index);

        bool TryDecodeJsonType(const std::string &json, int startIndex, int &endIndex) override;

        std::string EncodeJsonType() const override;

    private:
        JsonType _vectorType = JsonType::None;
        std::vector<BaseJsonType> _array;
    };
}
