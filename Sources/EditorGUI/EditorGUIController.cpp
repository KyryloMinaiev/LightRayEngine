//
// Created by Kirill Minaev on 13.07.2024.
//

#include "EditorGUIController.h"
#include <LightRayLog.h>

namespace LightRayEngine {

    bool EditorGUIController::Initialize(GLFWwindow *window) {
        try {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

            ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
            ImGui_ImplOpenGL3_Init();
            LightRayLog::Log("Successfully initialized ImGUI.");
            return true;
        } catch (...){
            LightRayLog::LogException("Unknown exception during GUI initialization!");
        }

        return false;
    }

    void EditorGUIController::StartFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    }

    void EditorGUIController::Render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    EditorGUIController::~EditorGUIController() {

    }

    EditorGUIController::EditorGUIController(EditorConfigurationSettings *editorSettings) : EditorLoopSystem(
            editorSettings) {}
}
