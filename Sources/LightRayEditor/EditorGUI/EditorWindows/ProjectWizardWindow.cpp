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
        ImGui::ShowDemoWindow();
        UpdateProjectsLastChangeTime();
        DrawWindowHeader();
        DrawProjectsTable();
        DrawWindowFooter();
    }

    ProjectWizardWindow *ProjectWizardWindow::Create(const ProjectWizardWindowData &windowData)
    {
        auto window = EditorWindowManager::CreateEditorWindow<ProjectWizardWindow>("Project Wizard");
        window->minHeight = 400;
        window->minWidth = 600;
        window->maxHeight = 400;
        window->width = 600;
        window->height = 400;
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

    void ProjectWizardWindow::UpdateProjectList(const std::vector<ProjectData> &projectList)
    {
        m_lastProjectsPathList = projectList;
    }

    ProjectWizardWindow::ProjectWizardWindow(EditorWindowManager *editorWindowManager) : EditorWindow(
            editorWindowManager)
    {}

    void ProjectWizardWindow::DrawWindowHeader() const
    {
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
    }

    void ProjectWizardWindow::DrawWindowFooter()
    {
        if (ImGui::Button("Cancel", ImVec2(100, 30)))
        {
            Close();
        }
    }

    void ProjectWizardWindow::DrawProjectsTable()
    {
        constexpr int rowMinHeight = 0;
        int selectedItem = -1;

        ImGuiTableFlags flags =
                ImGuiTableFlags_Hideable
                | ImGuiTableFlags_Sortable
                | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody
                | ImGuiTableFlags_ScrollY
                | ImGuiTableFlags_SizingStretchSame;
        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(10, 10));
        if (ImGui::BeginTable("Projects_table", 5, flags, ImVec2(0, 290)))
        {
            ImGui::TableSetupColumn(" ", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Modified", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Actions", ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupScrollFreeze(0, 1);

            ImGui::TableHeadersRow();

            ImGui::PushButtonRepeat(true);

            ImGuiListClipper clipper;
            clipper.Begin(m_lastProjectsPathList.size());
            while (clipper.Step())
            {
                for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
                {
                    auto projectData = m_lastProjectsPathList[row];

                    ImGui::PushID(projectData.path.c_str());
                    ImGui::TableNextRow(ImGuiTableRowFlags_None, rowMinHeight);

                    ImGui::TableSetColumnIndex(1);
                    if (ImGui::Selectable(projectData.name.c_str(), selectedItem == row, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap, ImVec2(0, 40)))
                    {
                        selectedItem = row;
                        m_windowData.OnOpenProjectButtonClick(projectData.path);
                    }

                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text(projectData.path.c_str());

                    ImGui::TableSetColumnIndex(3);
                    ImGui::Text(GetChangeTimeString(projectData.changeTime));

                    ImGui::TableSetColumnIndex(4);
                    if (ImGui::Button("Remove"))
                    {
                        m_windowData.OnRemoveProjectButtonClick.Invoke(projectData.path);
                    }

                    ImGui::PopID();
                }
            }

            ImGui::PopButtonRepeat();
            ImGui::EndTable();
        }

        ImGui::PopStyleVar();

//        for (const auto &project: m_lastProjectsPathList)
//        {
//            ImGui::Text(project.name.c_str());
//            ImGui::Text(project.path.c_str());
//            ImGui::SameLine();
//            ImGui::Text(GetChangeTimeString(project.changeTime));
//            ImGui::SameLine();
//            if (ImGui::Button("Open", ImVec2(100, 30)))
//            {
//                m_windowData.OnOpenProjectButtonClick.Invoke(project.path);
//            }
//
//            ImGui::SameLine();
//            if (ImGui::Button("Remove", ImVec2(100, 30)))
//            {
//                m_windowData.OnRemoveProjectButtonClick.Invoke(project.path);
//            }
//        }
    }
}