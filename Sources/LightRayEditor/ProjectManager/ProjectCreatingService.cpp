//
// Created by MrFlyingChip on 09.06.2025.
//

#include <filesystem>
#include "ProjectCreatingService.h"
#include "ProjectManager/ProjectManager.h"
#include "ProjectSettings.h"
#include "FileUtils.h"
#include "Const/Constants.h"

namespace LightRayEngine
{
    ProjectCreatingService::ProjectCreatingService(ProjectManager *projectManager) : m_projectManager(projectManager)
    {

    }

    bool ProjectCreatingService::TryCreateProjectByPath(const std::string &path, const std::string &projectName)
    {
        if (!ValidatePathForProjectCreating(path))
        {
            return false;
        }

        if (m_projectManager->ProjectExists(path))
        {
            return false;
        }

        if (!FileUtils::TryCreateFolder(path, AssetsFolderName))
        {
            return false;
        }

        if (!FileUtils::TryCreateFolder(path, ProjectSettingsFolderName))
        {
            return false;
        }

        std::string projectSettingsFilePath = CombinePath(CombinePath(path, ProjectSettingsFolderName),
                                                          ProjectSettingsFileName);
        ProjectSettings settings;
        settings.projectName = projectName;
        std::string json = JsonLibrary::JsonLibrary::ToJson(settings);
        if (!FileUtils::TrySaveFile(projectSettingsFilePath, json))
        {
            return false;
        }

        return true;
    }

    bool ProjectCreatingService::ValidatePathForProjectCreating(const std::string &path)
    {
        return std::filesystem::exists(path) && std::filesystem::is_empty(path);
    }

    std::string ProjectCreatingService::CombinePath(const std::string &path1, const std::string &path2)
    {
        return path1 + "/" + path2;
    }
} // LightRayEngine