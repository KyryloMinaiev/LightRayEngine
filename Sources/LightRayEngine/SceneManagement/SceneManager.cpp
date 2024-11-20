//
// Created by MrFlyingChip on 18.11.2024.
//

#include <algorithm>
#include "SceneManager.h"
#include "Scene.h"
#include "SerializedScene.h"
#include "World/WorldsSystem.h"
#include "World/World.h"
#include "World/EntityManager.h"

namespace LightRayEngine {
    void SceneManager::LoadScene(SceneData &sceneData, SceneLoadType sceneLoadType) {
        UnloadScene(GetActiveScene());

        World *gameplayWorld = WorldsSystem::GetMainWorld();
        EntityManager *entityManager = gameplayWorld->GetEntityManager();

        //Get Serialized scene either from AssetDatabase or from bundles
        auto *serializedScene = ObjectManager::CreateObjectOfType<SerializedScene>();

        ObjectManager::DeleteObject(serializedScene);
    }

    void SceneManager::UnloadScene(Scene *scene) {
        if (!scene || !IsSceneLoaded(scene)) {
            return;
        }

        World *gameplayWorld = WorldsSystem::GetMainWorld();
        EntityManager *entityManager = gameplayWorld->GetEntityManager();
        for (auto entity: scene->sceneEntities) {
            entityManager->DeleteEntity(entity);
        }

        if (scene == GetActiveScene()) {
            s_instance->m_mainScene = nullptr;
            //We need to unload all additive scenes with the main one
            for (auto additiveScenePointer :s_instance->m_additiveScenesPointers) {
                UnloadScene(additiveScenePointer);
            }

            return;
        }

        auto additiveScenes = GetAdditiveScenes();
        const auto start = additiveScenes.cbegin();
        const auto end = additiveScenes.cend();
        auto sceneIt = std::find(start, end, scene);
        if (sceneIt == end) {
            return;
        }

        auto index = std::distance(start, sceneIt);
        s_instance->m_additiveScenesPointers.erase(sceneIt);
        s_instance->m_additiveScenes.erase(s_instance->m_additiveScenes.cbegin() + index);
    }

    Scene *SceneManager::GetActiveScene() {
        return s_instance->m_mainScene.get();
    }

    std::vector<Scene *> SceneManager::GetAdditiveScenes() {
        return s_instance->m_additiveScenesPointers;
    }

    SceneManager::SceneManager() : SingletonManager<SceneManager>() {

    }

    SceneManager::~SceneManager() {

    }

    bool SceneManager::IsSceneLoaded(Scene *scene) {
        if (!scene) {
            return false;
        }

        if (scene == GetActiveScene()) {
            return true;
        }

        auto additiveScenes = GetAdditiveScenes();
        const auto start = additiveScenes.cbegin();
        const auto end = additiveScenes.cend();
        if (std::find(start, end, scene) != end) {
            return true;
        }

        return false;
    }
} // LightRayEngine