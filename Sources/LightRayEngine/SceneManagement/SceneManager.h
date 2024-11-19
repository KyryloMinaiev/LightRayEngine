//
// Created by MrFlyingChip on 18.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_SCENEMANAGER_H
#define LIGHTRAYAPPLICATION_SCENEMANAGER_H

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
        static void UnloadScene(SceneData& sceneData);

        static Scene* GetActiveScene();
        static std::vector<Scene*> GetAdditiveScenes();
    private:
        Scene* m_mainScene{};
        std::vector<Scene*> m_additiveScenes;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_SCENEMANAGER_H
