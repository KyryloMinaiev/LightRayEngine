#pragma once

#include "JsonLibraryException.h"
#include "../JsonTypes/JsonTypes.h"

namespace JsonLibrary {
    class InvalidCastTypeException : public JsonLibraryException {
    public:
        InvalidCastTypeException(JsonType to, JsonType from) : JsonLibraryException(
                std::string("Invalid cast type! From: " + toString(from) + ", to: " + toString(to))) {
        }
    };
}
