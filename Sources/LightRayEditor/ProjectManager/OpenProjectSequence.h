//
// Created by MrFlyingChip on 08.06.2025.
//

#ifndef LIGHTRAYAPPLICATION_OPENPROJECTSEQUENCE_H
#define LIGHTRAYAPPLICATION_OPENPROJECTSEQUENCE_H

#include "Generic/Delegates/Action.h"
#include "ProjectCreatingService.h"
#include <string>

namespace LightRayEngine
{
    class ProjectManager;
    class ProjectWizardWindow;
    class ProjectCreatingWindow;

    using OpenProjectCallback = Action<bool, const std::string&>;

    class OpenProjectSequence
    {
        public:
            OpenProjectSequence(ProjectManager *projectManager);
            void StartSequence(const OpenProjectCallback& openProjectCallback);

        private:
            void OnAddProjectButtonPressed();
            void OnOpenProjectButtonPressed(const std::string& path);
            void OnRemovedProjectButtonPressed(const std::string& path);
            void OnCreateProjectButtonPressed(const std::string& path, const std::string& name);
            void OpenProjectWizardWindow();
            void OpenProjectCreatingWindow();

            void ReloadProjectWizardWindow();

            ProjectManager *m_projectManager;
            ProjectCreatingService m_projectCreatingService;

            ProjectWizardWindow* m_projectWizardWindow;
            ProjectCreatingWindow* m_projectCreatingWindow;
            OpenProjectCallback m_openProjectCallback;
    };
}

#endif //LIGHTRAYAPPLICATION_OPENPROJECTSEQUENCE_H
