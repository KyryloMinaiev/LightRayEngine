//
// Created by MrFlyingChip on 10.11.2024.
//

#include "ApplicationWindow.h"

namespace LightRayEngine {
    ApplicationWindow::ApplicationWindow(GLFWwindow *glfwWindow) {
        m_glfwWindow = glfwWindow;
    }

    GLFWwindow *ApplicationWindow::GetGLFWWindow() const {
        return m_glfwWindow;
    }
} // LightRayEngine