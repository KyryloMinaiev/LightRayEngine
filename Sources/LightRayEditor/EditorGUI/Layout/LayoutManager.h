//
// Created by MrFlyingChip on 21.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_LAYOUTMANAGER_H
#define LIGHTRAYAPPLICATION_LAYOUTMANAGER_H

#include "EditorLayout.h"

namespace LightRayEngine {
    class EditorConfigurationSettings;
    class EditorWindowManager;

    class LayoutManager {
    public:
        explicit LayoutManager(EditorWindowManager* windowManager);
        void LoadLayouts(EditorConfigurationSettings* editorConfigurationSettings);
        void ApplyLayout(EditorConfigurationSettings* editorConfigurationSettings);

        void SaveCurrentLayout(EditorConfigurationSettings* editorConfigurationSettings);

        EditorLayout GetCurrentLayout();

    private:
        EditorWindowManager* m_windowManager{};
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_LAYOUTMANAGER_H
