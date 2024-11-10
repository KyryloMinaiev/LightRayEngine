#pragma once
#include "../EditorWindow.h"

namespace LightRayEngine {
    class ConsoleWindow : public EditorWindow {
    public:
        static void Create();

        void OnGui() override;
    };
}
