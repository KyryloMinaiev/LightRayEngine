//
// Created by MrFlyingChip on 24.06.2024.
//

#ifndef LIGHTRAYENGINE_EDITORAPPLICATION_H
#define LIGHTRAYENGINE_EDITORAPPLICATION_H

#include <vector>
#include <memory>
#include "platform-defines.h"
#include <glm.hpp>

#include "EditorConfigurationSettings/EditorConfigurationSettingsUtils.h"
#include "EditorLoop/EditorLoop.h"
#include "ConsoleLogImpl.h"
#include "FileLog/FileLog.h"

namespace LightRayEngine {

    class EditorApplication {
    public:
        bool Open();
        void Run();
        ~EditorApplication();
    private:
        bool InitializeGlfw();
        bool TryOpenWindow(glm::ivec2& outGlVersion);
        bool TryOpenWindowWithGLVersion(glm::ivec2 version);
        void SaveEditorConfiguration();
        static EditorConfigurationSettings* TryOpenEditorConfiguration();

        GLFWwindow *m_mainWindow;
        std::vector<glm::ivec2> availableGLVersions =
        {
            {4, 4},
            {4, 1},
            {3, 3},
            {3, 0}
        };

        EditorConfigurationSettings* m_editorConfigurationSettings;
        std::unique_ptr<EditorLoop> m_editorLoop = nullptr;
        std::unique_ptr<ConsoleLogImpl> m_consoleLog;
        std::unique_ptr<FileLog> m_fileLog;
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_EDITORAPPLICATION_H
