//
// Created by MrFlyingChip on 05.06.2025.
//

#ifndef LIGHTRAYAPPLICATION_DOCKINGNODE_H
#define LIGHTRAYAPPLICATION_DOCKINGNODE_H

#include "JsonLibrary.h"
#include <vector>
#include <imgui.h>
#include <imgui_internal.h>

namespace LightRayEngine {
    class DockingNode : public JsonLibrary::JsonSerialized {
    public:
        DockingNode() = default;
        explicit DockingNode(ImGuiDockNode *node);

        ~DockingNode() override;

        void FromJson(JsonLibrary::JsonObject &jsonObject) override;

        void ToJson(JsonLibrary::JsonObject &jsonObject) override;
        std::vector <DockingNode> childNodes;

        int id = 0;
        float relativeXPos = 0, relativeYPos = 0;
        float relativeXSize = 0, relativeYSize = 0;
        int splitAxis = -1;
        bool isCentralNode = false;
    };
} // LightRayEngine


#endif //LIGHTRAYAPPLICATION_DOCKINGNODE_H
