#pragma once
#include "../EditorWindow.h"
#include "IEngineDefaultEditorWindow.h"

namespace LightRayEngine {
    class Hierarchy : public EditorWindow, public IEngineDefaultEditorWindow {
    public:
            explicit Hierarchy(EditorWindowManager *editorWindowManager);
            void OnGui() override;

        static void Create();

        std::string GetDefaultWindowName() override;
    };
}
