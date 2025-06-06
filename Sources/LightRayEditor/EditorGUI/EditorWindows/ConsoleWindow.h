#pragma once
#include "../EditorWindow.h"
#include "IEngineDefaultEditorWindow.h"

namespace LightRayEngine {
    class ConsoleWindow : public EditorWindow, public IEngineDefaultEditorWindow {
    public:
        static void Create();

        void OnGui() override;

    private:
        std::string GetDefaultWindowName() override;
    };
}
