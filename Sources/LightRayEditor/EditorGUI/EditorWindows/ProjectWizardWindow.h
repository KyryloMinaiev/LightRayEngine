//
// Created by MrFlyingChip on 27.07.2024.
//

#ifndef LIGHTRAYENGINE_PROJECTWIZARDWINDOW_H
#define LIGHTRAYENGINE_PROJECTWIZARDWINDOW_H

#include "../EditorWindow.h"
#include "ProjectManager/ProjectData.h"
#include "Generic/Delegates/Action.h"
#include <vector>

namespace LightRayEngine
{
    class ProjectWizardWindow : public EditorWindow
    {
        public:
            struct ProjectWizardWindowData
            {
                Action<> OnProjectAddButtonClick;
                Action<const std::string&> OnOpenProjectButtonClick;
                Action<const std::string&> OnRemoveProjectButtonClick;
                Action<> OnCreateProjectButtonClick;
            };

            explicit ProjectWizardWindow(EditorWindowManager *editorWindowManager);
            void OnCreate() override;
            void OnGui() override;
            void UpdateProjectList(const std::vector<ProjectData>& projectList);
            static ProjectWizardWindow* Create(const ProjectWizardWindowData& windowData);
        private:
            void UpdateProjectsLastChangeTime();
            const char *GetChangeTimeString(const SerializedTime &changeTime);

            void DrawWindowHeader() const;
            void DrawWindowFooter();
            void DrawProjectsTable();

            SerializedTime m_currentTime;
            std::vector<ProjectData> m_lastProjectsPathList;
            ProjectWizardWindowData m_windowData;
    };
}


#endif //LIGHTRAYENGINE_PROJECTWIZARDWINDOW_H
