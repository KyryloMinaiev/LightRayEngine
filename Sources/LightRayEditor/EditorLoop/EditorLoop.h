//
// Created by MrFlyingChip on 25.06.2024.
//

#ifndef LIGHTRAYENGINE_EDITORLOOP_H
#define LIGHTRAYENGINE_EDITORLOOP_H

#include <memory>
#include "Window/IWindow.h"

namespace LightRayEngine {
    class EditorGUIController;
    class WindowTitleUpdater;
    class EditorConfigurationSettings;

    class EditorLoop {
    public:
        explicit EditorLoop(EditorConfigurationSettings* editorConfiguration);
        ~EditorLoop();

        bool Initialize(IWindow* window);
        void Start();
        void Update();
        void Stop();
    private:
        //std::unique_ptr<WindowTitleUpdater> m_windowTitleUpdater;
        std::unique_ptr<EditorGUIController> m_editorGuiController;
    };
}


#endif //LIGHTRAYENGINE_EDITORLOOP_H
