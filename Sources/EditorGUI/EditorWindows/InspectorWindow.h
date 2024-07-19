#pragma once
#include "../EditorWindow.h"

namespace LightRayEngine {
    class InspectorWindow : public EditorWindow {
    public:
        void OnGui() override;

        static void Create();
    };
}
