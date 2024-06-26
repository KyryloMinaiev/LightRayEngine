//
// Created by MrFlyingChip on 26.06.2024.
//

#ifndef LIGHTRAYENGINE_LIGHTRAYLOG_H
#define LIGHTRAYENGINE_LIGHTRAYLOG_H

#include <string>
#include <ctime>
#include <memory>
#include <vector>

namespace LightRay{
    enum class LogLevel{
        Message,
        Warning,
        Error,
        Exception
    };

    struct LogInfo{
        LogLevel logLevel;
        std::string log;
        std::tm logTime;
    };

    class ILightRayLogUpdateSubscriber{
    public:
        virtual void OnLogUpdated(const LogInfo& logInfo) = 0;
    };

    class LightRayLog {
    public:
        template<typename... Args>
        static void Log(const std::string& format, Args... args);
        template<typename... Args>
        static void LogWarning(const std::string& format, Args... args);
        template<typename... Args>
        static void LogError(const std::string& format, Args... args);
        template<typename... Args>
        static void LogException(const std::string& format, Args... args);

        static void SubscribeToLogUpdate(ILightRayLogUpdateSubscriber* logUpdateSubscriber);
        static void UnsubscribeToLogUpdate(ILightRayLogUpdateSubscriber* logUpdateSubscriber);
    private:
        static LightRayLog* GetOrCreateInstance();
        template<typename... Args>
        void LogInternal(LogLevel logLevel, const std::string& format, Args... args);
        template<typename T>
        void FormatString(std::ostringstream& os, const std::string& format, T value);
        template<typename T, typename... Args>
        void FormatString(std::ostringstream& os, const std::string& format, T value, Args... args);

        void UpdateSubscribers(const LogInfo& logInfo);

        std::vector<ILightRayLogUpdateSubscriber*> m_subscribers;
        std::vector<LogInfo> m_logsList;
        static std::unique_ptr<LightRayLog> s_instance;
    };
}

#endif //LIGHTRAYENGINE_LIGHTRAYLOG_H
