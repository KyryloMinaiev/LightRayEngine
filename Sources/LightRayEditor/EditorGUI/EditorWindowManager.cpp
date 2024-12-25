#include "EditorWindowManager.h"

#include <imgui.h>
#include <LightRayLog.h>

#include "EditorConfigurationSettings/EditorConfigurationSettings.h"
#include "EditorWindows/AvailableWindows.h"
#include "EditorWindowLayoutData.h"

namespace LightRayEngine {
    EditorWindowManager *EditorWindowManager::s_instance;

    EditorWindowManager::EditorWindowManager() {
        s_instance = this;
    }

    EditorWindowManager::~EditorWindowManager() = default;

    void EditorWindowManager::DrawEditorWindows() {
        for (auto &editorWindowData: m_editorWindows) {
            EditorWindow *windowPtr = editorWindowData.windowPtr.get();

            if(editorWindowData.isInitialized){
                InitializeEditorWindow(windowPtr);
                editorWindowData.isInitialized = true;
            }

            DrawEditorWindow(windowPtr);
        }
    }

    void EditorWindowManager::DrawEditorWindow(EditorWindow *window) const {
        ImGui::SetNextWindowSize(ImVec2(window->width, window->height), ImGuiCond_FirstUseEver);

        if(window->dockId){
            ImGui::SetNextWindowDockID(window->dockId);
        }

        int windowFlags = ImGuiWindowFlags_NoCollapse;// | ImGuiWindowFlags_NoSavedSettings;
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
            if(window == it->windowPtr.get()) {
                m_editorWindows.erase(it);
                break;
            }
        }
    }

    std::vector<EditorWindow *> EditorWindowManager::GetOpenedWindows() const {
        std::vector<EditorWindow*> openedWindows;
        for(auto& windowData : m_editorWindows){
            openedWindows.push_back(windowData.windowPtr.get());
        }

        return openedWindows;
    }

    void EditorWindowManager::CloseAllWindows() {
        m_editorWindows.clear();
    }

    void EditorWindowManager::CreateWindows(const std::vector<WindowData>& windowDataList) {
        for (const WindowData& windowData : windowDataList) {
             EditorWindow* window = availableWindows[windowData.className](windowData.title);
             windowData.SetupWindow(window);
        }
    }

    void EditorWindowManager::InitializeEditorWindow(EditorWindow *window) const {

    }
}
