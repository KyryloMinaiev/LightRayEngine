//
// Created by MrFlyingChip on 10.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_IWINDOW_H
#define LIGHTRAYAPPLICATION_IWINDOW_H

class GLFWwindow;

namespace LightRayEngine {
    class IWindow {
    public:
        virtual GLFWwindow* GetGLFWWindow() const = 0;
    };
}

#endif //LIGHTRAYAPPLICATION_IWINDOW_H
