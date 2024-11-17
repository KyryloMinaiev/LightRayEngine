//
// Created by MrFlyingChip on 11.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_WORLDSSYSTEM_H
#define LIGHTRAYAPPLICATION_WORLDSSYSTEM_H

#include <string>
#include <memory>
#include <vector>

namespace LightRayEngine {
    class World;

    class WorldsSystem {
    public:
        WorldsSystem();
        ~WorldsSystem() = default;
        void UpdateWorlds();

        static World* CreateWorld(const std::string& name, bool editorWorld = false);
        static void InjectWorld(World* world);
        static void DestroyWorld(World* world);
    private:
        static WorldsSystem* s_instance;
        std::vector<std::unique_ptr<World>> m_worlds;
        std::vector<World*> m_injectedWorlds;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_WORLDSSYSTEM_H
