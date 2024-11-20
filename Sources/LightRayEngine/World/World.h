//
// Created by MrFlyingChip on 10.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_WORLD_H
#define LIGHTRAYAPPLICATION_WORLD_H

#include <string>
#include <memory>

namespace LightRayEngine {
    class EntityManager;

    class World {
    public:
        World(const std::string& name, bool editorWorld);
        ~World();

        void Update();
        [[nodiscard]] EntityManager* GetEntityManager() const;

    private:
        std::string m_name;
        std::unique_ptr<EntityManager> m_entityManager;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_WORLD_H
