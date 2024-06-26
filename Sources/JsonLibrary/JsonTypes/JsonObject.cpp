#include "JsonObject.h"

#include <sstream>
#include "./../Utils/JsonLiteralsUtils.h"
#include "BaseJsonType.h"

std::string JsonObject::EncodeJsonType() const
{
	std::stringstream buffer;
	buffer << JsonLiteralsUtils::GetLiteral(JsonLiterals::ObjectStart);
	buffer << JsonLiteralsUtils::GetLiteral(JsonLiterals::NewLine);

	const std::map<std::string, std::shared_ptr<BaseJsonType>> data = _data.GetData();
	const int size = data.size();
	int index = 0;
	for (auto it = data.cbegin(); it != data.cend(); ++it, ++index)
	{
		JsonString fieldName(it->first);
		buffer << fieldName.EncodeJsonType();
		buffer << JsonLiteralsUtils::GetLiteral(JsonLiterals::FieldStart);
		const IJsonType* jsonType = it->second.get();
		buffer << jsonType->EncodeJsonType();
		if(index != size - 1)
		{
			buffer << JsonLiteralsUtils::GetLiteral(JsonLiterals::Comma);
		}
		buffer << JsonLiteralsUtils::GetLiteral(JsonLiterals::NewLine);
	}
	
	buffer << JsonLiteralsUtils::GetLiteral(JsonLiterals::ObjectEnd);
	return buffer.str();
}

bool JsonObject::TryDecodeJsonType(const std::string& json, int startIndex, int& endIndex)
{
	if (!JsonLiteralsUtils::IsJsonLiteral(json[startIndex], JsonLiterals::ObjectStart))
	{
		return false;
	}

	bool hasField = false;
	bool fieldEnded = false;
	JsonString fieldName;
	int index = 0;

	for (int i = startIndex + 1; i < json.length(); ++i)
	{
		const char currentChar = json[i];
		endIndex = i;

		//1. Don't take into account any spaces
		if (JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::Space))
		{
			continue;
		}

		//2. After spaces, there should be either field name or object end
		if (!hasField && fieldName.TryDecodeJsonType(json, i, index))
		{
			hasField = true;
			i = index;
			continue;
		}

		if (!hasField && JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::ObjectEnd))
		{
			return true;
		}

		//3. If there's no field name, it means that something is wrong in the json file
		if (!hasField)
		{
			return false;
		}

		//4. Skipping all the spaces and searching for the :
		if (JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::FieldStart))
		{
			continue;
		}

		if (!fieldEnded && TryDecodeJsonTypes(json, i, index, fieldName))
		{
			fieldEnded = true;
			i = index;
			continue;
		}

		if (!fieldEnded)
		{
			return false;
		}

		//5. Wait for a comma or a bracket as a sign that the field ended
		if (JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::Comma))
		{
			fieldEnded = false;
			hasField = false;
			continue;
		}

		if (JsonLiteralsUtils::IsJsonLiteral(currentChar, JsonLiterals::ObjectEnd))
		{
			return true;
		}
	}

	return false;
}

bool JsonObject::Contains(const std::string& fieldName) const
{
	return _data.ContainsField(fieldName);
}

BaseJsonType& JsonObject::GetField(const std::string& fieldName) const
{
	BaseJsonType& result = _data.GetBaseJsonTypeField(fieldName);
	return result;
}

BaseJsonType& JsonObject::operator[](const std::string& fieldName)
{
	if(!_data.ContainsField(fieldName))
	{
		_data.SetField(fieldName, BaseJsonType());
	}
	
	return GetField(fieldName);
}

bool JsonObject::TryDecodeJsonTypes(const std::string& json, int startIndex, int& endIndex, const JsonString& fieldName)
{
	BaseJsonType base_json;
	if(base_json.TryDecodeJsonType(json, startIndex, endIndex))
	{
		_data.SetField(fieldName, base_json);
		return true;
	}

	return false;
}

JsonObject::JsonObject() = default;
