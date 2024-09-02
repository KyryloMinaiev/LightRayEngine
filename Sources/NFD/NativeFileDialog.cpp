//
// Created by MrFlyingChip on 22.08.2024.
//

#include "NativeFileDialog.h"

namespace LightRayEngine {
    bool
    NativeFileDialog::OpenFileDialog(const std::string &filter, const std::string &defaultPath, std::string &outPath) {
        INativeFileDialogImpl* dialogImpl = GetPlatformImpl();
        if(!dialogImpl){
            return false;
        }

        bool success = dialogImpl->OpenFileDialog(filter, defaultPath, outPath);
        delete dialogImpl;
        return success;
    }

    INativeFileDialogImpl *NativeFileDialog::GetPlatformImpl() {
        #if defined(_WIN32)
            return new WinNativeFileDialogImpl();
        #endif

        return nullptr;
    }

    bool NativeFileDialog::OpenFolderDialog(const std::string &defaultPath, std::string &outPath) {
        INativeFileDialogImpl* dialogImpl = GetPlatformImpl();
        if(!dialogImpl){
            return false;
        }

        bool success = dialogImpl->OpenFolderDialog(defaultPath, outPath);
        delete dialogImpl;
        return success;
    }
} // LightRayEngine