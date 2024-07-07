//
// Created by MrFlyingChip on 25.06.2024.
//

#include "EditorConfigurationSettings.h"

namespace LightRayEngine {

    EditorConfigurationSettings::EditorConfigurationSettings(const EditorConfigurationSettings &other) = default;
    EditorConfigurationSettings::EditorConfigurationSettings() = default;
    EditorConfigurationSettings::EditorConfigurationSettings(const JsonLibrary::JsonObject &other) : JsonObject(other) {
    }
}