//
// Created by MrFlyingChip on 10.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_APPLICATIONWINDOW_H
#define LIGHTRAYAPPLICATION_APPLICATIONWINDOW_H

#include "../platform-defines.h"
#include "Window/IWindow.h"

namespace LightRayEngine {

    class ApplicationWindow : public IWindow{
    public:
        ApplicationWindow(GLFWwindow* glfwWindow);
        GLFWwindow * GetGLFWWindow() const override;
    private:
        GLFWwindow* m_glfwWindow;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_APPLICATIONWINDOW_H
