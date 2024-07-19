#include "InspectorWindow.h"

#include "../EditorWindowManager.h"

namespace LightRayEngine {
    void InspectorWindow::OnGui() {
    }

    void InspectorWindow::Create() {
        auto window = EditorWindowManager::CreateEditorWindow<InspectorWindow>("Inspector");
        window->width = 500;
        window->height = 300;
    }
}
