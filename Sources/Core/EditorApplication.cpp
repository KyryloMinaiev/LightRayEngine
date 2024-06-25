//
// Created by MrFlyingChip on 24.06.2024.
//

#include "EditorApplication.h"

#include <iostream>

namespace LightRayEngine {
    bool EditorApplication::Open() {
        m_editorConfigurationSettings = TryOpenEditorConfiguration();
        return InitializeGlfw(m_editorConfigurationSettings);
    }

    void EditorApplication::Run() {
        m_editorLoop = std::make_unique<EditorLoop>(m_editorConfigurationSettings);

        while (!glfwWindowShouldClose(m_mainWindow)) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            glClearColor(1, 1, 1, 1);
            glClearDepth(0);
            glClearStencil(0);

            glfwPollEvents();
            glfwSwapBuffers(m_mainWindow);
        }
    }

    EditorApplication::~EditorApplication()
    {
        glfwDestroyWindow(m_mainWindow);
        glfwTerminate();
    }

    bool EditorApplication::TryOpenWindow(ivec2& outGlVersion)
    {
        for (const auto& glVersion : availableGLVersions) {
            if(TryOpenWindowWithGLVersion(glVersion))
            {
                outGlVersion = glVersion;
                return true;
            }
        }

        return false;
    }

    bool EditorApplication::TryOpenWindowWithGLVersion(EditorApplication::ivec2 version) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version.x);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version.y);

        m_mainWindow = glfwCreateWindow(1024, 768, "LightRay Engine", nullptr, nullptr);
        glfwMakeContextCurrent(m_mainWindow);
        if (!m_mainWindow)
        {
            return false;
        }

        return true;
    }


    bool EditorApplication::InitializeGlfw(const EditorConfigurationSettings &editorConfiguration) {
        if (!glfwInit())
        {
            return false;
        }

        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

        ivec2 glVersion{0, 0};
        if(!TryOpenWindow(glVersion))
        {
            glfwTerminate();
            return false;
        }

        glewInit();
        std::cout << glGetString(GL_VERSION) << "\n";
        std::cout << glGetString(GL_VENDOR) << "\n";
        std::cout << glGetString(GL_RENDERER) << "\n";

        glfwSwapInterval(1);
        return true;
    }

    EditorConfigurationSettings EditorApplication::TryOpenEditorConfiguration() {
        return EditorConfigurationSettings();
    }
} // LightRayEngine