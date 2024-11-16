//
// Created by MrFlyingChip on 10.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_ENTITY_H
#define LIGHTRAYAPPLICATION_ENTITY_H

#include <string>

namespace LightRayEngine {
    class Entity {
    public:
        int id;
        bool enabled;
        std::string name;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_ENTITY_H
