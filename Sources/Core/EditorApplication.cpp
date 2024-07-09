//
// Created by MrFlyingChip on 24.06.2024.
//

#include "EditorApplication.h"
#include <iostream>

namespace LightRayEngine {
    bool EditorApplication::Open() {
        m_consoleLog = std::make_unique<ConsoleLogImpl>();
        m_fileLog = std::make_unique<FileLog>();
        m_editorConfigurationSettings = TryOpenEditorConfiguration();
        return InitializeGlfw();
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
        SaveEditorConfiguration();
        glfwDestroyWindow(m_mainWindow);
        glfwTerminate();
    }

    bool EditorApplication::TryOpenWindow(glm::ivec2& outGlVersion)
    {
            outGlVersion.x = m_editorConfigurationSettings->GetValue("glMajorVersion", availableGLVersions[0].x);
            outGlVersion.y = m_editorConfigurationSettings->GetValue("glMinorVersion", availableGLVersions[0].y);
            if(TryOpenWindowWithGLVersion(outGlVersion))
            {
                return true;
            }

        for (const auto& glVersion : availableGLVersions) {
            if(TryOpenWindowWithGLVersion(glVersion))
            {
                outGlVersion = glVersion;
                m_editorConfigurationSettings->SetField("glMajorVersion", glVersion.x);
                m_editorConfigurationSettings->SetField("glMinorVersion", glVersion.y);
                return true;
            }
        }

        return false;
    }

    bool EditorApplication::TryOpenWindowWithGLVersion(glm::ivec2 version) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version.x);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version.y);

        int width = m_editorConfigurationSettings->GetValue("editorWidth", 1024);
        int height = m_editorConfigurationSettings->GetValue("editorHeight", 768);

        m_mainWindow = glfwCreateWindow(width, height, "LightRay Engine", nullptr, nullptr);
        glfwMakeContextCurrent(m_mainWindow);
        if (!m_mainWindow)
        {
            return false;
        }

        return true;
    }


    bool EditorApplication::InitializeGlfw() {
        if (!glfwInit())
        {
            return false;
        }

        int editorMaximised = m_editorConfigurationSettings->GetValue("editorMaximised", 0);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_MAXIMIZED, editorMaximised);

        glm::ivec2 glVersion{0, 0};
        if(!TryOpenWindow(glVersion))
        {
            glfwTerminate();
            return false;
        }

        glewInit();
        LightRayLog::Log("GL_VERSION: {}",glGetString(GL_VERSION));
        LightRayLog::Log("GL_VENDOR: {}",glGetString(GL_VENDOR));
        LightRayLog::Log("GL_RENDERER: {}",glGetString(GL_RENDERER));

        glfwSwapInterval(1);
        return true;
    }

    EditorConfigurationSettings* EditorApplication::TryOpenEditorConfiguration() {
        return EditorConfigurationSettingsUtils::LoadOrCreateDefaultEditorConfig();
    }

    void EditorApplication::SaveEditorConfiguration() {
        int width, height;
        glfwGetWindowSize(m_mainWindow, &width, &height);
        m_editorConfigurationSettings->SetField("editorWidth", width);
        m_editorConfigurationSettings->SetField("editorHeight", height);
        int maximized = glfwGetWindowAttrib(m_mainWindow, GLFW_MAXIMIZED);
        m_editorConfigurationSettings->SetField("editorMaximised", maximized);
        EditorConfigurationSettingsUtils::SaveEditorConfigurationSettings();
    }
} // LightRayEngine