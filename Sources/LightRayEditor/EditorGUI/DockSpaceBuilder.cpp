//
// Created by MrFlyingChip on 17.12.2024.
//

#include "DockSpaceBuilder.h"
#include "Layout/EditorLayout.h"
#include "imgui_internal.h"

namespace LightRayEngine {
    void DockSpaceBuilder::BuildDockSpace() {
        ImGui::DockSpaceOverViewport(m_dockSpaceID, ImGui::GetMainViewport());
    }

    ImGuiID DockSpaceBuilder::GetDockSpaceID() const {
        return m_dockSpaceID;
    }

    void DockSpaceBuilder::CleanDockSpace() {

    }

    void DockSpaceBuilder::RebuildDockSpace(DockingData &dockingData) {
        m_dockSpaceID = dockingData.dockSpaceNode.id;
        AddDockingNode(dockingData.dockSpaceNode, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderFinish(m_dockSpaceID);
    }

    void DockSpaceBuilder::AddDockingNode(DockingNode &dockingNode, ImGuiDockNodeFlags flags) {
        ImGui::DockBuilderAddNode(dockingNode.id, flags);
        ImGui::DockBuilderSetNodePos(dockingNode.id, ImVec2(dockingNode.relativeXPos, dockingNode.relativeYPos));
        ImGui::DockBuilderSetNodeSize(dockingNode.id, ImVec2(dockingNode.relativeXSize, dockingNode.relativeYSize));

        for (auto childNode: dockingNode.childNodes) {
            AddDockingNode(childNode, 0);
        }
    }
} // LightRayEditor