//
// Created by MrFlyingChip on 08.06.2025.
//

#ifndef LIGHTRAYAPPLICATION_ASSETDATABASE_H
#define LIGHTRAYAPPLICATION_ASSETDATABASE_H

#include <string>
#include <functional>
#include <vector>
#include "Generic/SingletonManager.h"

namespace LightRayEngine{
    class AssetDatabase : SingletonManager<AssetDatabase>{
    public:
        AssetDatabase();
        ~AssetDatabase() override;

        void LoadDatabase(const std::string& projectPath, std::function<void(std::string)> loadDatabaseStepCallback);

        static void StartAssetEditing();
        static void StopAssetEditing();
        static void ImportAsset(const std::string& assetPath);
    private:
        std::vector<std::string> AnalyzeDatabase(const std::string& projectPath);
        void ConstructSerializedDatabase(const std::string& projectPath);

        void StartAssetEditingInternal();
        void StopAssetEditingInternal();

        void ImportAssetInternal(const std::string& assetPath);
    };
}

#endif //LIGHTRAYAPPLICATION_ASSETDATABASE_H
