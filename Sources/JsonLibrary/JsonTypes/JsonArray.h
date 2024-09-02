#pragma once

#include <vector>

#include "IJsonType.h"
#include "JsonTypes.h"
#include "./../Exceptions/InvalidCastTypeException.h"

namespace JsonLibrary {
    class JsonSerialized;
    class JsonObject;
    class BaseJsonType;

    class JsonArray : public IJsonType {
    public:
        ~JsonArray();

        JsonArray();
        JsonArray(const std::vector<int> &array);
        JsonArray(const std::vector<float> &array);
        JsonArray(const std::vector<bool> &array);
        JsonArray(const std::vector<std::string> &array);
        JsonArray(const std::vector<JsonObject> &array);
        JsonArray(const JsonArray &other);

        operator std::vector<int>();
        operator std::vector<float>();
        operator std::vector<std::string>();
        operator std::vector<bool>();
        operator std::vector<JsonObject>();

        BaseJsonType &operator[](const int &index);

        bool TryDecodeJsonType(const std::string &json, int startIndex, int &endIndex) override;

        std::string EncodeJsonType() const override;

    private:
        template<typename T>
        std::vector<T> GetJsonType(JsonType jsonType);

        JsonType _vectorType = JsonType::None;
        std::vector<BaseJsonType> _array;
    };
}
