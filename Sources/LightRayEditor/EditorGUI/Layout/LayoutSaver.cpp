//
// Created by MrFlyingChip on 21.11.2024.
//

#include "LayoutSaver.h"
#include "LayoutManager.h"
#include "NativeFileDialog.h"
#include "LayoutNameWindow.h"
#include "LightRayLog.h"
#include "EditorConfigurationSettings/EditorConfigurationSettings.h"

namespace LightRayEngine {
    LayoutManager* LayoutSaver::s_layoutManager;

    void LayoutSaver::SaveCurrentLayout() {
        LayoutNameWindow::Create(OnInputLayoutName);
    }

    void LayoutSaver::OnInputLayoutName(const std::string& layoutName) {
        if(!s_layoutManager){
            LightRayLog::LogError("LayoutManager is nullptr in LayoutSaver while trying to save layout!");
            return;
        }

        EditorLayout layout = s_layoutManager->GetCurrentLayout();
        std::string folder;
        NativeFileDialog::OpenFolderDialog("", folder);
        folder += std::string("/").append(layoutName).append(k_layoutExtension);
        JsonLibrary::JsonLibrary::SaveAsJson(folder, layout);
    }

    void LayoutSaver::Init(LayoutManager* layoutManager) {
        s_layoutManager = layoutManager;
    }

    void LayoutSaver::SaveLayout(EditorLayout &editorLayout, EditorConfigurationSettings *editorConfigurationSettings) {
        auto json = JsonLibrary::JsonLibrary::ToJsonObject(editorLayout);
        editorConfigurationSettings->SetField("currentLayout", json);
    }
} // LightRayEngine