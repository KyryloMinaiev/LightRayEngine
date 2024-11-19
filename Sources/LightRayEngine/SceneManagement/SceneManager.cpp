//
// Created by MrFlyingChip on 18.11.2024.
//

#include "SceneManager.h"

namespace LightRayEngine {
    void SceneManager::LoadScene(SceneData &sceneData, SceneLoadType sceneLoadType) {

    }

    void SceneManager::UnloadScene(SceneData &sceneData) {

    }

    Scene *SceneManager::GetActiveScene() {
        return nullptr;
    }

    std::vector<Scene *> SceneManager::GetAdditiveScenes() {
        return std::vector<Scene *>();
    }

    SceneManager::SceneManager() : SingletonManager<SceneManager>(){

    }

    SceneManager::~SceneManager() {

    }
} // LightRayEngine