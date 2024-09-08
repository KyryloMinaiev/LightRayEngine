//
// Created by MrFlyingChip on 25.06.2024.
//

#ifndef LIGHTRAYENGINE_EDITORLOOP_H
#define LIGHTRAYENGINE_EDITORLOOP_H

#include "../EditorConfigurationSettings/EditorConfigurationSettings.h"
#include "../platform-defines.h"
#include <memory>

namespace LightRayEngine {
    class EditorGUIController;
    class WindowTitleUpdater;
    class AssetDatabase;

    class EditorLoop {
    public:
        explicit EditorLoop(EditorConfigurationSettings* editorConfiguration);
        ~EditorLoop();

        bool Initialize(GLFWwindow* window);
        void Start();
        void Update();
        void Stop();
    private:
        std::unique_ptr<WindowTitleUpdater> m_windowTitleUpdater;
        std::unique_ptr<EditorGUIController> m_editorGuiController;
        std::unique_ptr<AssetDatabase> m_assetDatabase;
    };
}


#endif //LIGHTRAYENGINE_EDITORLOOP_H
