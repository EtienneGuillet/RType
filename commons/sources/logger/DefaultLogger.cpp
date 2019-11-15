/*
** EPITECH PROJECT, 2019
** B12Software
** File description:
** DefaultLogger.cpp
*/

/* Created the 18/09/2019 at 15:38 by julian.frabel@epitech.eu */

#include "DefaultLogger.hpp"

std::shared_ptr<b12software::logger::ILogger> b12software::logger::DefaultLogger::currentLogger = std::shared_ptr<b12software::logger::ILogger>();

void b12software::logger::DefaultLogger::SetDefaultLogger(const std::shared_ptr<ILogger> &logger)
{
    DefaultLogger::currentLogger = logger;
}

const std::shared_ptr<b12software::logger::ILogger> &b12software::logger::DefaultLogger::GetCurrentLogger()
{
    return DefaultLogger::currentLogger;
}

void b12software::logger::DefaultLogger::ClearDefautLogger()
{
    DefaultLogger::currentLogger = std::shared_ptr<b12software::logger::ILogger>();
}

void b12software::logger::DefaultLogger::SetLogLevel(b12software::logger::LogLevel level)
{
    if (DefaultLogger::currentLogger) {
        DefaultLogger::currentLogger->setLogLevel(level);
    }
}

b12software::logger::LogLevel b12software::logger::DefaultLogger::GetLogLevel()
{
    if (DefaultLogger::currentLogger) {
        return DefaultLogger::currentLogger->getLogLevel();
    }
    return LogLevelNone;
}

void b12software::logger::DefaultLogger::Log(b12software::logger::LogLevel messageLevel, const std::string &message)
{
    if (DefaultLogger::currentLogger) {
        DefaultLogger::currentLogger->log(messageLevel, message);
    }
}