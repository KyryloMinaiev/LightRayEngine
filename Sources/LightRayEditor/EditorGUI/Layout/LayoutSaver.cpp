//
// Created by MrFlyingChip on 21.11.2024.
//

#include "LayoutSaver.h"
#include "LayoutManager.h"
#include "NativeFileDialog.h"
#include "LayoutNameWindow.h"

namespace LightRayEngine {
    void LayoutSaver::SaveCurrentLayout() {
        LayoutNameWindow::Create(OnInputLayoutName);
    }

    void LayoutSaver::OnInputLayoutName(const std::string& layoutName) {
        EditorLayout layout = LayoutManager::GetCurrentLayout();
        std::string folder;
        NativeFileDialog::OpenFolderDialog("", folder);
        folder += std::string("/").append(layoutName).append(k_layoutExtension);
        JsonLibrary::JsonLibrary::SaveAsJson(folder, layout);
    }
} // LightRayEngine