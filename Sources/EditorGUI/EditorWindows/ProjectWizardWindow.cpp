//
// Created by MrFlyingChip on 27.07.2024.
//

#include "ProjectWizardWindow.h"
#include <ImGUI.h>
#include "../EditorWindowManager.h"
#include "../../Core/EditorConfigurationSettings/EditorConfigurationSettingsUtils.h"

namespace LightRayEngine {

    void ProjectWizardWindow::OnCreate() {
        LoadLastProjects();
    }

    void ProjectWizardWindow::OnGui() {

    }

    void ProjectWizardWindow::Create() {
        auto window = EditorWindowManager::CreateEditorWindow<ProjectWizardWindow>("Project Wizard");
        window->width = 600;
        window->height = 400;
        window->resizable = false;
        window->canBeDocked = false;
        ImGui::SetNextWindowFocus();
    }

    void ProjectWizardWindow::LoadLastProjects() {
        EditorConfigurationSettings *settings = EditorConfigurationSettingsUtils::GetSettings();
        if (!settings) {
            return;
        }

        m_lastProjectsPathList = settings->GetValue("lastProjects", std::vector<std::string>());
        for (auto projectPath : m_lastProjectsPathList) {

        }
    }
}