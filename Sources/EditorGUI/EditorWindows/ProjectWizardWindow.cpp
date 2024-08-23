//
// Created by MrFlyingChip on 27.07.2024.
//

#include "ProjectWizardWindow.h"
#include <ImGUI.h>
#include "../EditorWindowManager.h"
#include "ProjectCreatingWindow.h"
#include "NativeFileDialog.h"

namespace LightRayEngine {
    void ProjectWizardWindow::OnCreate() {
        LoadLastProjects();
    }

    void ProjectWizardWindow::OnGui() {
        ImGui::ShowDemoWindow();
        ImGui::Text("Projects:");
        ImGui::SameLine();
        if(ImGui::Button("Add", ImVec2(100, 30))){
            std::string selectedProjectPath;
            NativeFileDialog::OpenFolderDialog("", selectedProjectPath);
        }

        ImGui::SameLine();
        if(ImGui::Button("Create", ImVec2(100, 30))){
            auto callback = std::bind(&ProjectWizardWindow::OnProjectCreated, this, std::placeholders::_1, std::placeholders::_2);
            ProjectCreatingWindow::Create(callback);
        }

        if(ImGui::Button("Cancel", ImVec2(100, 30))){
            Close();
        }
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
        m_lastProjectsPathList = ProjectCreationUtils::GetSavedProjects();
        for (auto projectPath : m_lastProjectsPathList) {

        }
    }

    void ProjectWizardWindow::OnProjectCreated(std::string projectName, std::string projectPath) {

    }
}