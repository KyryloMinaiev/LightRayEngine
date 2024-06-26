#include "JsonObject.h"
#include "BaseJsonType.h"

void JsonObjectData::SetField(const std::string& fieldName, const BaseJsonType& value)
{
    _jsonTypeFieldsMap[fieldName] = std::make_shared<BaseJsonType>(value);
}

BaseJsonType& JsonObjectData::GetBaseJsonTypeField(const std::string& fieldName) const
{
    BaseJsonType* result = _jsonTypeFieldsMap.at(fieldName).get();
    return *result;
}

std::map<std::string, std::shared_ptr<BaseJsonType>> JsonObjectData::GetData() const
{
    return _jsonTypeFieldsMap;
}

bool JsonObjectData::ContainsField(const std::string& fieldName) const
{
    const auto it = _jsonTypeFieldsMap.find(fieldName);
    return it != _jsonTypeFieldsMap.end();
}
