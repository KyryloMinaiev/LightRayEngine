//
// Created by MrFlyingChip on 21.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_EDITORLAYOUT_H
#define LIGHTRAYAPPLICATION_EDITORLAYOUT_H

#include "JsonLibrary.h"
#include "DockingData.h"
#include <vector>
#include <imgui.h>
#include <imgui_internal.h>

namespace LightRayEngine {
    class EditorWindow;

    class WindowData : public JsonLibrary::JsonSerialized {
    public:
        WindowData() = default;
        explicit WindowData(EditorWindow* editorWindow);
        ~WindowData() override;

        void SetupWindow(EditorWindow* editorWindow) const;

        void FromJson(JsonLibrary::JsonObject &jsonObject) override;
        void ToJson(JsonLibrary::JsonObject &jsonObject) override;

        std::string className;
        std::string title;
        float width = 0;
        float height = 0;
        int positionX = 0;
        int positionY = 0;
        bool isDocked = false;
        int dockId = 0;
        bool isFocused = false;
    };

    class EditorLayout : public JsonLibrary::JsonSerialized{
    public:
        EditorLayout() = default;
        explicit EditorLayout(ImGuiID dockSpaceId);
        ~EditorLayout() override;

        void AddWindow(EditorWindow* window);

        void FromJson(JsonLibrary::JsonObject &jsonObject) override;
        void ToJson(JsonLibrary::JsonObject &jsonObject) override;

        std::vector<WindowData> windows;
        DockingData dockingData;
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_EDITORLAYOUT_H
