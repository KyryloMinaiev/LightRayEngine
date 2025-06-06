//
// Created by MrFlyingChip on 06.06.2025.
//

#ifndef LIGHTRAYAPPLICATION_IENGINEDEFAULTEDITORWINDOW_H
#define LIGHTRAYAPPLICATION_IENGINEDEFAULTEDITORWINDOW_H

#include <string>

namespace LightRayEngine {
    class IEngineDefaultEditorWindow{
    public:
        virtual std::string GetDefaultWindowName() = 0;
        virtual ~IEngineDefaultEditorWindow() {}
    };
}

#endif //LIGHTRAYAPPLICATION_IENGINEDEFAULTEDITORWINDOW_H
