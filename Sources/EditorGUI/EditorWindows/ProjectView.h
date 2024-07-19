#pragma once
#include "../EditorWindow.h"

namespace LightRayEngine {
    class ProjectView : public EditorWindow {
    public:
        void OnGui() override;

        static void Create();
    };
}
