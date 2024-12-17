//
// Created by MrFlyingChip on 17.12.2024.
//

#ifndef LIGHTRAYAPPLICATION_DOCKSPACEBUILDER_H
#define LIGHTRAYAPPLICATION_DOCKSPACEBUILDER_H

#include <imgui.h>

namespace LightRayEngine {
    class DockSpaceBuilder {
    public:
        DockSpaceBuilder() = default;
        ~DockSpaceBuilder() = default;

        void BuildDockSpace();
        [[nodiscard]] ImGuiID GetDockSpaceID() const;

    private:
        ImGuiID m_dockSpaceID;
    };

} // LightRayEditor

#endif //LIGHTRAYAPPLICATION_DOCKSPACEBUILDER_H
