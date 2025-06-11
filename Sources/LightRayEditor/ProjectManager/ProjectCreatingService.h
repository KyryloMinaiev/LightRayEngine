//
// Created by MrFlyingChip on 09.06.2025.
//

#ifndef LIGHTRAYAPPLICATION_PROJECTCREATINGSERVICE_H
#define LIGHTRAYAPPLICATION_PROJECTCREATINGSERVICE_H

#include <string>

namespace LightRayEngine
{
    class ProjectManager;

    class ProjectCreatingService
    {
        public:
            explicit ProjectCreatingService(ProjectManager* projectManager);
            bool TryCreateProjectByPath(const std::string &path, const std::string &projectName);
        private:
            bool ValidatePathForProjectCreating(const std::string &path);

            ProjectManager* m_projectManager;
            std::string CombinePath(const std::string &path1, const std::string &path2);
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_PROJECTCREATINGSERVICE_H
