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
            ProjectManager::TryAddProjectByPath(selectedProjectPath);
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
            ImGui::SameLine();
            ImGui::Text(GetChangeTimeString(project.changeTime));
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
        m_lastProjectsPathList = ProjectManager::GetSavedProjects();
        std::time_t now = std::time(nullptr);
        m_currentTime = SerializedTime(*std::localtime(&now));
    }

    void ProjectWizardWindow::OnProjectCreated(const std::string& projectName, const std::string& projectPath) {
        ProjectManager::TryCreateProjectByPath(projectPath, projectName);
        LoadLastProjects();
    }

    const char* ProjectWizardWindow::GetChangeTimeString(const SerializedTime &changeTime) {
        if(m_currentTime.tm_year - changeTime.tm_year > 0){
            return "More than a year ago";
        }

        if(m_currentTime.tm_mon - changeTime.tm_year > 1){
            return "Less than a year ago";
        }

        if(m_currentTime.tm_mday - changeTime.tm_mday > 1){
            return "Less than a month ago";
        }

        if(m_currentTime.tm_hour - changeTime.tm_hour > 1){
            return "More than a hour ago";
        }

        if(m_currentTime.tm_min - changeTime.tm_min > 5){
            return "Less than a hour ago";
        }

        return "A moment ago";
    }
}