//
// Created by MrFlyingChip on 03.09.2024.
//

#include <string>
#include <format>
#include "WindowTitleUpdater.h"
#include "../ProjectManager/ProjectManager.h"

namespace LightRayEngine {
    void WindowTitleUpdater::UpdateTitle() {
        if (!m_window) {
            return;
        }

        auto projectData = ProjectManager::GetCurrentOpenProject();
        bool requiresTitleUpdate = false;

        if (m_currentProjectName != projectData.name) {
            m_currentProjectName = projectData.name;
            requiresTitleUpdate = true;
        }

        if (!requiresTitleUpdate) {
            return;
        }

        std::string title = std::format("LightRayEngine <{}>", m_currentProjectName);
        glfwSetWindowTitle(m_window, title.c_str());
    }

    void WindowTitleUpdater::Initialize(GLFWwindow *window) {
        m_window = window;
    }
} // LightRayEngine