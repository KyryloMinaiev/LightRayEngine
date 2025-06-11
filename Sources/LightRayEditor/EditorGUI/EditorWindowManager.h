#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "EditorWindow.h"
#include "EditorGUI/EditorWindows/IEngineDefaultEditorWindow.h"

namespace LightRayEngine
{
    class EditorConfigurationSettings;

    class EditorWindowManager
    {
        public:
            EditorWindowManager();
            ~EditorWindowManager();
            void CloseAllWindows();

            template<typename T>
            static EditorWindow *CreateBasicEditorWindow();

            template<typename T>
            static T *CreateEditorWindow();

            template<typename T>
            static T *CreateEditorWindow(const std::string &title);

            template<typename T>
            static T *CreateEditorWindow(const std::string &title, WindowAnchor anchor);
            void CloseWindow(EditorWindow *window);
            void DrawEditorWindows();
            void FinalizeWindowDrawing();
            static void ConstructDefaultEditorWindows();
            [[nodiscard]] std::vector<EditorWindow *> GetOpenedWindows() const;
        private:
            static EditorWindowManager *s_instance;

            void DrawEditorWindow(EditorWindow *window) const;
            void InitializeEditorWindow(EditorWindow *window) const;
            template<typename T>
            T *CreateEditorWindowInternal(const std::string &title, WindowAnchor anchor);

            struct WindowInternalData
            {
                std::unique_ptr<EditorWindow> windowPtr;
                bool isInitialized = false;

                WindowInternalData(std::unique_ptr<EditorWindow> &&windowPtr) : windowPtr(std::move(windowPtr))
                {}

                WindowInternalData(const WindowInternalData &other) = delete;
                WindowInternalData &operator=(const WindowInternalData &other) = delete;

                WindowInternalData(WindowInternalData &&other) : windowPtr(std::move(other.windowPtr)),
                                                                 isInitialized(other.isInitialized)
                {
                    other.windowPtr = nullptr;
                }

                WindowInternalData &operator=(WindowInternalData &&other)
                {
                    windowPtr = std::move(other.windowPtr);
                    isInitialized = other.isInitialized;
                    other.windowPtr = nullptr;
                    return *this;
                }
            };

            std::vector<WindowInternalData> m_editorWindows;
            std::vector<WindowInternalData> m_markedForDeleteWindows;

            static constexpr int k_defaultWindowWidth = 400;
            static constexpr int k_defaultWindowHeight = 200;
    };

    template<typename T>
    EditorWindow *EditorWindowManager::CreateBasicEditorWindow()
    {
        static_assert(std::is_base_of<IEngineDefaultEditorWindow, T>::value,
                      "EditorWindowManager::CreateBasicEditorWindow works only with IEngineDefaultEditorWindow!");
        T *window = CreateEditorWindow<T>();
        auto *defaultWindow = dynamic_cast<IEngineDefaultEditorWindow *>(window);
        window->title = defaultWindow->GetDefaultWindowName();
        return window;
    }

    template<typename T>
    T *EditorWindowManager::CreateEditorWindow()
    {
        return CreateEditorWindow<T>("Editor Window");
    }

    template<typename T>
    T *EditorWindowManager::CreateEditorWindow(const std::string &title)
    {
        return CreateEditorWindow<T>(title, WindowAnchor::TopLeft);
    }

    template<typename T>
    T *EditorWindowManager::CreateEditorWindow(const std::string &title, WindowAnchor anchor)
    {
        return s_instance->CreateEditorWindowInternal<T>(title, anchor);
    }

    template<typename T>
    T *EditorWindowManager::CreateEditorWindowInternal(const std::string &title, LightRayEngine::WindowAnchor anchor)
    {
        static_assert(std::is_base_of<EditorWindow, T>::value,
                      "EditorWindowManager::CreateEditorWindow works only with EditorWindows!");
        assert(s_instance != nullptr);

        std::unique_ptr<T> windowPtr = std::make_unique<T>(this);
        EditorWindow *editorWindow = windowPtr.get();
        m_editorWindows.emplace_back(std::move(windowPtr));
        editorWindow->title = title;
        editorWindow->width = k_defaultWindowWidth;
        editorWindow->height = k_defaultWindowHeight;
        editorWindow->OnCreate();
        return dynamic_cast<T *>(editorWindow);
    }
}
