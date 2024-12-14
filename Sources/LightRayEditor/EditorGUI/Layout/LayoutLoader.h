//
// Created by MrFlyingChip on 21.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_LAYOUTLOADER_H
#define LIGHTRAYAPPLICATION_LAYOUTLOADER_H

#include <vector>
#include <string>

namespace LightRayEngine {
    class EditorConfigurationSettings;

    class LayoutLoader {
    public:
        static std::vector<std::string> LoadAvailableLayouts(EditorConfigurationSettings *settings);
    private:
        static constexpr auto k_defaultLayoutsFolder = "Resources/Default Layouts/";
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_LAYOUTLOADER_H
