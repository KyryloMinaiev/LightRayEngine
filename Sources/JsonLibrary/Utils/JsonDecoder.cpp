#include "JsonDecoder.h"

bool JsonDecoder::TryDecodeJson(const std::string& json, JsonObject& result)
{
    int endIndex;
    return result.TryDecodeJsonType(json, 0, endIndex);
}
