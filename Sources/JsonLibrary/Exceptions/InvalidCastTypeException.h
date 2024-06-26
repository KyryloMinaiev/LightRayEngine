#pragma once

#include <exception>

class InvalidCastTypeException : public std::exception
{
public:
    InvalidCastTypeException() : exception("Invalid cast type!") {}
};
