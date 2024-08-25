//
// Created by MrFlyingChip on 27.07.2024.
//

#include "ProjectWizardWindow.h"
#include <ImGUI.h>
#include <misc/cpp/imgui_stdlib.h>
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
            ProjectCreationUtils::TryAddProjectByPath(selectedProjectPath);
            LoadLastProjects();
        }

        ImGui::SameLine();
        if(ImGui::Button("Create", ImVec2(100, 30))){
            auto callback = std::bind(&ProjectWizardWindow::OnProjectCreated, this, std::placeholders::_1, std::placeholders::_2);
            ProjectCreatingWindow::Create(callback);
        }

        for (const auto& project : m_lastProjectsPathList) {
            ImGui::Text(project.name.c_str());
            ImGui::Text(project.path.c_str());
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
    }

    void ProjectWizardWindow::OnProjectCreated(const std::string& projectName, const std::string& projectPath) {
        ProjectCreationUtils::TryCreateProjectByPath(projectPath, projectName);
        LoadLastProjects();
    }
}