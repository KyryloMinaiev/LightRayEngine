//
// Created by MrFlyingChip on 25.06.2024.
//

#ifndef LIGHTRAYENGINE_FILEUTILS_H
#define LIGHTRAYENGINE_FILEUTILS_H

#include <string>
#include <vector>

namespace LightRayEngine {
    class FileUtils {
    public:
        static bool TryLoadFile(const std::string &path, std::string &output);

        static bool TryLoadFile(const std::string &path, std::vector<char> &output, int &dataLength);

        static bool TrySaveFile(const std::string &path, const std::string &input);

        static bool TrySaveFile(const std::string &path, const std::vector<char> &input, int dataLength);

        static bool TryAppendFile(const std::string &path, const std::string &input);

        static float GetLastFileChangeTime(const std::string &path);
        static bool TryCreateFolder(const std::string &path, const std::string &folderName);
    };
}


#endif //LIGHTRAYENGINE_FILEUTILS_H
