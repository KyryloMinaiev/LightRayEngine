//
// Created by Kirill Minaev on 25.06.2024.
//

#include "ConfigurationSettingsUtils.h"
#include "LightRayLog.h"
#include "FileUtils.h"

namespace LightRayEngine {
    std::unique_ptr<ConfigurationSettings> ConfigurationSettingsUtils::s_settings;

    ConfigurationSettings *ConfigurationSettingsUtils::LoadOrCreateDefaultEditorConfig() {
        std::string configStr;
        ConfigurationSettings settings;
        bool configCreated = false;
        if (FileUtils::TryLoadFile(k_configFileName, configStr)) {
            settings = JsonLibrary::JsonLibrary::FromJsonString(configStr);
        } else {
            LightRayLog::Log("Cannot load editor configuration. Creating new one.");
            settings = CreateDefaultConfig();
            configCreated = true;
        }

        s_settings = std::make_unique<ConfigurationSettings>(settings);
        if (configCreated) {
            SaveEditorConfigurationSettings();
        }

        return s_settings.get();
    }

    ConfigurationSettings ConfigurationSettingsUtils::CreateDefaultConfig() {
        ConfigurationSettings settings;
        return settings;
    }

    void ConfigurationSettingsUtils::SaveEditorConfigurationSettings() {
        std::string configStr = JsonLibrary::JsonLibrary::ToJson(*s_settings);
        if(!FileUtils::TrySaveFile(k_configFileName, configStr)) {
            LightRayLog::LogError("Cannot save editor configuration!");
        }
    }

    ConfigurationSettings *ConfigurationSettingsUtils::GetSettings() {
        return s_settings.get();
    }
}