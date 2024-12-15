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

    DockingData::DockingData(ImGuiID dockSpaceId) : dockSpaceNode(ImGui::DockBuilderGetNode(dockSpaceId)) {
    }

    DockingData::~DockingData() = default;

    void DockingData::FromJson(JsonLibrary::JsonObject &jsonObject) {
         jsonObject["dockSpaceNode"].DecodeObject(dockSpaceNode);
    }

    void DockingData::ToJson(JsonLibrary::JsonObject &jsonObject) {
        jsonObject["dockSpaceNode"].EncodeObject(dockSpaceNode);
    }

    DockingNode::DockingNode(ImGuiDockNode *node) {
        id = node->ID;
        auto position = node->Pos;
        relativeXPos = position.x;
        relativeYPos = position.y;
        ImVec2 size;
        if (node->IsDockSpace()) {
            size = node->Size;
        } else {
            size = node->SizeRef;
        }
        relativeXSize = size.x;
        relativeYSize = size.y;
        splitAxis = node->SplitAxis;
        isCentralNode = node->IsCentralNode();

        for (auto childNode: node->ChildNodes) {
            if (childNode) {
                childNodes.emplace_back(childNode);
            }
        }
    }

    DockingNode::~DockingNode() = default;

    void DockingNode::FromJson(JsonLibrary::JsonObject &jsonObject) {
        id = jsonObject["id"];
        relativeXPos = jsonObject["relativeXPos"];
        relativeYPos = jsonObject["relativeYPos"];
        relativeXSize = jsonObject["relativeXSize"];
        relativeYSize = jsonObject["relativeYSize"];
        splitAxis = jsonObject["splitAxis"];
        isCentralNode = jsonObject["isCentralNode"];

        jsonObject.GetField("childNodes").DecodeArray(childNodes);
    }

    void DockingNode::ToJson(JsonLibrary::JsonObject &jsonObject) {
        jsonObject["id"] = id;
        jsonObject["relativeXPos"] = relativeXPos;
        jsonObject["relativeYPos"] = relativeYPos;
        jsonObject["relativeXSize"] = relativeXSize;
        jsonObject["relativeYSize"] = relativeYSize;
        jsonObject["splitAxis"] = splitAxis;
        jsonObject["isCentralNode"] = isCentralNode;

        jsonObject.GetField("childNodes").EncodeArray(childNodes);
    }
} // LightRayEngine