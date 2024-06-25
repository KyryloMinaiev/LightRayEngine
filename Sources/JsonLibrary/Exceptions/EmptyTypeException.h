#pragma once
#include <exception>

class EmptyTypeException : public std::exception
{
public:
    EmptyTypeException() : exception("Cannot encode empty json type!") {}
};