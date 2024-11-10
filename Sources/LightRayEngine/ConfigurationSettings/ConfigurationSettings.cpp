//
// Created by MrFlyingChip on 25.06.2024.
//

#include "ConfigurationSettings.h"

namespace LightRayEngine {

    ConfigurationSettings::ConfigurationSettings(const ConfigurationSettings &other) = default;
    ConfigurationSettings::ConfigurationSettings() = default;
    ConfigurationSettings::ConfigurationSettings(const JsonLibrary::JsonObject &other) : JsonObject(other) {
    }

    JsonLibrary::BaseJsonType
    ConfigurationSettings::GetValue(const std::string &fieldName, const JsonLibrary::BaseJsonType &defaultValue) {
        if(Contains(fieldName)){
            return GetField(fieldName);
        }

        SetField(fieldName, defaultValue);
        return defaultValue;
    }
}