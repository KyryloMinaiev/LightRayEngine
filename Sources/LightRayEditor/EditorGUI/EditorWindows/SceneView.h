#pragma once
#include "../EditorWindow.h"
#include <glm.hpp>

namespace LightRayEngine {
    class Camera;

    class Transform;

    class GameObject;

    class SceneView : public EditorWindow {
    public:
        ~SceneView() override;

        SceneView();

        static void Create();

        void OnCreate() override;

        void OnGui() override;

    private:
        static constexpr float k_cameraMoveSpeed = 3.0f;
        static constexpr float k_cameraRotateSpeed = 0.08f;

        void RotateCamera();

        void MoveCamera(float deltaTime);

        GameObject *m_sceneViewCameraObject;
        Transform *m_sceneViewCameraTransform;
        Camera *m_sceneViewCamera;

        glm::vec2 m_lastMousePosition;
        bool m_isMoving = false;
        bool m_isRotating = false;
    };
}
