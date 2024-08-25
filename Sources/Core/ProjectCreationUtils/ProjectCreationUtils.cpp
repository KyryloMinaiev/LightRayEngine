//
// Created by MrFlyingChip on 19.08.2024.
//

#include "ProjectCreationUtils.h"
#include "../EditorConfigurationSettings/EditorConfigurationSettingsUtils.h"
#include <filesystem>

namespace LightRayEngine {
    EditorConfigurationSettings* ProjectCreationUtils::m_settings;
    std::vector<ProjectData> ProjectCreationUtils::m_savedProjectsPathList;

    std::vector<ProjectData> ProjectCreationUtils::GetSavedProjects() {
        return m_savedProjectsPathList;
    }

    void ProjectCreationUtils::Init(EditorConfigurationSettings *settings) {
        m_settings = settings;
        ReadSavedProjectsPathList();
    }

    void ProjectCreationUtils::ReadSavedProjectsPathList() {
        auto array = m_settings->GetValue("savedProjects", std::vector<JsonLibrary::JsonObject>());
        array.DecodeArray(m_savedProjectsPathList);
    }

    bool ProjectCreationUtils::ValidatePathForProjectCreating(const std::string &path) {
        return std::filesystem::exists(path) && std::filesystem::is_empty(path);
    }

    bool ProjectCreationUtils::TryAddProjectByPath(const std::string &path) {
        return false;
    }

    void ProjectData::FromJson(JsonLibrary::JsonObject &jsonObject) {
        name = static_cast<std::string>(jsonObject["name"]);
        path = static_cast<std::string>(jsonObject["path"]);
        isFavourite = jsonObject["isFavourite"];
        JsonLibrary::JsonLibrary::DecodeJsonObjectField(jsonObject, "changeTime", changeTime);
    }

    void ProjectData::ToJson(JsonLibrary::JsonObject &jsonObject) const {
        jsonObject["name"] = name;
        jsonObject["path"] = path;
        jsonObject["isFavourite"] = isFavourite;
        jsonObject["changeTime"] = JsonLibrary::JsonLibrary::ToJsonObject(changeTime);
    }
} // LightRayEngine