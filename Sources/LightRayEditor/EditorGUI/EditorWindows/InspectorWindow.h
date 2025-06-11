#pragma once
#include "../EditorWindow.h"
#include "IEngineDefaultEditorWindow.h"

namespace LightRayEngine {
    class InspectorWindow : public EditorWindow, public IEngineDefaultEditorWindow {
    public:
            explicit InspectorWindow(EditorWindowManager *editorWindowManager);
            void OnGui() override;

        static void Create();

        std::string GetDefaultWindowName() override;
    };
}
