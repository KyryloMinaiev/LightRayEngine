//
// Created by MrFlyingChip on 19.08.2024.
//

#include "ProjectManager.h"
#include "ProjectSettings.h"
#include "ConfigurationSettings/ConfigurationSettingsUtils.h"
#include "FileUtils.h"
#include <filesystem>
#include <algorithm>

namespace LightRayEngine {
    ConfigurationSettings *ProjectManager::m_settings;
    std::vector<ProjectData> ProjectManager::m_savedProjectsPathList;
    ProjectData ProjectManager::m_currentProject;
    ProjectOpenCallback ProjectManager::m_projectOpenCallback;

    std::vector<ProjectData> ProjectManager::GetSavedProjects() {
        return m_savedProjectsPathList;
    }

    void ProjectManager::Init(ConfigurationSettings *settings, ProjectOpenCallback projectOpenCallback) {
        m_settings = settings;
        m_projectOpenCallback = projectOpenCallback;
        ReadSavedProjectsPathList();
    }

    void ProjectManager::ReadSavedProjectsPathList() {
        auto array = m_settings->GetValue("savedProjects", std::vector<JsonLibrary::JsonObject>());
        array.DecodeArray(m_savedProjectsPathList);
    }

    bool ProjectManager::ValidatePathForProjectCreating(const std::string &path) {
        return std::filesystem::exists(path) && std::filesystem::is_empty(path);
    }

    bool ProjectManager::TryAddProjectByPath(const std::string &path) {
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

    bool ProjectManager::TryCreateProjectByPath(const std::string &path, const std::string &projectName) {
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

    std::string ProjectManager::CombinePath(const std::string &path1, const std::string &path2) {
        return path1 + "/" + path2;
    }

    bool ProjectManager::TryAddProjectToList(const std::string &path, const std::string &projectName) {
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

    bool ProjectManager::IsProjectAdded(const std::string &path) {
        ProjectData data;
        return TryGetProjectDataFromList(path, data);
    }

    bool ProjectManager::TryOpenProjectByPath(const std::string &path) {
        ProjectData projectData;
        if (!TryGetProjectDataFromList(path, projectData)) {
            return false;
        }

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

        bool result = true;
        if (m_projectOpenCallback) {
            result = m_projectOpenCallback(path);
        }

        if (result) {
            m_currentProject = projectData;
        }

        return result;
    }

    ProjectData ProjectManager::GetCurrentOpenProject() {
        return m_currentProject;
    }

    void ProjectManager::RemoveProjectFromList(const std::string &path) {
        m_savedProjectsPathList.erase(std::remove_if(m_savedProjectsPathList.begin(), m_savedProjectsPathList.end(),
                                                     [&path](const ProjectData &data) { return data.path == path; }),
                                      m_savedProjectsPathList.end());
        m_settings->GetField("savedProjects").EncodeArray(m_savedProjectsPathList);
    }

    bool ProjectManager::TryGetProjectDataFromList(const std::string &path, ProjectData &projectData) {
        for (const auto &pd: m_savedProjectsPathList) {
            if (pd.path == path) {
                projectData = pd;
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