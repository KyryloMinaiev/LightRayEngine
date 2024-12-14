//
// Created by MrFlyingChip on 25.06.2024.
//

#include "EditorConfigurationSettings.h"

namespace LightRayEngine {

    EditorConfigurationSettings::EditorConfigurationSettings(const EditorConfigurationSettings &other) = default;
    EditorConfigurationSettings::EditorConfigurationSettings() = default;
    EditorConfigurationSettings::EditorConfigurationSettings(const JsonLibrary::JsonObject &other) : JsonObject(other) {
    }

    JsonLibrary::BaseJsonType
    EditorConfigurationSettings::GetValue(const std::string &fieldName, const JsonLibrary::BaseJsonType &defaultValue) {
        if(Contains(fieldName)){
            return GetField(fieldName);
        }

        SetField(fieldName, defaultValue);
        return defaultValue;
    }
}