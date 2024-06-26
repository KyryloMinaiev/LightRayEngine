#pragma once

#include <string>

class IJsonType
{
public:
	virtual ~IJsonType() = default;
	virtual bool TryDecodeJsonType(const std::string& json, int startIndex, int& endIndex) = 0;
	virtual std::string EncodeJsonType() const = 0;
};
