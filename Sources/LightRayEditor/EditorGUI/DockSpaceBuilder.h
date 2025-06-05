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

        void BuildDockSpace() const;
        [[nodiscard]] ImGuiID GetDockSpaceID() const;

        void CleanDockSpace();
        void RebuildDockSpace(DockingData& dockingData);
    private:

        ImGuiID m_dockSpaceID;

        static constexpr int k_dockSpaceDefaultID = 1;

        ImGuiID AddDockingNode(const DockingNode &dockingNode, ImGuiID id, ImGuiDockNodeFlags flags);
        static ImGuiID ConstructNode(const DockingNode &dockingNode, ImGuiID id, ImGuiDockNodeFlags flags);
    };

} // LightRayEditor

#endif //LIGHTRAYAPPLICATION_DOCKSPACEBUILDER_H
