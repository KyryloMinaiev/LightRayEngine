//
// Created by MrFlyingChip on 03.09.2024.
//

#ifndef LIGHTRAYENGINE_WINDOWTITLEUPDATER_H
#define LIGHTRAYENGINE_WINDOWTITLEUPDATER_H

#include "GLFW/glfw3.h"

namespace LightRayEngine {

    class WindowTitleUpdater {
    public:
        WindowTitleUpdater() = default;
        void Initialize(GLFWwindow* window);
        void UpdateTitle(bool forceUpdate = false);
    private:
        bool UpdateProjectName(bool forceUpdate, std::string& projectName);
        bool UpdateSceneName(bool forceUpdate, std::string& sceneName);

        GLFWwindow* m_window = nullptr;
        std::string m_currentProjectName;
        std::string m_currentSceneName;
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_WINDOWTITLEUPDATER_H
