//
// Created by MrFlyingChip on 17.12.2024.
//

#include "DockSpaceBuilder.h"
#include "Layout/EditorLayout.h"

namespace LightRayEngine {
    void DockSpaceBuilder::BuildDockSpace() {
        m_dockSpaceID = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    }

    ImGuiID DockSpaceBuilder::GetDockSpaceID() const {
        return m_dockSpaceID;
    }

    void DockSpaceBuilder::CleanDockSpace() {

    }

    void DockSpaceBuilder::RebuildDockSpace(DockingData &dockingData) {

    }
} // LightRayEditor