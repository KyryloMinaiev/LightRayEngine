//
// Created by MrFlyingChip on 19.08.2024.
//

#include "ProjectManager.h"
#include "ProjectSettings.h"
#include "EditorConfigurationSettings/EditorConfigurationSettingsUtils.h"
#include "FileUtils.h"
#include <filesystem>
#include <algorithm>
#include "Const/Constants.h"

namespace LightRayEngine
{
    ProjectManager::ProjectManager()
    {
        m_settings = EditorConfigurationSettingsUtils::GetSettings();
        ReadSavedProjectsPathList();
    }

    std::vector<ProjectData> ProjectManager::GetSavedProjects()
    {
        return m_savedProjectsPathList;
    }

    void ProjectManager::ReadSavedProjectsPathList()
    {
        auto array = m_settings->GetValue("savedProjects", std::vector<JsonLibrary::JsonObject>());
        array.DecodeArray(m_savedProjectsPathList);
    }

    bool ProjectManager::TryAddProjectByPath(const std::string &path)
    {
        std::string assetsFolderPath = CombinePath(path, AssetsFolderName);
        std::string projectSettingsFolderPath = CombinePath(path, ProjectSettingsFolderName);
        std::string projectSettingsFilePath = CombinePath(projectSettingsFolderPath, ProjectSettingsFileName);

        if (!std::filesystem::exists(assetsFolderPath))
        {
            return false;
        }

        if (!std::filesystem::exists(projectSettingsFolderPath))
        {
            return false;
        }

        if (!std::filesystem::exists(projectSettingsFilePath))
        {
            return false;
        }

        std::string projectSettingsStr;
        if (!FileUtils::TryLoadFile(projectSettingsFilePath, projectSettingsStr))
        {
            return false;
        }

        ProjectSettings projectSettings;
        if (!JsonLibrary::JsonLibrary::FromJsonString(projectSettingsStr, projectSettings))
        {
            return false;
        }

        std::string projectName = projectSettings.projectName;
        if (!TryAddProjectToList(path, projectName))
        {
            return false;
        }

        return true;
    }

    std::string ProjectManager::CombinePath(const std::string &path1, const std::string &path2)
    {
        return path1 + "/" + path2;
    }

    bool ProjectManager::TryAddProjectToList(const std::string &path, const std::string &projectName)
    {
        if (ProjectExists(path))
        {
            return false;
        }

        ProjectData data(projectName, path, SerializedTime::Now());
        m_savedProjectsPathList.push_back(data);
        m_settings->GetField("savedProjects").EncodeArray(m_savedProjectsPathList);

        return true;
    }

    bool ProjectManager::ProjectExists(const std::string &path)
    {
        ProjectData data;
        return TryGetProjectDataFromList(path, data);
    }

    bool ProjectManager::TryOpenProjectByPath(const std::string &path)
    {
        ProjectData projectData;
        if (!TryGetProjectDataFromList(path, projectData))
        {
            return false;
        }

        std::string assetsFolderPath = CombinePath(path, AssetsFolderName);
        std::string projectSettingsFolderPath = CombinePath(path, ProjectSettingsFolderName);
        std::string projectSettingsFilePath = CombinePath(projectSettingsFolderPath, ProjectSettingsFileName);

        if (!std::filesystem::exists(assetsFolderPath))
        {
            return false;
        }

        if (!std::filesystem::exists(projectSettingsFolderPath))
        {
            return false;
        }

        if (!std::filesystem::exists(projectSettingsFilePath))
        {
            return false;
        }

        std::string projectSettingsStr;
        if (!FileUtils::TryLoadFile(projectSettingsFilePath, projectSettingsStr))
        {
            return false;
        }

        m_currentProject = projectData;
        m_settings->SetField("lastProject", m_currentProject.path);

        return true;
    }

    ProjectData ProjectManager::GetCurrentOpenProject()
    {
        return m_currentProject;
    }

    void ProjectManager::RemoveProjectFromList(const std::string &path)
    {
        m_savedProjectsPathList.erase(std::remove_if(m_savedProjectsPathList.begin(), m_savedProjectsPathList.end(),
                                                     [&path](const ProjectData &data)
                                                     { return data.path == path; }),
                                      m_savedProjectsPathList.end());
        m_settings->GetField("savedProjects").EncodeArray(m_savedProjectsPathList);
    }

    bool ProjectManager::TryGetProjectDataFromList(const std::string &path, ProjectData &projectData) const
    {
        for (const auto &pd: m_savedProjectsPathList)
        {
            if (pd.path == path)
            {
                projectData = pd;
                return true;
            }
        }

        return false;
    }

    bool ProjectManager::TryGetLastOpenedProject(ProjectData &projectData) const
    {
        std::string lastProjectPath = m_settings->GetField("lastProject");
        return TryGetProjectDataFromList(lastProjectPath, projectData);;
    }
} // LightRayEngine