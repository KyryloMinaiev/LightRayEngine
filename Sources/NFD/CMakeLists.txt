add_library(native-file-dialog STATIC NativeFileDialog.cpp
        INativeFileDialogImpl.h
        WinNativeFileDialogImpl.cpp
        WinNativeFileDialogImpl.h)
target_include_directories(native-file-dialog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})