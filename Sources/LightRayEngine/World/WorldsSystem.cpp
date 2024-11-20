//
// Created by MrFlyingChip on 11.11.2024.
//

#include "WorldsSystem.h"
#include "World.h"

namespace LightRayEngine {
    World* WorldsSystem::s_mainWorld;

    WorldsSystem::WorldsSystem() : SingletonManager<WorldsSystem>(){
        s_mainWorld = CreateWorld("Main World");
        InjectWorld(s_mainWorld);
    }

    void WorldsSystem::DestroyWorld(World *world) {

    }

    void WorldsSystem::UpdateWorlds() {
        for (auto world: m_injectedWorlds) {
            if (world) {
                world->Update();
            }
        }
    }

    World *WorldsSystem::CreateWorld(const std::string &name, bool editorWorld) {
        std::unique_ptr<World> world = std::make_unique<World>(name, editorWorld);
        World* worldPtr = world.get();
        s_instance->m_worlds.push_back(std::move(world));

        return worldPtr;
    }

    void WorldsSystem::InjectWorld(World *world) {
        if (!s_instance) {
            return;
        }

        s_instance->m_injectedWorlds.push_back(world);
    }

    World *WorldsSystem::GetMainWorld() {
        return s_mainWorld;
    }

    WorldsSystem::~WorldsSystem() = default;
} // LightRayEngine