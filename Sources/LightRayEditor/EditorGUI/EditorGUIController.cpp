//
// Created by Kirill Minaev on 13.07.2024.
//

#include "EditorGUIController.h"
#include <LightRayLog.h>
#include "MenuToolbar/MenuToolbar.h"
#include "EditorWindowManager.h"
#include "Window/IWindow.h"
#include "Layout/LayoutManager.h"
#include "DockSpaceBuilder.h"

namespace LightRayEngine {

    bool EditorGUIController::Initialize(IWindow *window) {
        return InitializeImGUI(window) && InitializeMenuToolbar() &&
               InitializeLayoutManager();
    }

    void EditorGUIController::StartFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        m_dockSpaceBuilder->BuildDockSpace();
        m_menuToolbar->ShowToolbar();
        m_editorWindowManager->DrawEditorWindows();
    }

    void EditorGUIController::Render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    EditorGUIController::~EditorGUIController() = default;

    EditorGUIController::EditorGUIController() : EditorLoopSystem() {
        m_dockSpaceBuilder = std::make_unique<DockSpaceBuilder>();
        m_menuToolbar = std::make_unique<MenuToolbar>();
        m_editorWindowManager = std::make_unique<EditorWindowManager>();
        m_layoutManager = std::make_unique<LayoutManager>(m_dockSpaceBuilder.get(), m_editorWindowManager.get());
    }

    bool EditorGUIController::InitializeImGUI(IWindow *window) {
        try {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

            ImGui_ImplGlfw_InitForOpenGL(window->GetGLFWWindow(),
                                         true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
            ImGui_ImplOpenGL3_Init();
            LightRayLog::Log("Successfully initialized ImGUI.");
            return true;
        } catch (...) {
            LightRayLog::LogException("Unknown exception during GUI initialization!");
        }

        return false;
    }

    bool EditorGUIController::InitializeMenuToolbar() {
        try {
            m_menuToolbar->Initialize();
            LightRayLog::Log("Successfully initialized MenuToolbar.");
            return true;
        } catch (...) {
            LightRayLog::LogException("Unknown exception during MenuToolbar initialization!");
        }

        return false;
    }

    void EditorGUIController::OnLoopStop() {
        m_layoutManager->SaveCurrentLayout(configurationSettings);
    }

    bool EditorGUIController::InitializeLayoutManager() {
        try {
            m_layoutManager->LoadLayouts(configurationSettings);
            m_layoutManager->ApplyLayout(configurationSettings);
            LightRayLog::Log("Successfully loaded editor window manager.");
            return true;
        } catch (...) {
            LightRayLog::LogException("Unknown exception during loading editor window layout!");
        }

        return false;
    }
}
