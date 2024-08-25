//
// Created by MrFlyingChip on 19.08.2024.
//

#include "ProjectCreationUtils.h"
#include "../EditorConfigurationSettings/EditorConfigurationSettingsUtils.h"
#include "FileUtils.h"
#include "../ProjectSettings.h"
#include <filesystem>

namespace LightRayEngine {
    EditorConfigurationSettings *ProjectCreationUtils::m_settings;
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
        std::string assetsFolderPath = CombinePath(path, k_assetsFolderName);
        std::string projectSettingsFolderPath = CombinePath(path, k_projectSettingsFolderName);
        std::string projectSettingsFilePath = CombinePath(projectSettingsFolderPath, k_projectSettingsFileName);

        if (!std::filesystem::exists(assetsFolderPath)) {
            return false;
        }

        if (!std::filesystem::exists(projectSettingsFolderPath)) {
            return false;
        }

        if (!std::filesystem::exists(projectSettingsFilePath)) {
            return false;
        }

        std::string projectSettingsStr;
        if (!FileUtils::TryLoadFile(projectSettingsFilePath, projectSettingsStr)) {
            return false;
        }

        ProjectSettings projectSettings;
        if (!JsonLibrary::JsonLibrary::FromJsonString(projectSettingsStr, projectSettings)) {
            return false;
        }

        std::string projectName = projectSettings.projectName;
        if (!TryAddProjectToList(path, projectName)) {
            return false;
        }

        return true;
    }

    bool ProjectCreationUtils::TryCreateProjectByPath(const std::string &path, const std::string &projectName) {
        if (!ValidatePathForProjectCreating(path)) {
            return false;
        }

        if (!TryAddProjectToList(path, projectName)) {
            return false;
        }

        if (!FileUtils::TryCreateFolder(path, k_assetsFolderName)) {
            return false;
        }

        if (!FileUtils::TryCreateFolder(path, k_projectSettingsFolderName)) {
            return false;
        }

        std::string projectSettingsFilePath = CombinePath(CombinePath(path, k_projectSettingsFolderName),
                                                          k_projectSettingsFileName);
        ProjectSettings settings;
        settings.projectName = projectName;
        std::string json = JsonLibrary::JsonLibrary::ToJson(settings);
        if (!FileUtils::TrySaveFile(projectSettingsFilePath, json)) {
            return false;
        }

        return true;
    }

    std::string ProjectCreationUtils::CombinePath(const std::string &path1, const std::string &path2) {
        return path1 + "/" + path2;
    }

    bool ProjectCreationUtils::TryAddProjectToList(const std::string &path, const std::string &projectName) {
        if (IsProjectAdded(path)) {
            return false;
        }

        std::time_t now = std::time(nullptr);
        ProjectData data;
        data.path = path;
        data.name = projectName;
        data.changeTime = SerializedTime(*std::localtime(&now));
        m_savedProjectsPathList.push_back(data);
        m_settings->GetField("savedProjects").EncodeArray(m_savedProjectsPathList);

        return true;
    }

    bool ProjectCreationUtils::IsProjectAdded(const std::string &path) {
        for (const auto &projectData: m_savedProjectsPathList) {
            if (projectData.path == path) {
                return true;
            }
        }

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