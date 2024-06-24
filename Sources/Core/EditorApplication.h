//
// Created by MrFlyingChip on 24.06.2024.
//

#ifndef LIGHTRAYENGINE_EDITORAPPLICATION_H
#define LIGHTRAYENGINE_EDITORAPPLICATION_H

#define GLFW_DLL

#include <glew.h>
#include <glfw3.h>

namespace LightRayEngine {

    class EditorApplication {
        public:
            bool Open();
            void Run() const;

            ~EditorApplication();
        private:
            GLFWwindow* m_mainWindow;
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_EDITORAPPLICATION_H
