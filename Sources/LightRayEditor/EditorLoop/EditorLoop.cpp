//
// Created by MrFlyingChip on 25.06.2024.
//

#include "EditorLoop.h"
#include "../EditorGUI/EditorGUIController.h"
#include "AssetDatabase/AssetDatabase.h"
#include "ProjectManager/ProjectManager.h"
#include "Generic/Delegates/Action.h"

namespace LightRayEngine
{
    EditorLoop::EditorLoop() : m_editorGuiController(std::make_unique<EditorGUIController>()),
                               m_projectManager(std::make_unique<ProjectManager>()),
                               m_assetDatabase(std::make_unique<AssetDatabase>()),
                               m_openProjectSequence(m_projectManager.get())
    {
    }

    EditorLoop::~EditorLoop() = default;

    void EditorLoop::Update()
    {
        m_editorGuiController->StartFrame();
        m_editorGuiController->Render();
    }

    bool EditorLoop::Initialize(IWindow *window)
    {
        if (!m_editorGuiController->Initialize(window))
        {
            return false;
        }

        return true;
    }

    void EditorLoop::Stop()
    {
        m_editorGuiController->OnLoopStop();
    }

    void EditorLoop::Start()
    {
        m_editorGuiController->ConstructGUI();
        m_openProjectSequence.StartSequence(CreateAction(this, &EditorLoop::OnProjectOpened));
    }

    void EditorLoop::OnProjectOpened(bool success, const std::string &path)
    {

    }
}
