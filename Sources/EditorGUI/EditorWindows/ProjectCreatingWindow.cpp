//
// Created by MrFlyingChip on 21.08.2024.
//

#include "ProjectCreatingWindow.h"
#include "../EditorWindowManager.h"
#include <ImGUI.h>
#include <misc/cpp/imgui_stdlib.h>
#include "NativeFileDialog.h"
#include <utility>

namespace LightRayEngine {
    void ProjectCreatingWindow::OnGui() {
        ImGui::Text("Project Name");
        ImGui::SameLine();
        ImGui::InputText("##projectName", &m_projectName);
        ImGui::Text("Project Path");
        ImGui::SameLine();
        ImGui::InputText("##projectPath", &m_projectPath);
        ImGui::SameLine();
        if (ImGui::Button("...", ImVec2(18, 18))) {
            NativeFileDialog::OpenFolderDialog("", m_projectPath);
        }

        bool isDisabled = !(IsNameValid() && IsPathValid());
        if (isDisabled) {
            ImGui::BeginDisabled();
        }
        if (ImGui::Button("Create", ImVec2(100, 30))) {
            if (m_projectCreationCallback) {
                m_projectCreationCallback(m_projectName, m_projectPath);
            }
        }
        if (isDisabled) {
            ImGui::EndDisabled();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(100, 30))) {
            Close();
        }
    }

    void ProjectCreatingWindow::Create(ProjectCreationCallback projectCreationCallback) {
        auto window = EditorWindowManager::CreateEditorWindow<ProjectCreatingWindow>("Create Project");
        window->width = 600;
        window->height = 400;
        window->resizable = false;
        window->canBeDocked = false;
        window->m_projectCreationCallback = std::move(projectCreationCallback);
        ImGui::SetNextWindowFocus();
    }

    bool ProjectCreatingWindow::IsNameValid() {
        return !m_projectName.empty();
    }

    bool ProjectCreatingWindow::IsPathValid() {
        return !m_projectPath.empty();
    }
} // LightRayEngine