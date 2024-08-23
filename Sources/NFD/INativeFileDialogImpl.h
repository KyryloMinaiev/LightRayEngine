//
// Created by MrFlyingChip on 22.08.2024.
//

#ifndef LIGHTRAYENGINE_INATIVEFILEDIALOGIMPL_H
#define LIGHTRAYENGINE_INATIVEFILEDIALOGIMPL_H

#include <string>

namespace LightRayEngine {
    class INativeFileDialogImpl {
    public:
        virtual ~INativeFileDialogImpl() = default;
        virtual bool OpenFileDialog(const std::string &filter, const std::string &defaultPath, std::string &outPath) = 0;
        virtual bool OpenFolderDialog(const std::string &defaultPath, std::string &outPath) = 0;
    };

} // LightRa

#endif //LIGHTRAYENGINE_INATIVEFILEDIALOGIMPL_H
