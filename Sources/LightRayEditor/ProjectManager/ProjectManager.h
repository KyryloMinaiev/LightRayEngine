//
// Created by MrFlyingChip on 19.08.2024.
//

#ifndef LIGHTRAYENGINE_PROJECTMANAGER_H
#define LIGHTRAYENGINE_PROJECTMANAGER_H

#include "ProjectData.h"

namespace LightRayEngine
{
    class EditorConfigurationSettings;
    class ProjectManager
    {
        public:
            explicit ProjectManager();

            std::vector<ProjectData> GetSavedProjects();
            bool TryAddProjectByPath(const std::string &path);
            bool ProjectExists(const std::string& path);
            bool TryOpenProjectByPath(const std::string &path);
            void RemoveProjectFromList(const std::string &path);
            ProjectData GetCurrentOpenProject();
            bool TryGetLastOpenedProject(ProjectData &projectData) const;
        private:
            bool TryAddProjectToList(const std::string &path, const std::string &projectName);
            bool TryGetProjectDataFromList(const std::string &path, ProjectData &projectData) const;
            void ReadSavedProjectsPathList();
            std::string CombinePath(const std::string &path1, const std::string &path2);

            EditorConfigurationSettings *m_settings;
            std::vector<ProjectData> m_savedProjectsPathList;
            ProjectData m_currentProject;
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_PROJECTMANAGER_H
