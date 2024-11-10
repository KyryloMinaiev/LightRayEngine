//
// Created by MrFlyingChip on 24.06.2024.
//

#include "Application.h"

namespace LightRayEngine {
    bool Application::Open() {
        m_consoleLog = std::make_unique<ConsoleLogImpl>();
        m_fileLog = std::make_unique<FileLog>();
        m_editorConfigurationSettings = TryOpenEditorConfiguration();
        return InitializeGlfw();
    }

    void Application::Run() {
        m_editorLoop = std::make_unique<EditorLoop>(m_editorConfigurationSettings);
        if (!m_editorLoop->Initialize(m_mainWindow.get())) {
            LightRayLog::LogError("Cannot initialize editor loop. Quitting application!");
            return;
        }

        m_editorLoop->Start();
        while (!glfwWindowShouldClose(m_mainWindow->GetGLFWWindow())) {
            try {
                m_editorLoop->Update();
            } catch (...) {
                LightRayLog::LogException("Unknown exception in editor loop!");
            }

            glfwPollEvents();
            glfwSwapBuffers(m_mainWindow->GetGLFWWindow());
        }
    }

    Application::~Application() {
        m_editorLoop->Stop();
        SaveEditorConfiguration();
        glfwDestroyWindow(m_mainWindow->GetGLFWWindow());
        glfwTerminate();
    }

    bool Application::TryOpenWindow(glm::ivec2 &outGlVersion) {
        outGlVersion.x = m_editorConfigurationSettings->GetValue("glMajorVersion", availableGLVersions[0].x);
        outGlVersion.y = m_editorConfigurationSettings->GetValue("glMinorVersion", availableGLVersions[0].y);
        if (TryOpenWindowWithGLVersion(outGlVersion)) {
            return true;
        }

        for (const auto &glVersion: availableGLVersions) {
            if (TryOpenWindowWithGLVersion(glVersion)) {
                outGlVersion = glVersion;
                m_editorConfigurationSettings->SetField("glMajorVersion", glVersion.x);
                m_editorConfigurationSettings->SetField("glMinorVersion", glVersion.y);
                return true;
            }
        }

        return false;
    }

    bool Application::TryOpenWindowWithGLVersion(glm::ivec2 version) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version.x);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version.y);

        int width = m_editorConfigurationSettings->GetValue("editorWidth", 1024);
        int height = m_editorConfigurationSettings->GetValue("editorHeight", 768);

        LightRayLog::Log("Trying to open window with width={}, height={}. GL version: {}.{}", width, height, version.x,
                         version.y);

        auto glfwWindow = glfwCreateWindow(width, height, "LightRay Engine", nullptr, nullptr);
        m_mainWindow = std::make_unique<ApplicationWindow>(glfwWindow);
        glfwMakeContextCurrent(m_mainWindow->GetGLFWWindow());
        if (!m_mainWindow->GetGLFWWindow()) {
            return false;
        }

        LightRayLog::Log("Successfully opened window with width={}, height={}. GL version: {}.{}", width, height,
                         version.x, version.y);
        return true;
    }


    bool Application::InitializeGlfw() {
        if (!glfwInit()) {
            LightRayLog::LogError("GLFW is not inited! Quiting application!");
            return false;
        }

        int editorMaximised = m_editorConfigurationSettings->GetValue("editorMaximised", 0);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_MAXIMIZED, editorMaximised);

        glm::ivec2 glVersion{0, 0};
        if (!TryOpenWindow(glVersion)) {
            glfwTerminate();
            LightRayLog::LogError("Cannot open a window with any GL version! Quiting application!");
            return false;
        }

        glewInit();
        LightRayLog::Log("GL_VERSION: {}", glGetString(GL_VERSION));
        LightRayLog::Log("GL_VENDOR: {}", glGetString(GL_VENDOR));
        LightRayLog::Log("GL_RENDERER: {}", glGetString(GL_RENDERER));

        glfwSwapInterval(1);
        return true;
    }

    ConfigurationSettings *Application::TryOpenEditorConfiguration() {
        return ConfigurationSettingsUtils::LoadOrCreateDefaultEditorConfig();
    }

    void Application::SaveEditorConfiguration() {
        int width, height;
        glfwGetWindowSize(m_mainWindow->GetGLFWWindow(), &width, &height);
        m_editorConfigurationSettings->SetField("editorWidth", width);
        m_editorConfigurationSettings->SetField("editorHeight", height);
        int maximized = glfwGetWindowAttrib(m_mainWindow->GetGLFWWindow(), GLFW_MAXIMIZED);
        m_editorConfigurationSettings->SetField("editorMaximised", maximized);

        ConfigurationSettingsUtils::SaveEditorConfigurationSettings();
    }
} // LightRayEngine