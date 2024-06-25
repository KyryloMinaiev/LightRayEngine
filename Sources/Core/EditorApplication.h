//
// Created by MrFlyingChip on 24.06.2024.
//

#ifndef LIGHTRAYENGINE_EDITORAPPLICATION_H
#define LIGHTRAYENGINE_EDITORAPPLICATION_H

#include <vector>
#include "platform-defines.h"

namespace LightRayEngine {

    class EditorApplication {
    public:
        bool Open();

        void Run() const;

        ~EditorApplication();

    private:
        struct ivec2 {
            int x;
            int y;
        };

        bool TryOpenWindow();
        bool TryOpenWindowWithGLVersion(ivec2 version);
        void TryOpenEditorConfiguration();

        GLFWwindow *m_mainWindow;
        std::vector<ivec2> availableGLVersions =
        {
            {4, 4},
            {4, 1},
            {3, 3},
            {3, 0}
        };
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_EDITORAPPLICATION_H
