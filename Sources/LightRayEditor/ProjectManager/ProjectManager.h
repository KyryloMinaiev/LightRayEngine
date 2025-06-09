//
// Created by MrFlyingChip on 19.08.2024.
//

#ifndef LIGHTRAYENGINE_PROJECTMANAGER_H
#define LIGHTRAYENGINE_PROJECTMANAGER_H

#include <vector>
#include <string>
#include <ctime>
#include "JsonLibrary.h"
#include <functional>
#include "SerializedTime.h"

namespace LightRayEngine {
    #define ProjectOpenCallback std::function<bool(std::string)>

    class EditorConfigurationSettings;

    struct ProjectData : public JsonLibrary::JsonSerialized {
        std::string name;
        std::string path;
        SerializedTime changeTime;
        bool isFavourite;

        ~ProjectData() override = default;
        void FromJson(JsonLibrary::JsonObject &jsonObject) override;
        void ToJson(JsonLibrary::JsonObject &jsonObject) override;
    };

    class ProjectManager {

    public:
        explicit ProjectManager(const ProjectOpenCallback& projectOpenCallback);

        std::vector<ProjectData> GetSavedProjects();
        bool TryAddProjectByPath(const std::string& path);
        bool ValidatePathForProjectCreating(const std::string& path);
        bool TryCreateProjectByPath(const std::string& path, const std::string& projectName);
        bool TryOpenProjectByPath(const std::string& path);
        void RemoveProjectFromList(const std::string& path);
        ProjectData GetCurrentOpenProject();

    private:
        bool TryAddProjectToList(const std::string& path, const std::string& projectName);
        bool IsProjectAdded(const std::string& path);
        bool TryGetProjectDataFromList(const std::string& path, ProjectData& projectData);
        void ReadSavedProjectsPathList();
        std::string CombinePath(const std::string& path1, const std::string& path2);

        EditorConfigurationSettings *m_settings;
        std::vector<ProjectData> m_savedProjectsPathList;
        ProjectData m_currentProject;
        ProjectOpenCallback m_projectOpenCallback;

        static constexpr auto k_assetsFolderName = "Assets";
        static constexpr auto k_projectSettingsFolderName = "ProjectSettings";
        static constexpr auto k_projectSettingsFileName = "ProjectSettings.json";
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_PROJECTMANAGER_H
