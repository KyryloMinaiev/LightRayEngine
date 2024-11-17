//
// Created by MrFlyingChip on 12.11.2024.
//

#include "LightRayObject.h"

namespace LightRayEngine {
    LightRayObject::LightRayObject(int objectID) : m_objectID(objectID) {

    }

    int LightRayObject::GetID() const {
        return m_objectID;
    }
} // LightRayEngine