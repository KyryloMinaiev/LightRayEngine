//
// Created by MrFlyingChip on 26.06.2024.
//

#include "LightRayLog.h"
#include <algorithm>

namespace LightRayEngine {
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

    void LightRayLog::Log(const std::string &message) {
        GetOrCreateInstance()->LogInternal(LogLevel::Message, message);
    }

    void LightRayLog::LogWarning(const std::string &message) {
        GetOrCreateInstance()->LogInternal(LogLevel::Warning, message);
    }

    void LightRayLog::LogError(const std::string &message) {
        GetOrCreateInstance()->LogInternal(LogLevel::Error, message);
    }

    void LightRayLog::LogException(const std::string &message) {
        GetOrCreateInstance()->LogInternal(LogLevel::Exception, message);
    }

    void LightRayLog::LogInternal(LogLevel logLevel, const std::string &message) {
        LogInfo logInfo;
        logInfo.logLevel = logLevel;
        std::time_t now = std::time(nullptr);
        logInfo.logTime = *std::localtime(&now);
        logInfo.log = message;
        m_logsList.push_back(logInfo);
        UpdateSubscribers(logInfo);
    }
}
