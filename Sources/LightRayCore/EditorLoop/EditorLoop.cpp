//
// Created by MrFlyingChip on 25.06.2024.
//

#include "EditorLoop.h"
#include "../../EditorGUI/EditorGUIController.h"
#include "../WindowTitle/WindowTitleUpdater.h"
#include "../../EditorGUI/EditorWindows/ProjectWizardWindow.h"

namespace LightRayEngine {
    EditorLoop::EditorLoop(EditorConfigurationSettings* editorConfiguration) {
        m_editorGuiController = std::make_unique<EditorGUIController>(editorConfiguration);
        m_windowTitleUpdater = std::make_unique<WindowTitleUpdater>();
        ProjectManager::Init(editorConfiguration, nullptr);
    }

    EditorLoop::~EditorLoop() = default;
    void EditorLoop::Update() {
        m_editorGuiController->StartFrame();

        m_windowTitleUpdater->UpdateTitle();

        m_editorGuiController->Render();
    }

    bool EditorLoop::Initialize(GLFWwindow *window) {
        if(!m_editorGuiController->Initialize(window)){
            return false;
        }

        m_windowTitleUpdater->Initialize(window);
        return true;
    }

    void EditorLoop::Stop() {
        m_editorGuiController->OnLoopStop();
    }

    void EditorLoop::Start() {
        ProjectWizardWindow::Create();
    }
}
