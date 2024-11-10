#pragma once

#include <string>
#include "JsonLibrary.h"

namespace LightRayEngine {
    class EditorWindow;

    class EditorWindowLayoutData : JsonLibrary::JsonSerialized {
    public:
        EditorWindowLayoutData() = default;

        EditorWindowLayoutData(const EditorWindow *editorWindow);

        std::string className;
        std::string title;
        float width = 0;
        float height = 0;
        int positionX = 0;
        int positionY = 0;
        bool isDocked;
        int dockId;
        bool isFocused;

        void SetupEditorWindow(EditorWindow *editorWindow) const;

        void FromJson(JsonLibrary::JsonObject &jsonObject) override;

        void ToJson(JsonLibrary::JsonObject &jsonObject) const override;
    };
}