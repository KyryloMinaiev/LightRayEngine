//
// Created by MrFlyingChip on 05.06.2025.
//

#include "DockingData.h"

namespace LightRayEngine {
    DockingData::DockingData(ImGuiID dockSpaceId) : dockSpaceNode(ImGui::DockBuilderGetNode(dockSpaceId)) {
    }

    DockingData::~DockingData() = default;

    void DockingData::FromJson(JsonLibrary::JsonObject &jsonObject) {
        jsonObject["dockSpaceNode"].DecodeObject(dockSpaceNode);
    }

    void DockingData::ToJson(JsonLibrary::JsonObject &jsonObject) {
        jsonObject["dockSpaceNode"].EncodeObject(dockSpaceNode);
    }
}