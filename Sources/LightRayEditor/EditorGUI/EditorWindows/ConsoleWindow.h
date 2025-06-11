#pragma once
#include "../EditorWindow.h"
#include "IEngineDefaultEditorWindow.h"

namespace LightRayEngine {
    class ConsoleWindow : public EditorWindow, public IEngineDefaultEditorWindow {
    public:
            explicit ConsoleWindow(EditorWindowManager *editorWindowManager);
            static void Create();

        void OnGui() override;

    private:
        std::string GetDefaultWindowName() override;
    };
}
