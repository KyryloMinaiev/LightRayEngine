//
// Created by MrFlyingChip on 21.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_LAYOUTSAVER_H
#define LIGHTRAYAPPLICATION_LAYOUTSAVER_H

#include <string>

namespace LightRayEngine {
    class LayoutSaver {
    public:
        static void SaveCurrentLayout();
    private:
        static void OnInputLayoutName(const std::string& layoutName);

        static constexpr auto k_layoutExtension = ".layout";
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_LAYOUTSAVER_H
