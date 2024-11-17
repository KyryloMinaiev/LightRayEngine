//
// Created by MrFlyingChip on 11.11.2024.
//

#include "EntityManager.h"
#include "EntityComponentContainer.h"
#include "World.h"
#include "Component.h"
#include "Entity.h"

namespace LightRayEngine {
    EntityManager::EntityManager(World *world) : m_world(world) {
        EnsureAvailableEntities(k_startEntityCount);
    }

    EntityManager::~EntityManager() = default;

    const World *EntityManager::GetGameWorld() const {
        return m_world;
    }

    Entity *EntityManager::CreateEntity() {
        Entity *entity = CreateEntityInternal();
        if (entity) {
            entity->name = "Entity - " + std::to_string(entity->id);
        }

        return entity;
    }

    Entity *EntityManager::CreateEntity(std::string &name) {
        Entity *entity = CreateEntityInternal();
        if (entity) {
            entity->name = name;
        }

        return entity;
    }

    Entity *EntityManager::CreateEntityInternal() {
        if(m_availableEntities.empty()){
            EnsureAvailableEntities(m_availableEntities.size() * 2);
        }

        auto entityData=  m_availableEntities.top();
        m_availableEntities.pop();

        m_entityToContainersMap[entityData.entity->id] = entityData.container;

        return entityData.entity;
    }

    EntityComponentContainer *EntityManager::GetEntityContainer(Entity *entity) {
        assert(entity);
        int entityID = entity->id;
        assert(m_entityToContainersMap.contains(entityID));

        auto container = m_entityToContainersMap[entityID];
        assert(container);

        return container;
    }

    void EntityManager::EnsureAvailableEntities(int entitiesCount) {
        if(entitiesCount <= m_availableEntities.size()){
            return;
        }

        for (int i = m_availableEntities.size(); i < entitiesCount; ++i) {
            auto entity = std::make_unique<Entity>();
            auto container = std::make_unique<EntityComponentContainer>();

            m_createdEntities.push_back(std::move(entity));
            m_entityComponentContainers.push_back(std::move(container));
            m_availableEntities.emplace(entity.get(), container.get());
        }
    }

    EntityManager::EntityContainerData::EntityContainerData(Entity *entity, EntityComponentContainer *container)
            : entity(entity), container(container) {}

    EntityManager::EntityContainerData::EntityContainerData() = default;
} // LightRayEngine