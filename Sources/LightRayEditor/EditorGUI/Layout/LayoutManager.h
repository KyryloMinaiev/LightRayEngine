//
// Created by MrFlyingChip on 21.11.2024.
//

#ifndef LIGHTRAYAPPLICATION_LAYOUTMANAGER_H
#define LIGHTRAYAPPLICATION_LAYOUTMANAGER_H

#include "EditorLayout.h"

namespace LightRayEngine {
    class LayoutManager {
    public:
        static EditorLayout GetCurrentLayout();
    };

} // LightRayEngine

#endif //LIGHTRAYAPPLICATION_LAYOUTMANAGER_H
