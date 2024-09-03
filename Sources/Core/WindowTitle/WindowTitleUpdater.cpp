//
// Created by MrFlyingChip on 03.09.2024.
//

#include <string>
#include <format>
#include "WindowTitleUpdater.h"
#include "../ProjectManager/ProjectManager.h"

namespace LightRayEngine {
    void WindowTitleUpdater::UpdateTitle(bool forceUpdate) {
        if (!m_window) {
            return;
        }

        std::string projectName, sceneName;
        bool updatedProjectName = UpdateProjectName(forceUpdate, projectName);
        bool updatedSceneName = UpdateSceneName(forceUpdate, sceneName);
        if (!updatedProjectName && !updatedSceneName) {
            return;
        }

        std::string title = std::format("LightRayEngine <{}> - <{}>", projectName, sceneName);
        glfwSetWindowTitle(m_window, title.c_str());
    }

    void WindowTitleUpdater::Initialize(GLFWwindow *window) {
        m_window = window;
        UpdateTitle(true);
    }

    bool WindowTitleUpdater::UpdateProjectName(bool forceUpdate, std::string& projectName) {
        auto projectData = ProjectManager::GetCurrentOpenProject();
        bool requiresProjectNameUpdate = false;

        if (m_currentProjectName != projectData.name) {
            m_currentProjectName = projectData.name;
            requiresProjectNameUpdate = true;
        }

        if (!requiresProjectNameUpdate && !forceUpdate) {
            return false;
        }

        projectName = m_currentProjectName;
        if (projectName.empty()) {
            projectName = "Empty Project";
        }

        return true;
    }

    bool WindowTitleUpdater::UpdateSceneName(bool forceUpdate, std::string& sceneName) {
        bool requiresSceneNameUpdate = false;

        if (!requiresSceneNameUpdate && !forceUpdate) {
            return false;
        }

        sceneName = m_currentSceneName;
        if (sceneName.empty()) {
            sceneName = "Empty Scene";
        }

        return true;
    }
} // LightRayEngine