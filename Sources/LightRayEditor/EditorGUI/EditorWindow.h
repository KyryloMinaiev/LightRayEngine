#pragma once

#include <string>
#include <limits>

namespace LightRayEngine
{
    class EditorWindowManager;

    enum class WindowAnchor
    {
        Center,
        TopCenter,
        BottomCenter,
        CenterLeft,
        CenterRight,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    class EditorWindow
    {
        public:
            EditorWindow(EditorWindowManager* editorWindowManager);
            virtual ~EditorWindow() = default;

            virtual void OnCreate();

            virtual void OnGui() = 0;

            float width = 0;
            float height = 0;

            float minWidth = 0;
            float minHeight = 0;
            float maxWidth = std::numeric_limits<float>::max();
            float maxHeight = std::numeric_limits<float>::max();

            int positionX = 0;
            int positionY = 0;

            bool canBeMoved = true;
            bool canBeDocked = true;
            bool resizable = true;
            bool isDocked;
            unsigned int dockId;
            bool isFocused;
            bool saveWindowData = true;

            std::string title;

            void Close();
        private:
            EditorWindowManager* m_editorWindowManager;
    };
}
