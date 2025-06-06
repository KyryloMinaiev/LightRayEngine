#pragma once
#include "../EditorWindow.h"
#include "IEngineDefaultEditorWindow.h"

namespace LightRayEngine {
    class Hierarchy : public EditorWindow, public IEngineDefaultEditorWindow {
    public:
        void OnGui() override;

        static void Create();

        std::string GetDefaultWindowName() override;
    };
}
