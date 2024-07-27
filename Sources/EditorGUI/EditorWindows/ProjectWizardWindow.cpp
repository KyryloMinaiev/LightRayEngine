//
// Created by MrFlyingChip on 27.07.2024.
//

#include "ProjectWizardWindow.h"
#include <ImGUI.h>
#include "../EditorWindowManager.h"

namespace LightRayEngine {

    void ProjectWizardWindow::OnCreate() {

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
}