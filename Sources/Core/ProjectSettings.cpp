//
// Created by MrFlyingChip on 25.08.2024.
//

#include "ProjectSettings.h"

namespace LightRayEngine {
    void ProjectSettings::FromJson(JsonLibrary::JsonObject &jsonObject) {
        projectName = static_cast<std::string>(jsonObject["projectName"]);
        lastOpenedSceneName = static_cast<std::string>(jsonObject["lastOpenedSceneName"]);
    }

    void ProjectSettings::ToJson(JsonLibrary::JsonObject &jsonObject) const {
        jsonObject["projectName"] = projectName;
        jsonObject["lastOpenedSceneName"] = lastOpenedSceneName;
    }
} // LightRayEngine