#include "SceneView.h"

#include "../EditorWindowManager.h"

namespace LightRayEngine {
    SceneView::~SceneView() = default;

    SceneView::SceneView() = default;

    void SceneView::Create() {
        auto window = EditorWindowManager::CreateEditorWindow<SceneView>("Scene View");
        window->width = 500;
        window->height = 300;
    }

    void SceneView::OnCreate() {
        // m_sceneViewCamera = Camera::Create();
        // m_sceneViewCameraObject = m_sceneViewCamera->componentGameObject;
        // m_sceneViewCameraTransform = m_sceneViewCamera->componentTransform;
        //
        // m_sceneViewCamera->clearTag = CameraClearTag::ClearColor;
        // m_sceneViewCamera->clearColor = glm::vec4(0.333f, 0.745f, 1.0f, 0.7f);
        //
        // m_sceneViewCameraTransform->SetPosition(glm::vec3(0.0f, 0.0f, -8.0f));
        // m_lastMousePosition = InputManager::GetMousePosition();
    }

    void SceneView::OnGui() {
        // //This should be changed
        // auto windowSize = Application::GetWindowSize();
        // float aspect = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
        // m_sceneViewCamera->SetAspect(aspect);
        //
        // RotateCamera();
        // //MoveCamera(deltaTime);
    }

    void SceneView::RotateCamera() {
//        auto mousePosition = InputManager::GetMousePosition();
//        if (!m_isMoving && InputManager::IsKeyPressed(1)) {
//            m_isRotating = true;
//            auto distance = glm::abs(glm::distance(mousePosition, m_lastMousePosition));
//            if (distance > 0.0001f) {
//                float deltaX = glm::radians(m_lastMousePosition.x - mousePosition.x) * k_cameraRotateSpeed;
//                float deltaY = glm::radians(mousePosition.y - m_lastMousePosition.y) * k_cameraRotateSpeed;
//
//                auto rotation = m_sceneViewCameraTransform->GetRotation();
//
//                glm::quat quat1 = glm::rotate(rotation, deltaY, rotation * glm::vec3(1, 0, 0));
//                glm::quat quat2 = glm::rotate(quat1, deltaX, glm::vec3(0, 1, 0));
//                m_sceneViewCameraTransform->SetRotation(quat2);
//            }
//        } else {
//            m_isRotating = false;
//        }
//
//        m_lastMousePosition = mousePosition;
    }

    void SceneView::MoveCamera(float deltaTime) {
//        if (m_isRotating) {
//            return;
//        }
//
//        glm::vec3 cameraMovement = glm::vec3();
//        auto rightVector = m_sceneViewCameraTransform->GetRight();
//        m_isMoving =
//                InputManager::IsKeyPressed(263) || InputManager::IsKeyPressed(262) || InputManager::IsKeyPressed(265)
//                || InputManager::IsKeyPressed(264);
//        if (InputManager::IsKeyPressed(263)) {
//            cameraMovement += rightVector * deltaTime * k_cameraMoveSpeed;
//        } else if (InputManager::IsKeyPressed(262)) {
//            cameraMovement -= rightVector * deltaTime * k_cameraMoveSpeed;
//        }
//
//        auto forwardVector = m_sceneViewCameraTransform->GetForward();
//        if (InputManager::IsKeyPressed(265)) {
//            cameraMovement += forwardVector * deltaTime * k_cameraMoveSpeed;
//        } else if (InputManager::IsKeyPressed(264)) {
//            cameraMovement -= forwardVector * deltaTime * k_cameraMoveSpeed;
//        }
//
//        m_sceneViewCameraTransform->Translate(cameraMovement);
    }
}
