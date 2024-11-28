//
// Created by MrFlyingChip on 21.11.2024.
//

#include "LayoutNameWindow.h"
#include "EditorGUI/EditorWindowManager.h"
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

namespace LightRayEngine {
    LayoutNameWindow::~LayoutNameWindow() = default;

    void LayoutNameWindow::Create(const std::function<void(const std::string&)>& onCreateButtonClick) {
        auto window = EditorWindowManager::CreateEditorWindow<LayoutNameWindow>("Save Layout");
        window->width = 250;
        window->height = 80;
        window->m_onCreateButtonClick = onCreateButtonClick;
        window->canBeDocked = false;
        window->canBeMoved = false;
        window->resizable = false;
    }

    void LayoutNameWindow::OnGui() {
        ImGui::InputText("Enter name", &m_inputName);

        bool inCorrectName = m_inputName.empty();

        ImGui::BeginDisabled(inCorrectName);
        if(ImGui::Button("Save")){
            m_onCreateButtonClick(m_inputName);
            Close();
        }
        ImGui::EndDisabled();

        ImGui::SameLine();
        if(ImGui::Button("Close")){
            Close();
        }
    }
} // LightRayEngine