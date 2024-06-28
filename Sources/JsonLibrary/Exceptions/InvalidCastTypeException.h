#pragma once

#include <exception>

namespace JsonLibrary {
    class InvalidCastTypeException : public std::exception {
    public:
        InvalidCastTypeException() : exception("Invalid cast type!") {}
    };
}
