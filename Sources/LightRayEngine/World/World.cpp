//
// Created by MrFlyingChip on 10.11.2024.
//

#include "World.h"
#include "LightRayLog.h"
#include "EntityManager.h"

namespace LightRayEngine {
    World::World(const std::string& name, bool editorWorld) {
        if (editorWorld) {
            m_name = "EditorWorld-" + name;
        }

        LightRayLog::Log("Creating world with name: {name}", m_name);
    }

    World::~World() {
        LightRayLog::Log("Shutdown world with name: {name}", m_name);
    }

    void World::Update() {

    }

    EntityManager *World::GetEntityManager() const {
        return m_entityManager.get();
    }
} // LightRayEngine