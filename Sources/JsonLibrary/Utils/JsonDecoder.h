#pragma once

#include <string>
#include <iostream>
#include "./../JsonTypes/JsonObject.h"

namespace JsonLibrary {
    class JsonDecoder {
    public:
        static bool TryDecodeJson(const std::string &json, JsonObject &result);
    };
}
