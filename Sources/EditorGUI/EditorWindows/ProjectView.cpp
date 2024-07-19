#include "ProjectView.h"

#include "../EditorWindowManager.h"

namespace LightRayEngine {
    void ProjectView::OnGui() {
    }

    void ProjectView::Create() {
        auto window = EditorWindowManager::CreateEditorWindow<ProjectView>("Project");
        window->width = 500;
        window->height = 300;
    }
}
