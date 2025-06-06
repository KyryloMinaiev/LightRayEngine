#pragma once
#include "../EditorWindow.h"
#include "IEngineDefaultEditorWindow.h"

namespace LightRayEngine {
    class ProjectView : public EditorWindow, public IEngineDefaultEditorWindow {
    public:
        void OnGui() override;

        static void Create();

        std::string GetDefaultWindowName() override;
    };
}
