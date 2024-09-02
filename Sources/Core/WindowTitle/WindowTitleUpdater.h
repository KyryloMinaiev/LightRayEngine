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
        void UpdateTitle();
    private:
        GLFWwindow* m_window = nullptr;
        std::string m_currentProjectName = "Empty Project";
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_WINDOWTITLEUPDATER_H
