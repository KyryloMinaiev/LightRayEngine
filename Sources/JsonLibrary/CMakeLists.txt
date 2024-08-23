add_library(json-library JsonLibrary.cpp
        Utils/FileUtils.cpp
        Utils/JsonDecoder.cpp
        Utils/JsonLiteralsUtils.cpp
        JsonTypes/BaseJsonType.cpp
        JsonTypes/JsonArray.cpp
        JsonTypes/JsonBool.cpp
        JsonTypes/JsonFloat.cpp
        JsonTypes/JsonObject.cpp
        JsonTypes/JsonObjectData.cpp
        JsonTypes/JsonString.cpp
        JsonTypes/JsonTypes.cpp)

target_include_directories(json-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})