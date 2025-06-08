//
// Created by MrFlyingChip on 08.06.2025.
//

#include "AssetDatabase.h"

namespace LightRayEngine {

    AssetDatabase::AssetDatabase() = default;
    AssetDatabase::~AssetDatabase() = default;

    void AssetDatabase::LoadDatabase(const std::string &projectPath, std::function<void(std::string)> loadDatabaseStepCallback) {

    }

    std::vector<std::string> AssetDatabase::AnalyzeDatabase(const std::string &projectPath) {
        return std::vector<std::string>();
    }

    void AssetDatabase::ConstructSerializedDatabase(const std::string &projectPath) {

    }

    void AssetDatabase::StartAssetEditingInternal() {

    }

    void AssetDatabase::StopAssetEditingInternal() {

    }

    void AssetDatabase::ImportAssetInternal(const std::string &assetPath) {

    }

    void AssetDatabase::StartAssetEditing() {
        s_instance->StartAssetEditingInternal();
    }

    void AssetDatabase::StopAssetEditing() {
        s_instance->StopAssetEditingInternal();
    }

    void AssetDatabase::ImportAsset(const std::string &assetPath) {
        s_instance->ImportAssetInternal(assetPath);
    }
}
