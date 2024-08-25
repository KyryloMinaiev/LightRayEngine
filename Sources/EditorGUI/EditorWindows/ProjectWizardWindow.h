//
// Created by MrFlyingChip on 27.07.2024.
//

#ifndef LIGHTRAYENGINE_PROJECTWIZARDWINDOW_H
#define LIGHTRAYENGINE_PROJECTWIZARDWINDOW_H

#include "../EditorWindow.h"
#include "../../Core/ProjectCreationUtils/ProjectCreationUtils.h"
#include <vector>
#include <functional>

namespace LightRayEngine {
    class ProjectWizardWindow : public EditorWindow {
    public:
        void OnCreate() override;
        void OnGui() override;
        static void Create();
    private:
        void OnProjectCreated(const std::string& projectName, const std::string& projectPath);
        void LoadLastProjects();

        std::vector<ProjectData> m_lastProjectsPathList;
    };
}


#endif //LIGHTRAYENGINE_PROJECTWIZARDWINDOW_H
