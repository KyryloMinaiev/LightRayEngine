//
// Created by MrFlyingChip on 21.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_LAYOUTSAVER_H
#define LIGHTRAYAPPLICATION_LAYOUTSAVER_H

#include <string>
#include "EditorLayout.h"

namespace LightRayEngine {
    class EditorConfigurationSettings;
    class LayoutManager;

    class LayoutSaver {
    public:
        static void Init(LayoutManager* layoutManager);
        static void SaveCurrentLayout();
        static void SaveLayout(EditorLayout& editorLayout, EditorConfigurationSettings* editorConfigurationSettings);
    private:
        static void OnInputLayoutName(const std::string& layoutName);
        static LayoutManager* s_layoutManager;

        static constexpr auto k_layoutExtension = ".layout";
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_LAYOUTSAVER_H
