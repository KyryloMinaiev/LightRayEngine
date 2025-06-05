//
// Created by MrFlyingChip on 05.06.2025.
//

#include "DockingNode.h"

namespace LightRayEngine {
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

    DockingNode::DockingNode(ImGuiDockNode *node) {
        if (!node) {
            return;
        }

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
}