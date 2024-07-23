#include "Hierarchy.h"

#include "../EditorWindowManager.h"

namespace LightRayEngine {
    void Hierarchy::OnGui() {
    }

    void Hierarchy::Create() {
        auto window = EditorWindowManager::CreateEditorWindow<Hierarchy>("Hierarchy");
        window->width = 500;
        window->height = 300;
    }
}
