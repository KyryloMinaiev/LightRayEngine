//
// Created by MrFlyingChip on 05.06.2025.
//

#ifndef LIGHTRAYAPPLICATION_DOCKINGDATA_H
#define LIGHTRAYAPPLICATION_DOCKINGDATA_H

#include "JsonLibrary.h"
#include "DockingNode.h"
#include <vector>
#include <imgui.h>
#include <imgui_internal.h>

namespace LightRayEngine {
    class DockingData : public JsonLibrary::JsonSerialized {
    public:
        DockingData() = default;
        explicit DockingData(ImGuiID dockSpaceId);
        ~DockingData() override;
        void FromJson(JsonLibrary::JsonObject &jsonObject) override;
        void ToJson(JsonLibrary::JsonObject &jsonObject) override;
        DockingNode dockSpaceNode;
    };
}


#endif //LIGHTRAYAPPLICATION_DOCKINGDATA_H
