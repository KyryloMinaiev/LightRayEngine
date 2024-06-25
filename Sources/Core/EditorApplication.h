//
// Created by MrFlyingChip on 24.06.2024.
//

#ifndef LIGHTRAYENGINE_EDITORAPPLICATION_H
#define LIGHTRAYENGINE_EDITORAPPLICATION_H

#include <vector>
#include <memory>
#include "platform-defines.h"

#include "EditorConfigurationSettings/EditorConfigurationSettings.h"
#include "EditorLoop/EditorLoop.h"

namespace LightRayEngine {

    class EditorApplication {
    public:
        bool Open();
        void Run();
        ~EditorApplication();
    private:
        struct ivec2 {
            int x;
            int y;
        };

        bool InitializeGlfw(const EditorConfigurationSettings& editorConfiguration);
        bool TryOpenWindow(ivec2& outGlVersion);
        bool TryOpenWindowWithGLVersion(ivec2 version);
        EditorConfigurationSettings TryOpenEditorConfiguration();

        GLFWwindow *m_mainWindow;
        std::vector<ivec2> availableGLVersions =
        {
            {4, 4},
            {4, 1},
            {3, 3},
            {3, 0}
        };

        EditorConfigurationSettings m_editorConfigurationSettings;
        std::unique_ptr<EditorLoop> m_editorLoop = nullptr;
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_EDITORAPPLICATION_H
