//
// Created by MrFlyingChip on 08.09.2024.
//

#ifndef LIGHTRAYENGINE_ASSETDATABASE_H
#define LIGHTRAYENGINE_ASSETDATABASE_H

namespace LightRayEngine {

    class AssetDatabase {
    public:
        AssetDatabase();
    private:
        static AssetDatabase* s_instance;
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_ASSETDATABASE_H
