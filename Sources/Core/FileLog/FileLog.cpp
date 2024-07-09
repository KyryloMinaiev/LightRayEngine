//
// Created by Kirill Minaev on 09.07.2024.
//

#include "FileLog.h"
#include <sstream>

namespace LightRayEngine{

    FileLog::FileLog() {
        LightRayLog::SubscribeToLogUpdate(this);
        //Empty log file on start
        FileUtils::TrySaveFile(k_editorLogFileName, "");
    }

    FileLog::~FileLog() {
        LightRayLog::UnsubscribeToLogUpdate(this);
    }

    void FileLog::OnLogUpdated(const LogInfo &logInfo) {
        auto timeStr = std::put_time(&logInfo.logTime, "%Y-%m-%d %H:%M:%S");
        std::string levelStr;
        switch (logInfo.logLevel) {
            case LogLevel::Message:
                levelStr = "Message";
                break;
            case LogLevel::Warning:
                levelStr = "Warning";
                break;
            case LogLevel::Exception:
                levelStr = "Exception";
            case LogLevel::Error:
                levelStr = "Error";
                break;
        }

        std::stringstream stringStream;
        stringStream << "[" << timeStr << "][" << levelStr << "]: " << logInfo.log << "\n";
        FileUtils::TryAppendFile(k_editorLogFileName, stringStream.str());
    }
}