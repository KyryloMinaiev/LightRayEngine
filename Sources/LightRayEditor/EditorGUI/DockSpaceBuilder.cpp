//
// Created by MrFlyingChip on 17.12.2024.
//

#include "DockSpaceBuilder.h"
#include "Layout/EditorLayout.h"
#include "imgui_internal.h"

namespace LightRayEngine {
    void DockSpaceBuilder::BuildDockSpace() const {
        ImGui::DockSpaceOverViewport(m_dockSpaceID, ImGui::GetMainViewport());
    }

    ImGuiID DockSpaceBuilder::GetDockSpaceID() const {
        return m_dockSpaceID;
    }

    void DockSpaceBuilder::CleanDockSpace() {

    }

    void DockSpaceBuilder::RebuildDockSpace(DockingData &dockingData) {
        m_dockSpaceID = AddDockingNode(dockingData.dockSpaceNode, k_dockSpaceDefaultID, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderFinish(m_dockSpaceID);
    }

    ImGuiID DockSpaceBuilder::AddDockingNode(const DockingNode &dockingNode, ImGuiID id, ImGuiDockNodeFlags flags) {
        ImGuiID nodeID = ConstructNode(dockingNode, id, flags);

        for (const auto& childNode: dockingNode.childNodes) {
            AddDockingNode(childNode, childNode.id, ImGuiDockNodeFlags_None);
        }

        return nodeID;
    }

    ImGuiID DockSpaceBuilder::ConstructNode(const DockingNode &dockingNode, ImGuiID id, ImGuiDockNodeFlags flags) {
        ImGuiID nodeID = ImGui::DockBuilderAddNode(id, flags);
        ImGui::DockBuilderSetNodePos(nodeID, ImVec2(dockingNode.relativeXPos, dockingNode.relativeYPos));
        ImGui::DockBuilderSetNodeSize(nodeID, ImVec2(dockingNode.relativeXSize, dockingNode.relativeYSize));

        return nodeID;
    }
} // LightRayEditor