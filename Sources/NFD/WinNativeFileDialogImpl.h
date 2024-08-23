//
// Created by MrFlyingChip on 22.08.2024.
//

#ifndef LIGHTRAYENGINE_WINNATIVEFILEDIALOGIMPL_H
#define LIGHTRAYENGINE_WINNATIVEFILEDIALOGIMPL_H

#include "INativeFileDialogImpl.h"
#include <Windows.h>
#include <shobjidl.h>

namespace LightRayEngine {
    class WinNativeFileDialogImpl : public INativeFileDialogImpl{
    public:
        ~WinNativeFileDialogImpl() override;

        bool OpenFileDialog(const std::string &filter, const std::string &defaultPath, std::string &outPath) override;
        bool OpenFolderDialog(const std::string &defaultPath, std::string &outPath) override;
    private:
        static bool OpenDialogWindow(const std::string &filter, const std::string &defaultPath, std::string &outPath, DWORD options = 0);
    };

} // LightRayEngine

#endif //LIGHTRAYENGINE_WINNATIVEFILEDIALOGIMPL_H
