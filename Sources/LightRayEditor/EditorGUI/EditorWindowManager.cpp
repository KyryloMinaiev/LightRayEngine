#include "EditorWindowManager.h"

#include <imgui.h>
#include "EditorWindows/AvailableWindows.h"

namespace LightRayEngine
{
    EditorWindowManager *EditorWindowManager::s_instance;

    EditorWindowManager::EditorWindowManager()
    {
        s_instance = this;
    }

    EditorWindowManager::~EditorWindowManager() = default;

    void EditorWindowManager::DrawEditorWindows()
    {
        for (auto &editorWindowData: m_editorWindows)
        {
            EditorWindow *windowPtr = editorWindowData.windowPtr.get();

            if (editorWindowData.isInitialized)
            {
                InitializeEditorWindow(windowPtr);
                editorWindowData.isInitialized = true;
            }

            DrawEditorWindow(windowPtr);
        }
    }

    void EditorWindowManager::DrawEditorWindow(EditorWindow *window) const
    {
        int windowFlags = ImGuiWindowFlags_NoCollapse;// | ImGuiWindowFlags_NoSavedSettings;
        if (!window->canBeMoved)
        {
            windowFlags |= ImGuiWindowFlags_NoMove;
        }

        if (!window->resizable)
        {
            windowFlags |= ImGuiWindowFlags_NoResize;
        }

        if (!window->canBeDocked)
        {
            windowFlags |= ImGuiWindowFlags_NoDocking;
        }

        if (!ImGui::Begin(window->title.c_str(), nullptr, windowFlags))
        {
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

    void EditorWindowManager::CloseWindow(EditorWindow *window)
    {
        for (auto it = m_editorWindows.begin(); it < m_editorWindows.end(); it++)
        {
            if (window == it->windowPtr.get())
            {
                m_markedForDeleteWindows.emplace_back(std::move(*it.base()));
                m_editorWindows.erase(it);
                break;
            }
        }
    }

    std::vector<EditorWindow *> EditorWindowManager::GetOpenedWindows() const
    {
        std::vector<EditorWindow *> openedWindows;
        for (auto &windowData: m_editorWindows)
        {
            openedWindows.push_back(windowData.windowPtr.get());
        }

        return openedWindows;
    }

    void EditorWindowManager::CloseAllWindows()
    {
        m_editorWindows.clear();
    }

    void EditorWindowManager::InitializeEditorWindow(EditorWindow *window) const
    {

    }

    void EditorWindowManager::ConstructDefaultEditorWindows()
    {
        for (auto &window: availableWindows)
        {
            window.second();
        }
    }

    void EditorWindowManager::FinalizeWindowDrawing()
    {
        m_markedForDeleteWindows.clear();
    }
}
