#pragma once
#include "../EditorWindow.h"
#include "IEngineDefaultEditorWindow.h"

namespace LightRayEngine {
    class ProjectView : public EditorWindow, public IEngineDefaultEditorWindow {
    public:
            explicit ProjectView(EditorWindowManager *editorWindowManager);
            void OnGui() override;

        static void Create();

        std::string GetDefaultWindowName() override;
    };
}
