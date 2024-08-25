//
// Created by MrFlyingChip on 19.08.2024.
//

#ifndef LIGHTRAYENGINE_PROJECTCREATIONUTILS_H
#define LIGHTRAYENGINE_PROJECTCREATIONUTILS_H

#include <vector>
#include <string>
#include <ctime>
#include "JsonLibrary.h"
#include "../SerializedTime.h"

namespace LightRayEngine {
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

    class ProjectCreationUtils {

    public:
        static void Init(EditorConfigurationSettings *settings);
        static std::vector<ProjectData> GetSavedProjects();
        static bool TryAddProjectByPath(const std::string& path);
        static bool ValidatePathForProjectCreating(const std::string& path);

    private:
        static void ReadSavedProjectsPathList();

        static EditorConfigurationSettings *m_settings;
        static std::vector<ProjectData> m_savedProjectsPathList;
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_PROJECTCREATIONUTILS_H
