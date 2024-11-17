//
// Created by MrFlyingChip on 11.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_ENTITYCOMPONENTCONTAINER_H
#define LIGHTRAYAPPLICATION_ENTITYCOMPONENTCONTAINER_H

#include <vector>
#include <memory>
#include <map>
#include "Entity.h"
#include "Component.h"
#include "Object/ObjectManager.h"

namespace LightRayEngine {
    class EntityComponentContainer {
    public:
        EntityComponentContainer() = default;

        ~EntityComponentContainer();

        template<class T>
        T *AddComponent();

        template<class T>
        T *GetComponent();

        template<class T>
        bool HasComponent();

        template<class T>
        void RemoveComponent();

        void Clean();

    private:
        static void DeleteComponent(Component* componentPtr);

        std::vector<Component *> m_components;
        std::map<size_t, Component *> m_typeComponentsMap;
        Entity *m_entity;

        //those vectors are used to track state changed
        std::vector<Component *> m_addedComponents;
        std::vector<Component *> m_deletedComponents;
        std::vector<Component *> m_enabledComponents;
        std::vector<Component *> m_disabledComponents;
    };

    template<class T>
    void EntityComponentContainer::RemoveComponent() {
        auto componentPtr = GetComponent<T>();
        if (!componentPtr) {
            return;
        }

        size_t typeHash = TypeManager::GetTypeHash<T>();
        m_typeComponentsMap.erase(typeHash);
        m_components.erase(componentPtr);
        DeleteComponent(componentPtr);
    }

    template<class T>
    bool EntityComponentContainer::HasComponent() {
        size_t typeHash = TypeManager::GetTypeHash<T>();
        return m_typeComponentsMap.contains(typeHash);
    }

    template<class T>
    T *EntityComponentContainer::AddComponent() {
        T *componentPtr = GetComponent<T>();
        if (componentPtr) {
            return componentPtr;
        }

        componentPtr = ObjectManager::CreateObjectOfType<T>();
        m_components.push_back(componentPtr);
        size_t typeHash = TypeManager::GetTypeHash<T>();
        m_typeComponentsMap[typeHash] = componentPtr;

        return componentPtr;
    }

    template<class T>
    T *EntityComponentContainer::GetComponent() {
        size_t typeHash = TypeManager::GetTypeHash<T>();
        if (m_typeComponentsMap.contains(typeHash)) {
            return m_typeComponentsMap[typeHash];
        }

        return nullptr;
    }
} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_ENTITYCOMPONENTCONTAINER_H
