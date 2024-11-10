//
// Created by Kirill Minaev on 25.06.2024.
//

#ifndef LIGHTRAYENGINE_CONFIGURATIONSETTINGSUTILS_H
#define LIGHTRAYENGINE_CONFIGURATIONSETTINGSUTILS_H

#include <memory>
#include "ConfigurationSettings.h"

namespace LightRayEngine {
    class ConfigurationSettingsUtils {
    public:
        static ConfigurationSettings* LoadOrCreateDefaultEditorConfig();
        static void SaveEditorConfigurationSettings();
        static ConfigurationSettings*  GetSettings();
    private:
        static constexpr auto k_configFileName = "editorConfiguration.config";

        static ConfigurationSettings CreateDefaultConfig();
        static std::unique_ptr<ConfigurationSettings> s_settings;
    };
}


#endif //LIGHTRAYENGINE_CONFIGURATIONSETTINGSUTILS_H
