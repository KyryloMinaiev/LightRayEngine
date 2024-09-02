//
// Created by MrFlyingChip on 22.08.2024.
//

#include "WinNativeFileDialogImpl.h"

namespace LightRayEngine {
    WinNativeFileDialogImpl::~WinNativeFileDialogImpl() = default;

    bool WinNativeFileDialogImpl::OpenFileDialog(const std::string &filter, const std::string &defaultPath,
                                                 std::string &outPath) {
        return OpenDialogWindow(filter, defaultPath, outPath);
    }

    bool WinNativeFileDialogImpl::OpenFolderDialog(const std::string &defaultPath, std::string &outPath) {
        return OpenDialogWindow("", defaultPath, outPath, FOS_PICKFOLDERS);
    }

    bool
    WinNativeFileDialogImpl::OpenDialogWindow(const std::string &filter, const std::string &defaultPath,
                                              std::string &outPath, DWORD options) {
        //  CREATE FILE OBJECT INSTANCE
        HRESULT systemHR = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (FAILED(systemHR))
            return FALSE;

        // CREATE FileOpenDialog OBJECT
        IFileOpenDialog *fileOpenDialog;
        systemHR = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog,
                                    reinterpret_cast<void **>(&fileOpenDialog));
        if (FAILED(systemHR)) {
            CoUninitialize();
            return FALSE;
        }

        DWORD dwFlags;
        systemHR = fileOpenDialog->GetOptions(&dwFlags);
        if (FAILED(systemHR)) {
            fileOpenDialog->Release();
            CoUninitialize();
            return FALSE;
        }

        systemHR = fileOpenDialog->SetOptions(dwFlags | options);
        if (FAILED(systemHR)) {
            fileOpenDialog->Release();
            CoUninitialize();
            return FALSE;
        }

        //  SHOW OPEN FILE DIALOG WINDOW
        systemHR = fileOpenDialog->Show(NULL);
        if (FAILED(systemHR)) {
            fileOpenDialog->Release();
            CoUninitialize();
            return FALSE;
        }

        //  RETRIEVE FILE NAME FROM THE SELECTED ITEM
        IShellItem *files;
        systemHR = fileOpenDialog->GetResult(&files);
        if (FAILED(systemHR)) {
            fileOpenDialog->Release();
            CoUninitialize();
            return FALSE;
        }

        //  STORE AND CONVERT THE FILE NAME
        PWSTR fileSystemPath;
        systemHR = files->GetDisplayName(SIGDN_FILESYSPATH, &fileSystemPath);
        if (FAILED(systemHR)) {
            files->Release();
            fileOpenDialog->Release();
            CoUninitialize();
            return FALSE;
        }

        //  FORMAT AND STORE THE FILE PATH
        std::wstring path(fileSystemPath);
        std::string c(path.begin(), path.end());
        outPath = c;

        //  SUCCESS, CLEAN UP
        CoTaskMemFree(fileSystemPath);
        files->Release();
        fileOpenDialog->Release();
        CoUninitialize();
        return TRUE;
    }
} // LightRayEngine