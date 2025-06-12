//
// Created by MrFlyingChip on 27.07.2024.
//

#include "ProjectWizardWindow.h"
#include <ImGUI.h>
#include "../EditorWindowManager.h"
#include "ProjectCreatingWindow.h"

namespace LightRayEngine
{
    void ProjectWizardWindow::OnCreate()
    {
        UpdateProjectsLastChangeTime();
    }

    void ProjectWizardWindow::OnGui()
    {
        //ImGui::ShowDemoWindow();
        UpdateProjectsLastChangeTime();

        ImGui::Text("Projects:");
        ImGui::SameLine();
        if (ImGui::Button("Add", ImVec2(100, 30)))
        {
            m_windowData.OnProjectAddButtonClick.Invoke();
        }

        ImGui::SameLine();
        if (ImGui::Button("Create", ImVec2(100, 30)))
        {
            m_windowData.OnCreateProjectButtonClick.Invoke();
        }

        for (const auto &project: m_lastProjectsPathList)
        {
            ImGui::Text(project.name.c_str());
            ImGui::Text(project.path.c_str());
            ImGui::SameLine();
            ImGui::Text(GetChangeTimeString(project.changeTime));
            ImGui::SameLine();
            if (ImGui::Button("Open", ImVec2(100, 30)))
            {
                m_windowData.OnOpenProjectButtonClick.Invoke(project.path);
            }

            ImGui::SameLine();
            if (ImGui::Button("Remove", ImVec2(100, 30)))
            {
                m_windowData.OnRemoveProjectButtonClick.Invoke(project.path);
            }
        }

        if (ImGui::Button("Cancel", ImVec2(100, 30)))
        {
            Close();
        }
    }

    ProjectWizardWindow* ProjectWizardWindow::Create(const ProjectWizardWindowData &windowData)
    {
        auto window = EditorWindowManager::CreateEditorWindow<ProjectWizardWindow>("Project Wizard");
        window->width = 600;
        window->height = 400;
        window->resizable = false;
        window->canBeDocked = false;
        window->m_windowData = windowData;
        window->saveWindowData = false;
        ImGui::SetNextWindowFocus();

        return window;
    }

    void ProjectWizardWindow::UpdateProjectsLastChangeTime()
    {
        std::time_t now = std::time(nullptr);
        m_currentTime = SerializedTime(*std::localtime(&now));
    }

    const char *ProjectWizardWindow::GetChangeTimeString(const SerializedTime &changeTime)
    {
        if (m_currentTime.tm_year - changeTime.tm_year > 0)
        {
            return "More than a year ago";
        }

        if (m_currentTime.tm_mon - changeTime.tm_mon > 1)
        {
            return "Less than a year ago";
        }

        if (m_currentTime.tm_mday - changeTime.tm_mday > 1)
        {
            return "Less than a month ago";
        }

        if (m_currentTime.tm_hour - changeTime.tm_hour > 1)
        {
            return "More than a hour ago";
        }

        if (m_currentTime.tm_min - changeTime.tm_min > 5)
        {
            return "Less than a hour ago";
        }

        return "A moment ago";
    }

    void ProjectWizardWindow::UpdateProjectList(std::vector<ProjectData> projectList)
    {
        m_lastProjectsPathList = projectList;
    }

    ProjectWizardWindow::ProjectWizardWindow(EditorWindowManager *editorWindowManager) : EditorWindow(
            editorWindowManager)
    {}
}