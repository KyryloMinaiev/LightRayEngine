//
// Created by MrFlyingChip on 25.06.2024.
//

#include "FileUtils.h"
#include <fstream>
#include <sstream>
#include <filesystem>

namespace LightRayEngine {
    bool FileUtils::TryLoadFile(const std::string &path, std::string &output) {
        std::ifstream inputFileStream;
        inputFileStream.open(path);

        if (!inputFileStream.is_open() || inputFileStream.fail()) {
            return false;
        }

        std::stringstream buffer;
        buffer << inputFileStream.rdbuf();
        output = buffer.str();
        inputFileStream.close();

        return true;
    }

    bool FileUtils::TryLoadFile(const std::string &path, std::vector<char> &output, int &dataLength) {
        std::ifstream inputFileStream;
        inputFileStream.open(path, std::ios::binary);

        if (!inputFileStream.is_open() || inputFileStream.fail()) {
            return false;
        }

        inputFileStream.seekg(0, std::ios::end);
        dataLength = inputFileStream.tellg();
        inputFileStream.seekg(0, std::ios::beg);
        char *outputArray = new char[dataLength];
        inputFileStream.read(outputArray, dataLength);
        inputFileStream.close();

        output.clear();
        for (int i = 0; i < dataLength; ++i) {
            output.push_back(outputArray[i]);
        }

        delete[] outputArray;

        return true;
    }

    bool FileUtils::TrySaveFile(const std::string &path, const std::string &input) {
        std::ofstream outputFileStream;
        outputFileStream.open(path, std::ios::trunc);

        if (!outputFileStream.is_open() || outputFileStream.fail()) {
            return false;
        }

        outputFileStream << input;
        outputFileStream.close();

        return true;
    }

    bool FileUtils::TrySaveFile(const std::string &path, const std::vector<char> &input, int dataLength) {
        std::ofstream outputFileStream;
        outputFileStream.open(path, std::ios::trunc);

        if (!outputFileStream.is_open() || outputFileStream.fail()) {
            return false;
        }

        outputFileStream << input.data();
        outputFileStream.close();

        return true;
    }

    float FileUtils::GetLastFileChangeTime(const std::string &path) {
        return 0;
    }

    bool FileUtils::TryAppendFile(const std::string &path, const std::string &input) {
        std::ofstream outputFileStream;
        outputFileStream.open(path, std::ios::app);

        if (!outputFileStream.is_open() || outputFileStream.fail()) {
            return false;
        }

        outputFileStream << input;
        outputFileStream.close();

        return true;
    }

    bool FileUtils::TryCreateFolder(const std::string &path, const std::string &folderName) {
        if(!std::filesystem::exists(path)){
            return false;
        }

        std::string fullPath = path + "/" + folderName;
        return std::filesystem::create_directory(fullPath);
    }
}
