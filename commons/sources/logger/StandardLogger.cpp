/*
** EPITECH PROJECT, 2019
** B12Software
** File description:
** StandardLogger.cpp
*/

/* Created the 18/09/2019 at 14:34 by julian.frabel@epitech.eu */

#include <map>
#include <thread>
#include <iostream>
#include "StandardLogger.hpp"

b12software::logger::StandardLogger::StandardLogger(b12software::logger::LogLevel defaultLevel)
    : _currentLevel(defaultLevel)
{

}

void b12software::logger::StandardLogger::setLogLevel(b12software::logger::LogLevel level)
{
    _currentLevel = level;
}

b12software::logger::LogLevel b12software::logger::StandardLogger::getLogLevel() const
{
    return _currentLevel;
}

void b12software::logger::StandardLogger::log(b12software::logger::LogLevel messageLevel, const std::string &message)
{
    std::map<LogLevel, std::string> stringLevels = {
        {LogLevelDebug, "DEBUG"},
        {LogLevelInfo, "INFO"},
        {LogLevelWarn, "WARN"},
        {LogLevelError, "ERROR"},
        {LogLevelFatal, "FATAL"},
        {LogLevelNone, "NONE"},
    };
    if (messageLevel >= LogLevelNone)
        return;
    if (messageLevel >= _currentLevel) {
        if (stringLevels.count(messageLevel) != 0)
            std::cerr << "[" << stringLevels[messageLevel] << "][" << std::this_thread::get_id() << "]" << message << std::endl;
        else
            std::cerr << "[" << std::to_string(messageLevel) << "][" << std::this_thread::get_id() << "]" << message << std::endl;
    }
}
