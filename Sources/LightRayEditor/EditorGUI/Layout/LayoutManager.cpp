//
// Created by MrFlyingChip on 21.11.2024.
//

#include "LayoutManager.h"
#include "LayoutSaver.h"
#include "../EditorWindowManager.h"
#include "EditorConfigurationSettings/EditorConfigurationSettings.h"
#include "../DockSpaceBuilder.h"

namespace LightRayEngine {
    EditorLayout LayoutManager::GetCurrentLayout() {
        auto windows = m_windowManager->GetOpenedWindows();
        auto dockSpaceID = m_dockSpaceBuilder->GetDockSpaceID();

        EditorLayout layout(dockSpaceID);
        for (auto window : windows) {
            layout.AddWindow(window);
        }

        return layout;
    }

    LayoutManager::LayoutManager(DockSpaceBuilder *dockSpaceBuilder, EditorWindowManager *windowManager)
            : m_dockSpaceBuilder(dockSpaceBuilder), m_windowManager(windowManager) {

    }

    void LayoutManager::ApplyLayout(EditorConfigurationSettings *editorConfigurationSettings) {

    }

    void LayoutManager::LoadLayouts(EditorConfigurationSettings *editorConfigurationSettings) {

    }

    void
    LayoutManager::SaveCurrentLayout(EditorConfigurationSettings *editorConfigurationSettings) {
        auto currentLayout = GetCurrentLayout();
        LayoutSaver::SaveLayout(currentLayout, editorConfigurationSettings);
    }
} // LightRayEngine