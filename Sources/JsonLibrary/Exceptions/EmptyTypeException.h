#pragma once

#include "JsonLibraryException.h"
#include "../JsonTypes/JsonTypes.h"

namespace JsonLibrary {
    class EmptyTypeException : public JsonLibraryException {
    public:
        EmptyTypeException() : JsonLibraryException("Cannot encode empty json type!") {}
    };
}