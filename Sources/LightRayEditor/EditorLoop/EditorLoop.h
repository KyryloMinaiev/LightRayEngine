//
// Created by MrFlyingChip on 25.06.2024.
//

#ifndef LIGHTRAYENGINE_EDITORLOOP_H
#define LIGHTRAYENGINE_EDITORLOOP_H

#include <memory>
#include "Window/IWindow.h"

namespace LightRayEngine {
    class EditorGUIController;
    class ProjectManager;

    class EditorLoop {
    public:
        EditorLoop();
        ~EditorLoop();

        bool Initialize(IWindow* window);
        void Start();
        void Update();
        void Stop();
    private:
        std::unique_ptr<EditorGUIController> m_editorGuiController;
        std::unique_ptr<ProjectManager> m_projectManager;
    };
}


#endif //LIGHTRAYENGINE_EDITORLOOP_H
