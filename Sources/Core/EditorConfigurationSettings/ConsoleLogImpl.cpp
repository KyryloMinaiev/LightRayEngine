//
// Created by Kirill Minaev on 27.06.2024.
//

#include "ConsoleLogImpl.h"

namespace LightRayEngine {

    void ConsoleLogImpl::OnLogUpdated(const LogInfo &logInfo) {
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

        std::cout << "[" << timeStr << "][" << levelStr << "]: " << logInfo.log << "\n";
    }

    ConsoleLogImpl::ConsoleLogImpl() {
        LightRayLog::SubscribeToLogUpdate(this);
    }

    ConsoleLogImpl::~ConsoleLogImpl() {
        LightRayLog::UnsubscribeToLogUpdate(this);
    }
}