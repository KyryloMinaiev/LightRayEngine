//
// Created by MrFlyingChip on 11.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_ENTITYMANAGER_H
#define LIGHTRAYAPPLICATION_ENTITYMANAGER_H

#include <vector>
#include <map>
#include <stack>
#include <memory>
#include <string>
#include <cassert>
#include "Entity.h"
#include "EntityComponentContainer.h"

namespace LightRayEngine {
    class World;
    class Component;

    class EntityManager {
    public:
        explicit EntityManager(World* world);
        ~EntityManager();

        template<class T>
        T* AddComponent(Entity* entity);
        template<class T>
        void RemoveComponent(Entity* entity);
        template<class T>
        bool HasComponent(Entity* entity);
        template<class T>
        T* GetComponent(Entity* entity);

        Entity* CreateEntity();
        Entity* CreateEntity(std::string& name);

        [[nodiscard]] const World* GetGameWorld() const;
    private:
        struct EntityContainerData{
            EntityContainerData();
            EntityContainerData(Entity *entity, EntityComponentContainer *container);

            Entity* entity{};
            EntityComponentContainer* container{};
        };

        static constexpr int k_startEntityCount = 128;

        void EnsureAvailableEntities(int entitiesCount);
        Entity* CreateEntityInternal();
        EntityComponentContainer* GetEntityContainer(Entity* entity);

        World* m_world;

        std::vector<std::unique_ptr<Entity>> m_createdEntities;
        std::vector<std::unique_ptr<EntityComponentContainer>> m_entityComponentContainers;
        std::stack<EntityContainerData> m_availableEntities;

        std::map<int, EntityComponentContainer*> m_entityToContainersMap;
    };

    template<class T>
    T *EntityManager::AddComponent(Entity *entity) {
        static_assert(std::is_base_of<Component, T>());
        auto container = GetEntityContainer(entity);

        return container->AddComponent<T>();
    }

    template<class T>
    void EntityManager::RemoveComponent(Entity *entity) {
        static_assert(std::is_base_of<Component, T>());
        auto container = GetEntityContainer(entity);

        return container->RemoveComponent<T>();
    }

    template<class T>
    bool EntityManager::HasComponent(Entity *entity) {
        static_assert(std::is_base_of<Component, T>());
        auto container = GetEntityContainer(entity);

        return container->HasComponent<T>();
    }

    template<class T>
    T *EntityManager::GetComponent(Entity *entity) {
        static_assert(std::is_base_of<Component, T>());
        auto container = GetEntityContainer(entity);

        return container->GetComponent<T>();
    }
} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_ENTITYMANAGER_H
