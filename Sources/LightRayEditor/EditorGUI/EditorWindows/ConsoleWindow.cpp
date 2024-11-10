#include "ConsoleWindow.h"

#include "../EditorWindowManager.h"

namespace LightRayEngine {
    void ConsoleWindow::Create() {
        auto window = EditorWindowManager::CreateEditorWindow<ConsoleWindow>("Console");
        window->width = 500;
        window->height = 300;
    }

    void ConsoleWindow::OnGui() {
    }
}
