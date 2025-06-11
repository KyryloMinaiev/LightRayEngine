#include "EditorWindow.h"
#include "EditorWindowManager.h"

namespace LightRayEngine {
    void EditorWindow::OnCreate() {
    }

    void EditorWindow::Close() {
        m_editorWindowManager->CloseWindow(this);
    }

    EditorWindow::EditorWindow(EditorWindowManager *editorWindowManager) : m_editorWindowManager(editorWindowManager)
    {

    }
}
