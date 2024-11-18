//
// Created by MrFlyingChip on 18.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_SCENEMANAGER_H
#define LIGHTRAYAPPLICATION_SCENEMANAGER_H

#include "SceneData.h"

namespace LightRayEngine {
    class SceneManager {
    public:
        static void LoadScene(SceneData& sceneData);
        static void UnloadScene(SceneData& sceneData);
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_SCENEMANAGER_H
