//
// Created by MrFlyingChip on 18.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_SCENE_H
#define LIGHTRAYAPPLICATION_SCENE_H

#include <string>
#include <vector>
#include "World/Entity.h"
#include "SceneData.h"

namespace LightRayEngine {
    struct Scene {
        SceneData sceneData;
        std::vector<Entity*> sceneEntities;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_SCENE_H
