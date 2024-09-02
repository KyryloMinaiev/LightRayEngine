#pragma once

#include <string>

namespace JsonLibrary {
    enum class JsonType {
        JsonFloat,
        JsonBool,
        JsonString,
        JsonObject,
        JsonArray,
        None
    };

    std::string toString(JsonType jsonType);
}
