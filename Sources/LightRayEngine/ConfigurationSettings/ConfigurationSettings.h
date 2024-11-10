//
// Created by MrFlyingChip on 25.06.2024.
//

#ifndef LIGHTRAYENGINE_CONFIGURATIONSETTINGS_H
#define LIGHTRAYENGINE_CONFIGURATIONSETTINGS_H

#include "JsonLibrary.h"

namespace LightRayEngine {
    class ConfigurationSettings : public JsonLibrary::JsonObject{
    public:
        ConfigurationSettings(const ConfigurationSettings &other);
        ConfigurationSettings(const JsonLibrary::JsonObject &other);

        ConfigurationSettings();

        JsonLibrary::BaseJsonType GetValue(const std::string& fieldName, const JsonLibrary::BaseJsonType& defaultValue);
    };
}


#endif //LIGHTRAYENGINE_CONFIGURATIONSETTINGS_H
