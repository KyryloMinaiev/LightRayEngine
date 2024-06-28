#pragma once
#include <exception>

namespace JsonLibrary {
    class EmptyTypeException : public std::exception {
    public:
        EmptyTypeException() : exception("Cannot encode empty json type!") {}
    };
}