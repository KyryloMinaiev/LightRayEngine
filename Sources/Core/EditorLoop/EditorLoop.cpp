//
// Created by MrFlyingChip on 25.06.2024.
//

#include "EditorLoop.h"
#include "../../EditorGUI/EditorGUIController.h"

namespace LightRayEngine {
    EditorLoop::EditorLoop(EditorConfigurationSettings* editorConfiguration) {
        m_editorGuiController = std::make_unique<EditorGUIController>(editorConfiguration);
    }

    EditorLoop::~EditorLoop() = default;
    void EditorLoop::Update() {
        m_editorGuiController->StartFrame();

        m_editorGuiController->Render();
    }

    bool EditorLoop::Initialize(GLFWwindow *window) {
        if(!m_editorGuiController->Initialize(window)){
            return false;
        }

        return true;
    }
}
