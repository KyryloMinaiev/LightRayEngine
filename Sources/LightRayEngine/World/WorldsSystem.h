//
// Created by MrFlyingChip on 11.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_WORLDSSYSTEM_H
#define LIGHTRAYAPPLICATION_WORLDSSYSTEM_H

#include <string>
#include <memory>
#include <vector>
#include "Generic/SingletonManager.h"

namespace LightRayEngine {
    class World;

    class WorldsSystem : public SingletonManager<WorldsSystem>{
    public:
        WorldsSystem();
        ~WorldsSystem() override;
        void UpdateWorlds();

        static World* CreateWorld(const std::string& name, bool editorWorld = false);
        static void InjectWorld(World* world);
        static void DestroyWorld(World* world);
        static World* GetMainWorld();
    private:
        static World* s_mainWorld;
        std::vector<std::unique_ptr<World>> m_worlds;
        std::vector<World*> m_injectedWorlds;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_WORLDSSYSTEM_H
