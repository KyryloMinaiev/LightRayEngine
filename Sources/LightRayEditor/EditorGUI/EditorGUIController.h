//
// Created by Kirill Minaev on 13.07.2024.
//

#ifndef LIGHTRAYENGINE_EDITORGUICONTROLLER_H
#define LIGHTRAYENGINE_EDITORGUICONTROLLER_H

#include <memory>
#include "../EditorLoop/EditorLoopSystem.h"
#include "Window/IWindow.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace LightRayEngine {
    class MenuToolbar;
    class EditorWindowManager;
    class LayoutManager;
    class DockSpaceBuilder;

    class EditorGUIController : public EditorLoopSystem{
        public:
            explicit EditorGUIController();

            bool Initialize(IWindow* window);
            void StartFrame();
            void Render();

        void OnLoopStop() override;

        ~EditorGUIController() override;

        private:
            static bool InitializeImGUI(IWindow* window);
            bool InitializeMenuToolbar();
            bool InitializeLayoutManager();

            std::unique_ptr<DockSpaceBuilder> m_dockSpaceBuilder;
            std::unique_ptr<LayoutManager> m_layoutManager;
            std::unique_ptr<MenuToolbar> m_menuToolbar;
            std::unique_ptr<EditorWindowManager> m_editorWindowManager;
    };
}


#endif //LIGHTRAYENGINE_EDITORGUICONTROLLER_H
