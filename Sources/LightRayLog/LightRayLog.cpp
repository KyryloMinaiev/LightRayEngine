//
// Created by MrFlyingChip on 26.06.2024.
//

#include "LightRayLog.h"

#include <iomanip>
#include <sstream>

namespace LightRay {
    std::unique_ptr<LightRayLog> LightRayLog::s_instance;

    LightRayLog *LightRayLog::GetOrCreateInstance() {
        if(s_instance == nullptr){
            s_instance = std::make_unique<LightRayLog>();
        }

        return s_instance.get();
    }

    void LightRayLog::SubscribeToLogUpdate(ILightRayLogUpdateSubscriber *logUpdateSubscriber) {
        if(!logUpdateSubscriber){
            return;
        }

        GetOrCreateInstance()->m_subscribers.push_back(logUpdateSubscriber);
    }

    void LightRayLog::UpdateSubscribers(const LogInfo &logInfo) {
        for (auto subscriber : m_subscribers) {
            if(subscriber){
                subscriber->OnLogUpdated(logInfo);
            }
        }
    }

    void LightRayLog::UnsubscribeToLogUpdate(ILightRayLogUpdateSubscriber *logUpdateSubscriber) {
        if(!logUpdateSubscriber){
            return;
        }

        LightRayLog* log = GetOrCreateInstance();
        auto it = std::find(log->m_subscribers.begin(), log->m_subscribers.end(), logUpdateSubscriber);
        log->m_subscribers.erase(it);
    }

    template<typename T>
    void LightRayLog::FormatString(std::ostringstream &os, const std::string &format, T value) {
        size_t pos = format.find("{}");
        if (pos != std::string::npos) {
            os << format.substr(0, pos) << value;
            FormatString(os, format.substr(pos + 2), "");
        } else {
            os << format;
        }
    }

    template<typename T, typename... Args>
    void LightRayLog::FormatString(std::ostringstream &os, const std::string &format, T value, Args... args) {
        size_t pos = format.find("{}");
        if (pos != std::string::npos) {
            os << format.substr(0, pos) << value;
            FormatString(os, format.substr(pos + 2), args...);
        } else {
            os << format;
        }
    }

    template<typename... Args>
    void LightRayLog::Log(const std::string &format, Args... args) {
        GetOrCreateInstance()->LogInternal(LogLevel::Message, format, args...);
    }

    template<typename... Args>
    void LightRayLog::LogWarning(const std::string &format, Args... args) {
        GetOrCreateInstance()->LogInternal(LogLevel::Warning, format, args...);
    }

    template<typename... Args>
    void LightRayLog::LogError(const std::string &format, Args... args) {
        GetOrCreateInstance()->LogInternal(LogLevel::Error, format, args...);
    }

    template<typename... Args>
    void LightRayLog::LogException(const std::string &format, Args... args) {
        GetOrCreateInstance()->LogInternal(LogLevel::Exception, format, args...);
    }

    template<typename... Args>
    void LightRayLog::LogInternal(LogLevel logLevel, const std::string &format, Args... args) {
        LogInfo logInfo;

        logInfo.logLevel = logLevel;
        std::time_t now = std::time(nullptr);
        logInfo.logTime = *std::localtime(&now);

        std::ostringstream logMessage;
        FormatString(logMessage, format, args...);
        logInfo.log = logMessage.str();

        m_logsList.push_back(logInfo);
        UpdateSubscribers(logInfo);
    }
}
