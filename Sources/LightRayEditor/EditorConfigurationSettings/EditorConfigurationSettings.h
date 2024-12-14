//
// Created by MrFlyingChip on 25.06.2024.
//

#ifndef LIGHTRAYENGINE_CONFIGURATIONSETTINGS_H
#define LIGHTRAYENGINE_CONFIGURATIONSETTINGS_H

#include "JsonLibrary.h"

namespace LightRayEngine {
    class EditorConfigurationSettings : public JsonLibrary::JsonObject{
    public:
        EditorConfigurationSettings(const EditorConfigurationSettings &other);
        EditorConfigurationSettings(const JsonLibrary::JsonObject &other);

        EditorConfigurationSettings();

        JsonLibrary::BaseJsonType GetValue(const std::string& fieldName, const JsonLibrary::BaseJsonType& defaultValue);
    };
}


#endif //LIGHTRAYENGINE_CONFIGURATIONSETTINGS_H
