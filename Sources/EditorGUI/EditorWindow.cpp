#include "EditorWindow.h"
#include "EditorWindowManager.h"

namespace LightRayEngine {
    void EditorWindow::OnCreate() {
    }

    void EditorWindow::Close() {
        EditorWindowManager::CloseWindow(this);
    }
}
