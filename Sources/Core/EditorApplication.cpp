//
// Created by MrFlyingChip on 24.06.2024.
//

#include "EditorApplication.h"

namespace LightRayEngine {
    bool EditorApplication::Open() {
        if (!glfwInit())
        {
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

        m_mainWindow = glfwCreateWindow(1024, 768, "LightRay Engine", nullptr, nullptr);

        glfwMakeContextCurrent(m_mainWindow);
        if (glewInit() != GLEW_OK)
        {
            return false;
        }

        glfwSwapInterval(1);

        return true;
    }

    void EditorApplication::Run() const {
        while (!glfwWindowShouldClose(m_mainWindow)) {
            glfwPollEvents();
            glfwSwapBuffers(m_mainWindow);
        }
    }

    EditorApplication::~EditorApplication()
    {
        glfwDestroyWindow(m_mainWindow);
        glfwTerminate();
    }
} // LightRayEngine