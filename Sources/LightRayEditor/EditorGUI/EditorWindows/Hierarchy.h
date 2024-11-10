#pragma once
#include "../EditorWindow.h"

namespace LightRayEngine {
    class Hierarchy : public EditorWindow {
    public:
        void OnGui() override;

        static void Create();
    };
}
