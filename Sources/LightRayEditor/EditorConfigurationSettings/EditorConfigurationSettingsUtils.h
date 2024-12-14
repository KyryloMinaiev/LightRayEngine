//
// Created by Kirill Minaev on 25.06.2024.
//

#ifndef LIGHTRAYENGINE_CONFIGURATIONSETTINGSUTILS_H
#define LIGHTRAYENGINE_CONFIGURATIONSETTINGSUTILS_H

#include <memory>
#include "EditorConfigurationSettings.h"

namespace LightRayEngine {
    class EditorConfigurationSettingsUtils {
    public:
        static void SaveEditorConfigurationSettings();
        static EditorConfigurationSettings*  GetSettings();
    private:
        static constexpr auto k_configFileName = "editorConfiguration.config";

        static EditorConfigurationSettings CreateDefaultConfig();
        static void LoadOrCreateDefaultEditorConfig();
        static std::unique_ptr<EditorConfigurationSettings> s_settings;
    };
}


#endif //LIGHTRAYENGINE_CONFIGURATIONSETTINGSUTILS_H
