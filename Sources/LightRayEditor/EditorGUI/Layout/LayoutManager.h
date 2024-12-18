//
// Created by MrFlyingChip on 21.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_LAYOUTMANAGER_H
#define LIGHTRAYAPPLICATION_LAYOUTMANAGER_H

#include "EditorLayout.h"
#include <vector>
#include <string>

namespace LightRayEngine {
    class EditorConfigurationSettings;
    class EditorWindowManager;
    class DockSpaceBuilder;

    class LayoutManager {
    public:
        explicit LayoutManager(DockSpaceBuilder* dockSpaceBuilder, EditorWindowManager* windowManager);
        void LoadLayouts(EditorConfigurationSettings* editorConfigurationSettings);
        void ApplySavedLayout(EditorConfigurationSettings* editorConfigurationSettings);

        void SaveCurrentLayout(EditorConfigurationSettings* editorConfigurationSettings);

        EditorLayout GetCurrentLayout();

    private:
        DockSpaceBuilder* m_dockSpaceBuilder;
        EditorWindowManager* m_windowManager;

        std::vector<std::string> m_loadedLayouts;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_LAYOUTMANAGER_H
