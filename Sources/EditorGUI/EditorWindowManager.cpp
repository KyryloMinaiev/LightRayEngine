#include "EditorWindowManager.h"

#include <imgui.h>
#include <LightRayLog.h>

#include "../Core/EditorConfigurationSettings/EditorConfigurationSettings.h"
#include "EditorWindows/AvailableWindows.h"
#include "EditorWindowLayoutData.h"

namespace LightRayEngine {
    EditorWindowManager *EditorWindowManager::s_instance;

    EditorWindowManager::EditorWindowManager() {
        s_instance = this;
    }

    EditorWindowManager::~EditorWindowManager() = default;

    void EditorWindowManager::DrawEditorWindows() const {
        for (auto &editorWindow: m_editorWindows) {
            EditorWindow *windowPtr = editorWindow.get();
            DrawEditorWindow(windowPtr);
        }
    }

    void EditorWindowManager::LoadLayout(EditorConfigurationSettings* editorConfigurationSettings) {
        std::vector<EditorWindowLayoutData> openedWindows;
        editorConfigurationSettings->GetValue("openedWindows", std::vector<JsonLibrary::JsonObject>()).DecodeArray(openedWindows);

        for (const auto &openedWindow: openedWindows) {
            if (availableWindows.find(openedWindow.className) != availableWindows.cend()) {
                auto window = availableWindows[openedWindow.className](openedWindow.title);
                openedWindow.SetupEditorWindow(window);
            }
        }
    }

    void EditorWindowManager::SaveLayout(EditorConfigurationSettings* editorConfigurationSettings) const {
        std::vector<EditorWindowLayoutData> openedWindows;
        for (const auto &window: m_editorWindows) {
            EditorWindow *ptr = window.get();
            openedWindows.emplace_back(ptr);
        }

        editorConfigurationSettings->GetField("openedWindows").EncodeArray(openedWindows);
    }

    void EditorWindowManager::DrawEditorWindow(EditorWindow *window) const {
        ImGui::SetNextWindowSize(ImVec2(window->width, window->height), ImGuiCond_FirstUseEver);
        int windowFlags = ImGuiWindowFlags_NoCollapse;
        if(!window->canBeMoved) {
            windowFlags |= ImGuiWindowFlags_NoMove;
        }

        if(!window->resizable) {
            windowFlags |= ImGuiWindowFlags_NoResize;
        }

        if(!window->canBeDocked) {
            windowFlags |= ImGuiWindowFlags_NoDocking;
        }

        if (!ImGui::Begin(window->title.c_str(), nullptr, windowFlags)) {
            ImGui::End();
            return;
        }

        ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;
        auto isDocked = ImGui::IsWindowDocked();
        auto isFocused = ImGui::IsWindowFocused();
        auto dockID = ImGui::GetWindowDockID();
        auto windowSize = ImGui::GetWindowSize();

        window->width = windowSize.x;
        window->height = windowSize.y;
        window->isFocused = isFocused;
        window->isDocked = isDocked;
        window->dockId = dockID;

        window->OnGui();
        ImGui::End();
    }

    void EditorWindowManager::CloseWindow(EditorWindow *window) {
        s_instance->CloseWindowInternal(window);
    }

    void EditorWindowManager::CloseWindowInternal(EditorWindow *window) {
        auto it = m_editorWindows.begin();

        for (;it < m_editorWindows.end(); it++) {
            if(window == it->get()) {
                m_editorWindows.erase(it);
                break;
            }
        }
    }
}
