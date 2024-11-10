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
#include "../SerializedTime.h"

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
        void ToJson(JsonLibrary::JsonObject &jsonObject) const override;
    };

    class ProjectManager {

    public:
        static void Init(EditorConfigurationSettings *settings, ProjectOpenCallback projectOpenCallback);
        static std::vector<ProjectData> GetSavedProjects();
        static bool TryAddProjectByPath(const std::string& path);
        static bool ValidatePathForProjectCreating(const std::string& path);
        static bool TryCreateProjectByPath(const std::string& path, const std::string& projectName);
        static bool TryOpenProjectByPath(const std::string& path);
        static void RemoveProjectFromList(const std::string& path);
        static ProjectData GetCurrentOpenProject();

    private:
        static bool TryAddProjectToList(const std::string& path, const std::string& projectName);
        static bool IsProjectAdded(const std::string& path);
        static bool TryGetProjectDataFromList(const std::string& path, ProjectData& projectData);
        static void ReadSavedProjectsPathList();
        static std::string CombinePath(const std::string& path1, const std::string& path2);

        static EditorConfigurationSettings *m_settings;
        static std::vector<ProjectData> m_savedProjectsPathList;
        static ProjectData m_currentProject;
        static ProjectOpenCallback m_projectOpenCallback;

        static constexpr auto k_assetsFolderName = "Assets";
        static constexpr auto k_projectSettingsFolderName = "ProjectSettings";
        static constexpr auto k_projectSettingsFileName = "ProjectSettings.json";
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_PROJECTMANAGER_H
