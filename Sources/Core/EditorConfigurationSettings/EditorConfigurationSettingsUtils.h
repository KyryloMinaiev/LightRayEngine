//
// Created by Kirill Minaev on 25.06.2024.
//

#ifndef LIGHTRAYENGINE_EDITORCONFIGURATIONSETTINGSUTILS_H
#define LIGHTRAYENGINE_EDITORCONFIGURATIONSETTINGSUTILS_H

#include <memory>
#include "EditorConfigurationSettings.h"

namespace LightRayEngine {
    class EditorConfigurationSettingsUtils {
    public:
        static EditorConfigurationSettings* LoadOrCreateDefaultEditorConfig();
        static void SaveEditorConfigurationSettings();
        static EditorConfigurationSettings*  GetSettings();
    private:
        static constexpr auto k_configFileName = "editorConfiguration.config";

        static EditorConfigurationSettings CreateDefaultConfig();
        static std::unique_ptr<EditorConfigurationSettings> s_settings;
    };
}


#endif //LIGHTRAYENGINE_EDITORCONFIGURATIONSETTINGSUTILS_H
