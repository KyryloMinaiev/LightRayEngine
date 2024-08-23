//
// Created by MrFlyingChip on 22.08.2024.
//

#ifndef LIGHTRAYENGINE_NATIVEFILEDIALOG_H
#define LIGHTRAYENGINE_NATIVEFILEDIALOG_H

#include "WinNativeFileDialogImpl.h"

namespace LightRayEngine {
    class NativeFileDialog{
    public:
        static bool OpenFileDialog(const std::string& filter, const std::string& defaultPath, std::string& outPath);
        static bool OpenFolderDialog(const std::string& defaultPath, std::string& outPath);
    private:
        static INativeFileDialogImpl* GetPlatformImpl();
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_NATIVEFILEDIALOG_H
