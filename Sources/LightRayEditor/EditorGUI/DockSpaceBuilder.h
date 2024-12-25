//
// Created by MrFlyingChip on 17.12.2024.
//

#ifndef LIGHTRAYAPPLICATION_DOCKSPACEBUILDER_H
#define LIGHTRAYAPPLICATION_DOCKSPACEBUILDER_H

#include <imgui.h>

namespace LightRayEngine {
    class DockingData;
    class DockingNode;

    class DockSpaceBuilder {
    public:
        DockSpaceBuilder() = default;
        ~DockSpaceBuilder() = default;

        void BuildDockSpace();
        [[nodiscard]] ImGuiID GetDockSpaceID() const;

        void CleanDockSpace();
        void RebuildDockSpace(DockingData& dockingData);
    private:
        void AddDockingNode(DockingNode& dockingNode, ImGuiDockNodeFlags flags);

        ImGuiID m_dockSpaceID;
    };

} // LightRayEditor

#endif //LIGHTRAYAPPLICATION_DOCKSPACEBUILDER_H
