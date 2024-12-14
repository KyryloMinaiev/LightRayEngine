//
// Created by Kirill Minaev on 25.06.2024.
//

#include "EditorConfigurationSettingsUtils.h"
#include "LightRayLog.h"
#include "FileUtils.h"

namespace LightRayEngine {
    std::unique_ptr<EditorConfigurationSettings> EditorConfigurationSettingsUtils::s_settings;

    EditorConfigurationSettings *EditorConfigurationSettingsUtils::LoadOrCreateDefaultEditorConfig() {
        std::string configStr;
        EditorConfigurationSettings settings;
        bool configCreated = false;
        if (FileUtils::TryLoadFile(k_configFileName, configStr)) {
            settings = JsonLibrary::JsonLibrary::FromJsonString(configStr);
        } else {
            LightRayLog::Log("Cannot load editor configuration. Creating new one.");
            settings = CreateDefaultConfig();
            configCreated = true;
        }

        s_settings = std::make_unique<EditorConfigurationSettings>(settings);
        if (configCreated) {
            SaveEditorConfigurationSettings();
        }

        return s_settings.get();
    }

    EditorConfigurationSettings EditorConfigurationSettingsUtils::CreateDefaultConfig() {
        EditorConfigurationSettings settings;
        return settings;
    }

    void EditorConfigurationSettingsUtils::SaveEditorConfigurationSettings() {
        std::string configStr = JsonLibrary::JsonLibrary::ToJson(*s_settings);
        if(!FileUtils::TrySaveFile(k_configFileName, configStr)) {
            LightRayLog::LogError("Cannot save editor configuration!");
        }
    }

    EditorConfigurationSettings *EditorConfigurationSettingsUtils::GetSettings() {
        return s_settings.get();
    }
}