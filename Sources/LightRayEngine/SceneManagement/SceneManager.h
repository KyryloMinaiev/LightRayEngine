//
// Created by MrFlyingChip on 18.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_SCENEMANAGER_H
#define LIGHTRAYAPPLICATION_SCENEMANAGER_H

#include <memory>
#include "SceneData.h"
#include "Generic/SingletonManager.h"
#include <vector>

namespace LightRayEngine {
    class Scene;

    enum class SceneLoadType{
        Main,
        Additive
    };

    class SceneManager : public SingletonManager<SceneManager>{
    public:
        SceneManager();
        ~SceneManager() override;

        static void LoadScene(SceneData& sceneData, SceneLoadType sceneLoadType);
        static void UnloadScene(Scene* scene);

        static Scene* GetActiveScene();
        static std::vector<Scene*> GetAdditiveScenes();
        static bool IsSceneLoaded(Scene* scene);

    private:
        std::unique_ptr<Scene> m_mainScene;
        std::vector<std::unique_ptr<Scene>> m_additiveScenes;
        std::vector<Scene*> m_additiveScenesPointers;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_SCENEMANAGER_H
