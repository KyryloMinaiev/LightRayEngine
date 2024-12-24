//
// Created by MrFlyingChip on 21.11.2024.
//

#include "LayoutLoader.h"
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
        LayoutSaver::Init(this);
    }

    void LayoutManager::ApplySavedLayout(EditorConfigurationSettings *editorConfigurationSettings) {
        if(!editorConfigurationSettings->Contains("savedLayout")){
            return;
        }

        EditorLayout layout;
        editorConfigurationSettings->GetField("savedLayout").DecodeObject(layout);
        ApplyLayout(layout);
    }

    void LayoutManager::LoadLayouts(EditorConfigurationSettings *editorConfigurationSettings) {
        m_loadedLayouts = LayoutLoader::LoadAvailableLayouts(editorConfigurationSettings);
    }

    void
    LayoutManager::SaveCurrentLayout(EditorConfigurationSettings *editorConfigurationSettings) {
        auto currentLayout = GetCurrentLayout();
        LayoutSaver::SaveLayout(currentLayout, editorConfigurationSettings);
    }

    void LayoutManager::ApplyLayout(EditorLayout &editorLayout) {
        m_dockSpaceBuilder->CleanDockSpace();
        m_windowManager->CloseAllWindows();

        m_dockSpaceBuilder->RebuildDockSpace(editorLayout.dockingData);
        EditorWindowManager::CreateWindows(editorLayout.windows);
    }
} // LightRayEngine