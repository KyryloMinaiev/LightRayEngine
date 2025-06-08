//
// Created by MrFlyingChip on 25.06.2024.
//

#include "EditorLoop.h"
#include "EditorConfigurationSettings/EditorConfigurationSettings.h"
#include "../EditorGUI/EditorGUIController.h"
#include "../EditorGUI/EditorWindows/ProjectWizardWindow.h"
#include "AssetDatabase/AssetDatabase.h"

namespace LightRayEngine {
    EditorLoop::EditorLoop() {
        m_editorGuiController = std::make_unique<EditorGUIController>();
        m_projectManager = std::make_unique<ProjectManager>(nullptr);
        m_assetDatabase = std::make_unique<AssetDatabase>();
    }

    EditorLoop::~EditorLoop() = default;
    void EditorLoop::Update() {
        m_editorGuiController->StartFrame();
        m_editorGuiController->Render();
    }

    bool EditorLoop::Initialize(IWindow* window) {
        if(!m_editorGuiController->Initialize(window)){
            return false;
        }

        return true;
    }

    void EditorLoop::Stop() {
        m_editorGuiController->OnLoopStop();
    }

    void EditorLoop::Start() {
        m_editorGuiController->ConstructGUI();
        ProjectWizardWindow::Create();
    }
}
