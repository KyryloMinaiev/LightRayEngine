//
// Created by MrFlyingChip on 20.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_SERIALIZEDSCENE_H
#define LIGHTRAYAPPLICATION_SERIALIZEDSCENE_H

#include "Object/LightRayObject.h"

namespace LightRayEngine {
    class SerializedScene : public LightRayObject {
    public:
        explicit SerializedScene(int objectId);
        ~SerializedScene() override;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_SERIALIZEDSCENE_H
