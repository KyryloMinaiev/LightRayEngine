//
// Created by MrFlyingChip on 21.11.2024.
//

#include "EditorLayout.h"
#include "../EditorWindow.h"

namespace LightRayEngine {
    EditorLayout::EditorLayout(ImGuiID dockSpaceId) : dockingData(dockSpaceId) {

    }

    EditorLayout::~EditorLayout() = default;

    void EditorLayout::FromJson(JsonLibrary::JsonObject &jsonObject) {
        jsonObject["dockingData"].DecodeObject(dockingData);
        jsonObject["windows"].DecodeArray(windows);
    }

    void EditorLayout::ToJson(JsonLibrary::JsonObject &jsonObject) {
        jsonObject["dockingData"].EncodeObject(dockingData);
        jsonObject["windows"].EncodeArray(windows);
    }

    void EditorLayout::AddWindow(EditorWindow *window) {
        if (!window) {
            return;
        }

        WindowData windowData(window);
        windows.push_back(windowData);
    }

    WindowData::WindowData(EditorWindow *window) {
        className = typeid(*window).name();
        width = window->width;
        title = window->title;
        height = window->height;
        positionX = window->positionX;
        positionY = window->positionY;
        isDocked = window->isDocked;
        dockId = window->dockId;
        isFocused = window->isFocused;
    }

    WindowData::~WindowData() = default;

    void WindowData::FromJson(JsonLibrary::JsonObject &jsonObject) {
        className = static_cast<std::string>(jsonObject["className"]);
        title = static_cast<std::string>(jsonObject["title"]);
        width = jsonObject["width"];
        height = jsonObject["height"];
        positionX = jsonObject["positionX"];
        positionY = jsonObject["positionY"];
        isDocked = jsonObject["isDocked"];
        dockId = jsonObject["dockId"];
        isFocused = jsonObject["isFocused"];
    }

    void WindowData::ToJson(JsonLibrary::JsonObject &jsonObject) {
        jsonObject["className"] = className;
        jsonObject["title"] = title;
        jsonObject["width"] = width;
        jsonObject["height"] = height;
        jsonObject["positionX"] = positionX;
        jsonObject["positionY"] = positionY;
        jsonObject["isDocked"] = isDocked;
        jsonObject["dockId"] = dockId;
        jsonObject["isFocused"] = isFocused;
    }

    void WindowData::SetupWindow(EditorWindow *editorWindow) const {
        editorWindow->width = width;
        editorWindow->height = height;
        editorWindow->positionX = positionX;
        editorWindow->positionY = positionY;
        editorWindow->isDocked = isDocked;
        editorWindow->dockId = dockId;
        editorWindow->isFocused = isFocused;
    }
} // LightRayEngine