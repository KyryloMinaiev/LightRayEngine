//
// Created by Kirill Minaev on 13.07.2024.
//

#ifndef LIGHTRAYENGINE_EDITORGUICONTROLLER_H
#define LIGHTRAYENGINE_EDITORGUICONTROLLER_H

#include "../Core/EditorLoop/EditorLoopSystem.h"
#include "../Core/platform-defines.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace LightRayEngine {
    class MenuToolbar;

    class EditorGUIController : public EditorLoopSystem{
        public:
            explicit EditorGUIController(EditorConfigurationSettings *editorSettings);

            bool Initialize(GLFWwindow* window);
            void StartFrame();
            void Render();

            ~EditorGUIController() override;

        private:
            static bool InitializeImGUI(GLFWwindow* window);
            bool InitializeMenuToolbar();

            std::unique_ptr<MenuToolbar> m_menuToolbar;
    };
}


#endif //LIGHTRAYENGINE_EDITORGUICONTROLLER_H
