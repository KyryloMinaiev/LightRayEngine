//
// Created by MrFlyingChip on 11.11.2024.
//

#include "WorldsSystem.h"
#include "World.h"

namespace LightRayEngine {
    WorldsSystem *WorldsSystem::s_instance;

    WorldsSystem::WorldsSystem() {
        s_instance = this;
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
        return nullptr;
    }

    void WorldsSystem::InjectWorld(World *world) {
        if (!s_instance) {
            return;
        }

        s_instance->m_injectedWorlds.push_back(world);
    }


} // LightRayEngine