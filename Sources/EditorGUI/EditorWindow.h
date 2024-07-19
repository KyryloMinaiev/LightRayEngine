#pragma once

#include <string>

namespace LightRayEngine {
    class EditorWindow {
    public:
        virtual ~EditorWindow() = default;

        virtual void OnCreate();

        virtual void OnGui() = 0;

        float width = 0;
        float height = 0;

        int positionX = 0;
        int positionY = 0;

        bool isDocked;
        unsigned int dockId;
        bool isFocused;

        std::string title;
    };
}
