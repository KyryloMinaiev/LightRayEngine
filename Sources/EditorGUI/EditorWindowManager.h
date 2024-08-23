#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "EditorWindow.h"

namespace LightRayEngine {
    class EditorConfigurationSettings;

    class EditorWindowManager {
    public:
        EditorWindowManager();
        ~EditorWindowManager();

        template<typename T>
        static EditorWindow *CreateBasicEditorWindow(std::string title);
        template<typename T>
        static T *CreateEditorWindow();
        template<typename T>
        static T *CreateEditorWindow(std::string title);

        static void CloseWindow(EditorWindow *window);

        void DrawEditorWindows() const;
        void LoadLayout(EditorConfigurationSettings *editorConfigurationSettings);
        void SaveLayout(EditorConfigurationSettings *editorConfigurationSettings) const;

    private:
        static EditorWindowManager *s_instance;

        void DrawEditorWindow(EditorWindow *window) const;
        void CloseWindowInternal(EditorWindow *window);

        std::vector<std::unique_ptr<EditorWindow>> m_editorWindows;

        static constexpr int k_defaultWindowWidth = 400;
        static constexpr int k_defaultWindowHeight = 200;
    };

    template<typename T>
    EditorWindow *EditorWindowManager::CreateBasicEditorWindow(std::string title) {
        return CreateEditorWindow<T>(title);
    }

    template<typename T>
    T *EditorWindowManager::CreateEditorWindow() {
        return CreateEditorWindow<T>("Editor Window");
    }

    template<typename T>
    T *EditorWindowManager::CreateEditorWindow(std::string title) {
        static_assert(std::is_base_of<EditorWindow, T>::value,
                      "EditorWindowManager::CreateEditorWindow works only with EditorWindows!");
        assert(s_instance != nullptr);

        size_t currentIndex = s_instance->m_editorWindows.size();
        s_instance->m_editorWindows.push_back(std::make_unique<T>());
        EditorWindow *editor_window = s_instance->m_editorWindows[currentIndex].get();
        editor_window->title = std::move(title);
        editor_window->width = k_defaultWindowWidth;
        editor_window->height = k_defaultWindowHeight;
        editor_window->OnCreate();
        return dynamic_cast<T *>(editor_window);
    }
}
