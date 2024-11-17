//
// Created by MrFlyingChip on 11.11.2024.
//

#include "EntityComponentContainer.h"

namespace LightRayEngine {
    EntityComponentContainer::~EntityComponentContainer() {
        Clean();
    }

    void EntityComponentContainer::Clean() {
        for (auto component: m_components) {
            DeleteComponent(component);
        }

        m_components.clear();
        m_typeComponentsMap.clear();
    }

    void EntityComponentContainer::DeleteComponent(Component *componentPtr) {
        ObjectManager::DeleteObject(componentPtr);
    }
} // LightRayEngine