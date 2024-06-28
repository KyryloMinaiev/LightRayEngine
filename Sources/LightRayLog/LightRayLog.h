//
// Created by MrFlyingChip on 26.06.2024.
//

#ifndef LIGHTRAYENGINE_LIGHTRAYLOG_H
#define LIGHTRAYENGINE_LIGHTRAYLOG_H

#include <string>
#include <ctime>
#include <memory>
#include <vector>
#include <iomanip>
#include <sstream>

namespace LightRayEngine{
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
        static void Log(const std::string& message);
        static void LogWarning(const std::string& message);
        static void LogError(const std::string& message);
        static void LogException(const std::string& message);

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
        void LogInternal(LogLevel logLevel, const std::string& message);

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

#endif //LIGHTRAYENGINE_LIGHTRAYLOG_H
