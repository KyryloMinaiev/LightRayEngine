//
// Created by MrFlyingChip on 08.06.2025.
//

#ifndef LIGHTRAYAPPLICATION_OPENPROJECTSEQUENCE_H
#define LIGHTRAYAPPLICATION_OPENPROJECTSEQUENCE_H

#include "Generic/Delegates/Action.h"
#include <string>

namespace LightRayEngine
{
    class ProjectManager;
    class ProjectWizardWindow;

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
            void OpenProjectWizardWindow();
            void OpenProjectCreatingWindow();

            ProjectManager *m_projectManager;
            ProjectWizardWindow* m_projectWizardWindow;
            OpenProjectCallback m_openProjectCallback;
    };
}

#endif //LIGHTRAYAPPLICATION_OPENPROJECTSEQUENCE_H
