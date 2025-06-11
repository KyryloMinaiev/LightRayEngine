//
// Created by MrFlyingChip on 25.06.2024.
//

#ifndef LIGHTRAYENGINE_EDITORLOOP_H
#define LIGHTRAYENGINE_EDITORLOOP_H

#include <memory>
#include "Window/IWindow.h"
#include "ProjectManager/OpenProjectSequence.h"

namespace LightRayEngine
{
    class EditorGUIController;
    class ProjectManager;
    class AssetDatabase;

    class EditorLoop
    {
        public:
            EditorLoop();
            ~EditorLoop();

            bool Initialize(IWindow *window);
            void Start();
            void Update();
            void Stop();
        private:
            void OnProjectOpened(bool success, const std::string& path);

            std::unique_ptr<EditorGUIController> m_editorGuiController;
            std::unique_ptr<ProjectManager> m_projectManager;
            std::unique_ptr<AssetDatabase> m_assetDatabase;

            OpenProjectSequence m_openProjectSequence;
    };
}


#endif //LIGHTRAYENGINE_EDITORLOOP_H
