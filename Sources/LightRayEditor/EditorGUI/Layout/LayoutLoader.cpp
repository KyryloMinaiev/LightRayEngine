//
// Created by MrFlyingChip on 21.11.2024.
//

#include "LayoutLoader.h"
#include "EditorConfigurationSettings/EditorConfigurationSettings.h"
#include <filesystem>
#include "LightRayLog.h"

namespace LightRayEngine {
    std::vector<std::string> LayoutLoader::LoadAvailableLayouts(EditorConfigurationSettings *settings) {
        auto result = LoadDefaultLayouts();
        std::vector<std::string> savedLayouts = settings->GetValue("savedLayouts", std::vector<std::string>());
        result.insert(result.end(), savedLayouts.begin(), savedLayouts.end());

        return result;
    }

    std::vector<std::string> LayoutLoader::LoadDefaultLayouts() {
        auto applicationPath = std::filesystem::current_path();
        std::string defaultLayoutsFolder = applicationPath.string() + k_defaultLayoutsFolder;
        std::vector<std::string> result;
        if (!std::filesystem::exists(defaultLayoutsFolder)) {
            LightRayLog::LogError("Default Layouts folder doesn't exist!");
            return result;
        }

        for (const auto &entry: std::filesystem::directory_iterator(defaultLayoutsFolder)) {
            const auto &path = entry.path();
            if (path.extension().string() == k_layoutExtension) {
                result.push_back(path.string());
            }
        }

        return result;
    }
} // LightRayEngine