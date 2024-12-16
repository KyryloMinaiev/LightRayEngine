//
// Created by MrFlyingChip on 21.11.2024.
//

#include "LayoutManager.h"
#include "LayoutSaver.h"
#include "../EditorWindowManager.h"
#include "EditorConfigurationSettings/EditorConfigurationSettings.h"

namespace LightRayEngine {
    EditorLayout LayoutManager::GetCurrentLayout() {
        return EditorLayout(0);
    }

    LayoutManager::LayoutManager(EditorWindowManager *windowManager) : m_windowManager(windowManager) {

    }

    void LayoutManager::ApplyLayout(EditorConfigurationSettings *editorConfigurationSettings) {

    }

    void LayoutManager::LoadLayouts(EditorConfigurationSettings *editorConfigurationSettings) {

    }

    void LayoutManager::SaveCurrentLayout(EditorConfigurationSettings *editorConfigurationSettings) {
        LayoutSaver::SaveLayout(GetCurrentLayout(), editorConfigurationSettings);
    }
} // LightRayEngine