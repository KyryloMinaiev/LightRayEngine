//
// Created by MrFlyingChip on 25.08.2024.
//

#ifndef LIGHTRAYENGINE_PROJECTSETTINGS_H
#define LIGHTRAYENGINE_PROJECTSETTINGS_H

#include "JsonLibrary.h"

namespace LightRayEngine {

    class ProjectSettings : public JsonLibrary::JsonSerialized{
    public:
        std::string projectName;
        std::string lastOpenedSceneName;

        ~ProjectSettings() override = default;
        void FromJson(JsonLibrary::JsonObject &jsonObject) override;
        void ToJson(JsonLibrary::JsonObject &jsonObject) const override;
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_PROJECTSETTINGS_H
